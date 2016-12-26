/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:45:24 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 22:45:25 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_program_runer(t_stg *settings, char **cmd_split, char **split)
{
	char	*paths;
	int		ret;
	int		index;

	index = 0;
	paths = cmd_split[0];
	while (1)
	{
		ret = execve(paths, cmd_split, *(settings->m_env));
		if (!split || ret != -1 || !split[index])
			break ;
		if (index > 0)
			free_str(&paths);
		paths = ft_strjoin(split[index], ft_strjoin("/", cmd_split[0]));
		index++;
	}
	if (ret == -1)
		ft_printf("%s: command not found\n", cmd_split[0]);
	if (paths && index > 0)
		free_str(&paths);
	ft_free_strsplit(&split);
	ft_free_strsplit(&cmd_split);
}

/*
** This Functions run the special command. he try to find the right path.
** If the function fall, 'command not found' print to the screen.
*/

void		cmd_program(t_stg *settings, char *full_cmd)
{
	char	**split;
	char	**cmd_split;
	char	*paths;

	split = 0;
	cmd_split = 0;
	paths = 0;
	if (env_search_key(settings, "PATH"))
	{
		if (!(paths = env_get_value(*(settings->m_env), "PATH")))
			return (notes('p', 1, 0, 0));
		if (!(split = ft_strsplit(paths, ':')))
			return (notes('p', 1, 0, 0));
		free_str(&paths);
	}
	if (!(cmd_split = ft_strsplit(full_cmd, ' ')))
		return (notes('p', 1, 0, 0));
	cmd_program_runer(settings, cmd_split, split);
}
