/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 19:01:16 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 19:01:17 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ctrl_c_push(int get)
{
	char	*path;

	(void)get;
	if (g_full_pwd)
	{
		if (!(path = (char*)malloc(sizeof(char) * 1024)))
			notes('g', 1, 0, 1);
		ft_memset(path, '\0', 1024);
		ft_printf("\n%s $> ", getcwd(path, 1023));
		free_str(&path);
	}
	else
		ft_printf("\n$> ");
}

static void	init_settings(t_stg *settings, char ***en)
{
	char	*path;

	if (!(path = (char*)malloc(sizeof(char) * 1024)))
		notes('g', 1, 0, 1);
	ft_memset(path, '\0', 1024);
	settings->my_path = getcwd(path, 1023);
	settings->last_path = ft_strdup(settings->my_path);
	settings->m_env = en;
	settings->free_en = 0;
}

/*
** If the command is: 'cd' or 'exit' the main thread will work on it.
** Else the function call to 'second_thread_management'
**		that create new process for the command.
*/

static void	cmd_management(t_stg *settings, char **cmds)
{
	char	*cmd;
	int		index;

	index = -1;
	while (cmds[++index])
	{
		if (!(cmd = get_cmd(cmds[index])))
			return ;
		if (!ft_strcmp(cmd, "exit"))
			cmd_exit(settings, cmds[index], cmd, cmds);
		else if (!ft_strcmp(cmd, "env"))
			cmd_env(settings, cmds[index], 1);
		else if (!ft_strcmp(cmd, "setenv"))
			cmd_env(settings, cmds[index], 2);
		else if (!ft_strcmp(cmd, "unsetenv"))
			cmd_env(settings, cmds[index], 3);
		else if (!ft_strcmp(cmd, "cd"))
			cmd_cd(settings, cmds[index]);
		else if (!ft_strcmp(cmd, "polo"))
			cmd_polo(settings, cmds[index]);
		else
			second_thread_management(settings, cmds[index], cmd);
		free_str(&cmd);
	}
}

/*
** Function that take a full cmd with many commands separated by a semi colon
** and return array of pointer to strings (clear commands).
** The function also remove the spaces from the start and the end of etch
** command.
*/

static char	**cmd_get_commands(char *full_cmd)
{
	char	**cmds;
	char	*tmp;
	int		index;

	index = -1;
	cmds = ft_strsplit(full_cmd, ';');
	while (cmds[++index])
	{
		tmp = ft_strtrim(cmds[index]);
		free_str(&cmds[index]);
		cmds[index] = tmp;
	}
	return (cmds);
}

/*
**	Step One: ('main') -> init_settings, lifetime loop ->
**		get commands from stdin; {main thread}
**	Step Two: ('cmd_management') -> check witch command
**		we get and call to the right function;
**				Options: 'cd' | 'echo' | 'exit' | 'env' | 'program';
**				Theards:
**							'cd' & 'exit' -> {main thread};
**							all other commands -> {child thread};
**	Errors:
**		void	notes(char type_cmd, int num_error, char **free_str,
**						int do_exit);
**				'type_cmd':		g-global, c-cd, e-echo, n-env, p-program;
**				'num_error':	witch error to print?
**				'str_to_free':	0->do not free;
**				'do_exit':		do exit after printing the error;
*/

int			main(int ac, char **av, char **en)
{
	char	*full_cmd;
	char	**cmds;
	t_stg	settings;

	full_cmd = 0;
	cmds = 0;
	init_flags(&settings, ac, av);
	init_settings(&settings, &en);
	signal(SIGINT, ctrl_c_push);
	if (g_full_pwd)
		ft_printf("%s ", settings.my_path);
	ft_printf("$> ");
	while (get_next_line(0, &full_cmd))
	{
		cmds = cmd_get_commands(clear_full_cmd(&full_cmd));
		cmd_management(&settings, cmds);
		if (full_cmd)
			free_str(&full_cmd);
		if (cmds)
			ft_free_strsplit(&cmds);
		if (g_full_pwd)
			ft_printf("%s ", settings.my_path);
		ft_printf("$> ");
	}
	return (0);
}
