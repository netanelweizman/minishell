/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 19:00:42 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 19:00:43 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Define Errors 'errno':
*/

# define E_ENOMEM "Out of memory\n"
# define E_EACCES "Permission denied\n"

# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>

# include "libft/ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"

/*
** Global Variable for 'ctrl+C';
*/

bool	g_full_pwd;

typedef struct	s_stg
{
	char	*my_path;
	char	*last_path;
	char	***m_env;
	char	*polo_test;
	char	*polo_proj;
	bool	free_en;

}				t_stg;

/*
** Hellp Functions
*/

char			*get_cmd(char *full_cmd);
char			*rq(char **str);
void			init_flags(t_stg *settings, int ac, char **flags);
char			*clear_full_cmd(char **full_cmd);

/*
** Env Functions
*/

char			*env_get_value(char **env, char *key);
void			print_env(char **env);
void			export_env(t_stg *settings, char ***m_env, char *key,
	char *value);
int				env_search_key(t_stg *settings, char *key);
void			unset_env(t_stg *settings, char ***m_env, char *key,
	char key_len);
/*
** Main Functions
*/

void			cmd_cd(t_stg *settings, char *full_cmd);
void			second_thread_management(t_stg *settings,
	char *full_cmd, char *cmd);
void			cmd_echo(t_stg *settings, char *full_cmd);
void			cmd_env(t_stg *settings, char *full_cmd, int type);
void			cmd_program(t_stg *settings, char *full_cmd);
void			cmd_exit(t_stg *settings, char *full_cmd, char *cmd,
	char **cmds);
void			cmd_polo(t_stg *settings, char *full_cmd);

/*
** Error(s)
*/

void			notes(char type_cmd, int num_error,
	char **str_to_free, int do_exit);
void			notes_global(int type);
void			notes_cd(int type, char *str);
void			notes_echo(int type);
void			notes_env(int type);
void			notes_program(int type);

/*
** Free Functions
*/

void			free_settings(t_stg *settings);
void			free_str(char **str);

#endif
