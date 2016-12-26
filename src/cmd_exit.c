/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:44:48 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 22:44:50 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function that check if the user ask for spasific exit number.
** Id he didn't so the program will exit with exit(1);
*/

void	cmd_exit(t_stg *settings, char *full_cmd, char *cmd, char **cmds)
{
	char	**split;
	int		type;

	type = 1;
	split = 0;
	if (!(split = ft_strsplit(full_cmd, ' ')))
		notes('g', 1, 0, 0);
	if (split)
		type = split[1] ? ft_atoi(split[1]) : 1;
	free_settings(settings);
	if (split)
		ft_free_strsplit(&split);
	free_str(&cmd);
	ft_free_strsplit(&cmds);
	exit(type);
}
