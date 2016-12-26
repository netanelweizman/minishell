/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:14:18 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 20:14:19 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** This function take a pointer to string and return new pointer to string
** without quotation marks
** remove_quotation() -> rq();
*/

char		*rq(char **str)
{
	char	*new;
	int		index;
	int		len;

	if (!(*str))
		return (0);
	index = -1;
	len = ft_strlen(*str);
	while (str[0][++index])
		if (str[0][index] == '"')
			len--;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
	{
		notes('g', 1, 0, 0);
		return (0);
	}
	index = -1;
	len = -1;
	while (str[0][++index])
		if (str[0][index] != '"')
			new[++len] = str[0][index];
	new[len + 1] = '\0';
	free_str(str);
	return (*str = new);
}

static int	words_count(char *str)
{
	int		count;
	int		status;

	count = 0;
	status = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			status = 0;
		else if (status == 0)
		{
			count++;
			status = 1;
		}
		str++;
	}
	return (count);
}

static int	char_count(char *str)
{
	int		count;
	int		status;

	count = 0;
	status = 0;
	while (*str)
	{
		if (*str == '"' && status)
			status = 0;
		else if (*str == '"')
			status = 1;
		if (status || (*str != ' ' && *str != '\t'))
			count++;
		str++;
	}
	return (count);
}

static void	fill_new_cmd(char *new, char *full_cmd, int index, int len)
{
	int	spaces;
	int status;

	spaces = 0;
	status = 0;
	while (full_cmd[++index])
	{
		if (full_cmd[index] == '"' && status)
			status = 0;
		else if (full_cmd[index] == '"')
			status = 1;
		if (status || (full_cmd[index] != ' ' && full_cmd[index] != '\t'))
		{
			new[++len] = full_cmd[index];
			spaces = 1;
		}
		else if (spaces)
		{
			new[++len] = ' ';
			spaces = 0;
		}
	}
	new[++len] = '\0';
}

/*
** Function that takes a pointer to 'full_cmd' string and return new
** 'full_cmd' with only one space betwine etch word.
*/

char		*clear_full_cmd(char **full_cmd)
{
	int		len;
	int		index;
	int		spaces;
	char	*new;

	len = 0;
	index = -1;
	len = char_count(*full_cmd);
	spaces = words_count(full_cmd[0]) - 1;
	if (!(new = (char*)malloc(sizeof(char) * (spaces + len + 1))))
	{
		notes('g', 1, 0, 0);
		return (0);
	}
	fill_new_cmd(new, full_cmd[0], -1, -1);
	free_str(full_cmd);
	return (new);
}
