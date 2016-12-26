/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 16:21:07 by nweizman          #+#    #+#             */
/*   Updated: 2016/12/22 16:21:08 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function that return 1 if key exist;
** Else retrun 0;
*/

int		env_search_key(t_stg *settings, char *key)
{
	char	**t_env;
	int		index;
	int		len;

	t_env = *(settings->m_env);
	index = -1;
	len = ft_strlen(key);
	while (t_env[++index])
	{
		if (!ft_strncmp(t_env[index], key, len))
			return (1);
	}
	return (0);
}

/*
** Function that take a key and return a new string of the value for this key.
** If the key is not exist the function return 0;
*/

char	*env_get_value(char **env, char *key)
{
	int		i;
	int		len;
	char	*value;

	i = -1;
	len = ft_strlen(key);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, len))
			break ;
	}
	if (!env[i])
		return (0);
	if (!(value = ft_strdup(&env[i][len + 1])))
	{
		notes('g', 1, 0, 0);
		return (0);
	}
	return (value);
}

/*
** Function that update a value for exist key.
*/

void	update_env(t_stg *settings, char ***m_env, char *key, char *value)
{
	char	**tmp;
	int		index;
	int		len;
	char	*v_t;

	index = -1;
	tmp = *m_env;
	len = ft_strlen(key);
	while (tmp[++index])
		if (!(ft_strncmp(tmp[index], key, len)))
			break ;
	if (settings->free_en)
		free_str(&tmp[index]);
	if (!(v_t = ft_strjoin("=", value)))
		return (notes('g', 1, 0, 0));
	if (!(tmp[index] = ft_strjoin(key, v_t)))
		return (notes('g', 1, 0, 0));
	free_str(&v_t);
}

/*
** Function that add a new env to the main env
*/

void	export_env(t_stg *settings, char ***m_env, char *key, char *value)
{
	char	**new_env;
	int		env_len;
	int		index;
	char	**tmp;
	char	*v_t;

	if (env_search_key(settings, key))
		return (update_env(settings, m_env, key, value));
	index = -1;
	tmp = *m_env;
	env_len = ft_strsplit_len(*m_env);
	new_env = (char**)malloc(sizeof(char*) * (env_len + 2));
	while (++index < env_len)
		new_env[index] = ft_strdup(tmp[index]);
	if (!(v_t = ft_strjoin("=", value)))
		return (notes('g', 1, 0, 0));
	if (!(new_env[index] = ft_strjoin(key, v_t)))
		notes('g', 1, 0, 0);
	free_str(&v_t);
	new_env[++index] = 0;
	if (settings->free_en)
		ft_free_strsplit(m_env);
	*m_env = new_env;
	settings->free_en = 1;
}

/*
** Function that remove the 'key' from the main env list;
*/

void	unset_env(t_stg *settings, char ***m_env, char *key, char key_len)
{
	char	**new_env;
	int		env_len;
	int		index;
	int		j;
	char	**tmp;

	index = -1;
	j = -1;
	tmp = *m_env;
	env_len = ft_strsplit_len(*m_env);
	new_env = (char**)malloc(sizeof(char*) * env_len);
	while (++index < env_len)
		if (ft_strncmp(key, tmp[index], key_len))
			new_env[++j] = ft_strdup(tmp[index]);
	new_env[++j] = 0;
	if (settings->free_en)
		ft_free_strsplit(m_env);
	*m_env = new_env;
	settings->free_en = 1;
}
