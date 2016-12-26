/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_polo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:44:48 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 22:44:50 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** usage: polo [test / project / backup] [name]
*/

static void	cmd_polo_test(t_stg *settings, char *name)
{
	char	*cmd;
	char	*nm;

	nm = ft_strjoin(name, ".c");
	cmd = ft_strjoin("tar -xf ", settings->polo_test);
	second_thread_management(settings, cmd, "tar");
	free_str(&cmd);
	cmd = ft_strjoin("mv polo_test/polo_test.c ", nm);
	second_thread_management(settings, cmd, "mv");
	free_str(&cmd);
	cmd = "rm -rf polo_test";
	second_thread_management(settings, cmd, "rm");
	cmd = ft_strjoin("vim ", nm);
	second_thread_management(settings, cmd, "vim");
	free_str(&cmd);
	free_str(&nm);
}

static void	cmd_polo_project(t_stg *settings, char *name)
{
	char	*cmd;

	cmd = ft_strjoin("tar -xf ", settings->polo_proj);
	second_thread_management(settings, cmd, "tar");
	free_str(&cmd);
	cmd = ft_strjoin("mv polo_project ", name);
	second_thread_management(settings, cmd, "mv");
	free_str(&cmd);
	cmd = ft_strjoin("open ", name);
	second_thread_management(settings, cmd, "open");
	free_str(&cmd);
}

static void	cmd_polo_backup(t_stg *settings, char *name)
{
	char	*cmd;
	char	*tmp;
	char	*desktop;

	desktop = env_get_value(*(settings->m_env), "HOME");
	tmp = ft_strjoin(desktop, "/Desktop/");
	free_str(&desktop);
	desktop = ft_strjoin(tmp, name);
	free_str(&tmp);
	tmp = ft_strjoin(desktop, ".tar.gz");
	free_str(&desktop);
	desktop = ft_strjoin("tar -cf ", tmp);
	cmd = ft_strjoin(desktop, " .");
	second_thread_management(settings, cmd, "tar");
	free_str(&cmd);
	free_str(&tmp);
	free_str(&desktop);
}

/*
** 'polo' it a command that can do three things:
**		Create a fast test file
**		Create a new project
**		Create a fast backup on your dekstop
*/

void		cmd_polo(t_stg *settings, char *full_cmd)
{
	char	**split;
	int		i;

	i = 0;
	if (!(split = ft_strsplit(full_cmd, ' ')))
		return (notes('g', 1, 0, 0));
	if (ft_strsplit_len(split) == 3)
	{
		if (!ft_strcmp(split[1], "test"))
			cmd_polo_test(settings, split[2]);
		else if (!ft_strcmp(split[1], "project"))
			cmd_polo_project(settings, split[2]);
		else if (!ft_strcmp(split[1], "backup"))
			cmd_polo_backup(settings, split[2]);
	}
	else
		ft_printf("usage: polo [test / project / backup] [name]\n");
	ft_free_strsplit(&split);
}
