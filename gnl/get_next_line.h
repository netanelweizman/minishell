/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 12:50:57 by nweizman          #+#    #+#             */
/*   Updated: 2016/10/26 10:31:33 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# define I settings_file->index
# define STR settings_file->str
# define STATUS settings_file->status
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "../libft/libft.h"

typedef struct	s_file
{
	int		id;
	char	str[BUFF_SIZE];
	int		index;
	int		status;

}				t_file;

int				get_next_line(const int fd, char **line);

#endif
