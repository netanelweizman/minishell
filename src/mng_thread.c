/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:12:10 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 20:12:11 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Return new string of the command;
** ex: get_cmd(settings, "echo hello work!") -> "echo";
*/

char		*get_cmd(char *full_cmd)
{
	char	*cmd;
	size_t	len;

	len = 0;
	while (full_cmd[len] && full_cmd[len] != ' ' && full_cmd[len] != '\t')
		len++;
	if (!(cmd = (char*)malloc(sizeof(char) * (len + 1))))
	{
		notes('g', 1, 0, 0);
		return (0);
	}
	cmd[len] = '\0';
	len = 0;
	while (full_cmd[len] && full_cmd[len] != ' ' && full_cmd[len] != '\t')
	{
		cmd[len] = full_cmd[len];
		len++;
	}
	return (cmd);
}

/*
** This function check witch command we got:
**		'echo' / 'env...' / 'program' and run them.
** If we got a 'program' we have to make sure that it's a
**		reat program and not a jank.
** DONT FORGET TO FREE CMD IN THE FUNCTIONS.
*/

static void	witch_cmd(t_stg *settings, char *full_cmd, char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		cmd_echo(settings, full_cmd);
	else
		cmd_program(settings, full_cmd);
}

/*
** This function create a NEW process and return the MAIN
**		to work whan the NEW process done.
** Thins function and ONLY this function call to exit(1)
**		whan the NEW process done.
*/

void		second_thread_management(t_stg *settings,
	char *full_cmd, char *cmd)
{
	pid_t	process;
	int		status;

	process = fork();
	if (process > 0)
	{
		waitpid(process, &status, 0);
		return ;
	}
	if (process == 0)
	{
		witch_cmd(settings, full_cmd, cmd);
		exit(1);
	}
}
