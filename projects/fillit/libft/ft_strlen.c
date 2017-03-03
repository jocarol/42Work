/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrau <agrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:07:32 by agrau             #+#    #+#             */
/*   Updated: 2017/01/21 17:34:51 by agrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}