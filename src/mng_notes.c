/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_notes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 19:23:58 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 19:24:01 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Free noraml string.
*/

void	free_str(char **str)
{
	free(*str);
	*str = 0;
}

/*
** Free struct 'settings'
*/

void	free_settings(t_stg *settings)
{
	free_str(&(settings->my_path));
	free_str(&(settings->last_path));
	if (settings->free_en)
		ft_free_strsplit(settings->m_env);
	free_str(&(settings->polo_test));
	free_str(&(settings->polo_proj));
}

/*
**	Errors:
**		void	notes(char type_cmd, int num_error, char **free_str,
**					int do_exit);
**				'type_cmd':		g-global, c-cd, e-echo, n-env, p-program;
**				'num_error':	witch error to print?
**				'str_to_free':	0->do not free;
**				'do_exit':		do exit after printing the error;
*/

void	notes(char type_cmd, int num_error, char **str_to_free, int do_exit)
{
	if (type_cmd == 'g')
		notes_global(num_error);
	else if (type_cmd == 'c')
		notes_cd(num_error, 0);
	else if (type_cmd == 'e')
		notes_echo(num_error);
	else if (type_cmd == 'n')
		notes_env(num_error);
	else if (type_cmd == 'p')
		notes_program(num_error);
	if (str_to_free)
		free_str(str_to_free);
	if (do_exit)
		exit(1);
}
