/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nweizman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 14:38:34 by nweizman          #+#    #+#             */
/*   Updated: 2016/10/25 14:38:36 by nweizman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_to_lower(char *str)
{
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}
