/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:14:18 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/21 20:14:19 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** This function do the 'cd' Action.
** This function update the new path in settings.
*/

static void	cmd_cd_update_mypath(t_stg *settings, char *path)
{
	if (ft_strcmp(path, "-"))
	{
		if (access(path, R_OK) == -1)
			return (notes('c', 6, &path, 0));
		chdir(path);
		free_str(&path);
		if (!(path = (char*)malloc(sizeof(char) * 1024)))
			return (notes('c', 1, 0, 0));
		ft_memset(path, '\0', 1024);
		free_str(&(settings->last_path));
		if (!(settings->last_path = ft_strdup(settings->my_path)))
			return (notes('c', 1, 0, 0));
		free_str(&(settings->my_path));
		settings->my_path = getcwd(path, 1023);
	}
	else
	{
		free_str(&path);
		path = settings->last_path;
		settings->last_path = settings->my_path;
		settings->my_path = path;
		chdir(path);
	}
}

/*
** Function that find and retrun the 'Home' path.
*/

static char	*cmd_cd_create_path(t_stg *settings)
{
	char	*path;

	if (!(path = env_get_value(*(settings->m_env), "HOME")))
	{
		notes('c', 1, 0, 0);
		return (0);
	}
	return (path);
}

/*
** Checks if the path that the user give as is valide and also have
**			a valide access.
*/

static char	*cmd_cd_validate_access(t_stg *settings, char **split)
{
	struct stat	st;
	char		*path;
	char		*tmp;

	if (split[1][0] == '~')
	{
		tmp = cmd_cd_create_path(settings);
		path = ft_strjoin(tmp, &split[1][1]);
		free_str(&tmp);
	}
	else
		path = ft_strdup(split[1]);
	if (stat(path, &st) == -1 && ft_strcmp(path, "-"))
	{
		notes_cd(2, path);
		free_str(&path);
	}
	ft_free_strsplit(&split);
	return (path);
}

/*
** This functions check for some errors: ! ? etc..
** If the user give as a path - we jest make sure that it
** valid path witg: 'cmd_cd_validate_access';
** Else we create the 'Home' path with: 'cmd_cd_create_path';
** This function return the new path address.
*/

static char	*cmd_cd_validate(t_stg *settings, char **split, size_t len)
{
	int		err;

	err = 0;
	if (len > 2)
		err = 3;
	else if (len == 2 && split[1][0] == '!' && split[1][1])
	{
		notes_cd(4, split[1] + 1);
		ft_free_strsplit(&split);
		return (0);
	}
	else if (len == 2 && split[1][0] == '?')
		err = 5;
	if (err > 0 && err != 4)
	{
		notes_cd(err, split[1]);
		ft_free_strsplit(&split);
		return (0);
	}
	if (len == 2)
		return (cmd_cd_validate_access(settings, split));
	ft_free_strsplit(&split);
	return (cmd_cd_create_path(settings));
}

/*
** The all 'cd' Option to include:
** 		cd -> absolute path; 		["/path"]
** 		cd -> relative path; 		["/path"]
** 		cd -> user's home folder	["" or "/"]
** 		cd -> folder use before 	["~"]
** 		cd -> absolute path; 		["~/path"]
**
** 'cmd_cd_validate' will exit(1) and free if not validate.
*/

void		cmd_cd(t_stg *settings, char *full_cmd)
{
	char	**split;
	char	*path;
	size_t	len;

	if (!(split = ft_strsplit(full_cmd, ' ')))
		notes('c', 1, 0, 0);
	len = ft_strsplit_len(split);
	if (len > 1 && !ft_strcmp(split[1], "--"))
	{
		split[1][0] = '~';
		split[1][1] = '\0';
	}
	if (!(path = cmd_cd_validate(settings, split, len)))
		return ;
	cmd_cd_update_mypath(settings, path);
}
