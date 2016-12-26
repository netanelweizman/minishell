/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:45:05 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 22:45:06 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function that print the all env list;
*/

void		print_env(char **env)
{
	int index;

	index = -1;
	while (env[++index])
		ft_printf("%s\n", env[index]);
}

/*
** Function that create list of key to delete.
** Te function send etch key that exsit in env to 'unset_env'.
*/

static void	cmd_env_build_unset(t_stg *settings, char *full_cmd)
{
	char	**split;
	int		index;

	index = -1;
	split = ft_strsplit(full_cmd, ' ');
	while (split[++index])
	{
		if (env_search_key(settings, split[index]))
			unset_env(settings, settings->m_env, split[index],
				ft_strlen(split[index]));
	}
	ft_free_strsplit(&split);
}

/*
** Function that create 'key' and 'value' and send it to 'export_env';
** This Function support multipal keys and valus;
** Two formats are avaliable: 'FOO=name' or 'FOO name'
*/

static void	cmd_env_build_export(t_stg *settings, char *full_cmd, int index)
{
	char	**sp_one;
	char	**sp_two;

	sp_two = 0;
	if (!(sp_one = ft_strsplit(full_cmd, ' ')))
		return (notes('n', 1, 0, 0));
	while (sp_one[++index])
	{
		if (ft_strchr(sp_one[index], '='))
		{
			sp_two = ft_strsplit(sp_one[index], '=');
			export_env(settings, settings->m_env, rq(&(sp_two[0])),
				rq(&(sp_two[1])));
			ft_free_strsplit(&sp_two);
			continue ;
		}
		if (sp_one[index + 1] && !ft_strchr(sp_one[index], '='))
		{
			export_env(settings, settings->m_env, rq(&(sp_one[index])),
				rq(&(sp_one[index + 1])));
			index++;
		}
	}
	ft_free_strsplit(&sp_one);
}

void		cmd_env(t_stg *settings, char *full_cmd, int type)
{
	(void)full_cmd;
	if (type == 1)
		print_env(*(settings->m_env));
	else if (type == 2)
		cmd_env_build_export(settings, full_cmd, 0);
	else if (type == 3)
		cmd_env_build_unset(settings, full_cmd);
}
