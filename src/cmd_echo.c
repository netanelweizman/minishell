/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:44:48 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 22:44:50 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_echo_special(t_stg *settings, char *str)
{
	char	*value;

	value = env_get_value(*(settings->m_env), str + 1);
	if (value)
	{
		ft_printf("%s", value);
		free_str(&value);
	}
}

static void	cmd_echo_noraml(char *str)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if ((str[i] != '"' && str[i] != '\\') || (i > 0 && str[i - 1] == '\\'))
			write(1, &str[i], 1);
		i++;
	}
}

void		cmd_echo(t_stg *settings, char *full_cmd)
{
	char	**split;
	int		len;
	int		i;

	i = 0;
	if (!(split = ft_strsplit(full_cmd, ' ')))
		return (notes('n', 1, 0, 0));
	len = ft_strsplit_len(split);
	while (++i < len)
	{
		if (i > 1)
			write(1, " ", 1);
		if (split[i][0] == '$')
			cmd_echo_special(settings, split[i]);
		else if (split[i][0])
			cmd_echo_noraml(split[i]);
	}
	write(1, "\n", 1);
	ft_free_strsplit(&split);
}
