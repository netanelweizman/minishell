/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 12:50:52 by nweizman          #+#    #+#             */
/*   Updated: 2016/10/21 12:50:53 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		free_list_file(t_list **files)
{
	int		num;
	int		i;
	t_file	*settings_file;
	t_list	*point;

	num = 0;
	point = *files;
	while (point)
	{
		settings_file = point->content;
		i = STATUS;
		if (i <= 0)
		{
			ft_free_node(files, num);
			return (i);
		}
		num++;
		point = point->next;
	}
	return (0);
}

int		read_line(t_file *settings_file, char **line)
{
	if ((STR[I] == 0 && I < BUFF_SIZE) || I == BUFF_SIZE)
	{
		settings_file->index = 0;
		ft_memset(settings_file->str, '\0', BUFF_SIZE);
		STATUS = read(settings_file->id, STR, BUFF_SIZE);
		if (STATUS == 0)
		{
			if (ft_strlen(*line) == 0)
			{
				*line = 0;
				return (0);
			}
			return (1);
		}
		return (STATUS);
	}
	return (1);
}

int		read_management(t_list **root, t_file *settings_file,
	char **line, t_array *darr)
{
	while (1)
	{
		if (read_line(settings_file, line) <= 0)
			return (free_list_file(root));
		while (STR[I] != '\n' && STR[I] != '\0' && I < BUFF_SIZE)
			*line = ft_insert_dynamic_arr(darr, STR[I++]);
		if (STR[I] == '\n' || STATUS == 0)
		{
			I++;
			return (1);
		}
		if (STATUS > 0 && STATUS < BUFF_SIZE)
		{
			I = (I == STATUS - 1) ? 0 : I;
			STR[0] = (I == 0) ? 0 : STR[0];
			return (1);
		}
	}
	return (1);
}

void	set_settings(t_file *settings_file, int fd)
{
	settings_file->id = fd;
	settings_file->index = 0;
	settings_file->status = 0;
	ft_memset(settings_file->str, '\0', BUFF_SIZE);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*files;
	t_list			*temp;
	t_file			*settings_file;
	t_array			darr;

	temp = files;
	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	*line = ft_init_dynamic_arr(&darr, 2);
	ft_memset(darr.arr, '\0', 2);
	while (temp)
	{
		settings_file = temp->content;
		if (settings_file->id == fd)
			return (read_management(&files, settings_file, line, &darr));
		temp = temp->next;
	}
	if (!(settings_file = (t_file*)malloc(sizeof(t_file))))
		return (0);
	ft_list_push_front(&files, settings_file, sizeof(t_file));
	free(settings_file);
	settings_file = files->content;
	set_settings(settings_file, fd);
	return (read_management(&files, settings_file, line, &darr));
}
