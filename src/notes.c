/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 19:30:35 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 19:30:37 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	notes_global(int type)
{
	if (type == 1)
		ft_printf("%s", E_ENOMEM);
}

void	notes_cd(int type, char *str)
{
	if (type == 1)
		ft_printf("%s", E_ENOMEM);
	else if (type == 2)
		ft_printf("%s %s\n", "cd: no such file or directory: ", str);
	else if (type == 3)
		ft_printf("%s %s\n", "cd: string not in pwd: ", str);
	else if (type == 4)
		ft_printf("%s %s\n", "zsh: event not found: ", str);
	else if (type == 5)
		ft_printf("%s %s\n", "zsh: no matches found: ", str);
	else if (type == 6)
		ft_printf("%s", E_EACCES);
}

void	notes_echo(int type)
{
	if (type == 1)
		ft_printf("%s", E_ENOMEM);
}

void	notes_env(int type)
{
	if (type == 1)
		ft_printf("%s", E_ENOMEM);
}

void	notes_program(int type)
{
	if (type == 1)
		ft_printf("%s", E_ENOMEM);
}
