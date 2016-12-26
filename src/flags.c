/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:14:18 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 20:14:19 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_polo(t_stg *settings)
{
	char	*path;

	if (!(path = (char*)malloc(sizeof(char) * 1024)))
		notes('g', 1, 0, 1);
	ft_memset(path, '\0', 1024);
	settings->polo_test = ft_strjoin(getcwd(path, 1023),
		"/str/polo_test.tar.gz");
	settings->polo_proj = ft_strjoin(getcwd(path, 1023),
		"/str/polo_project.tar.gz");
	free_str(&path);
}

void		init_flags(t_stg *settings, int ac, char **flags)
{
	if (ac > 1 && !ft_strcmp(flags[1], "-f"))
		g_full_pwd = 1;
	init_polo(settings);
}
