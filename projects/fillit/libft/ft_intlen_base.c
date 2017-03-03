/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrau <agrau@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:28:32 by agrau             #+#    #+#             */
/*   Updated: 2017/01/22 08:58:58 by agrau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen_base(int nb, int base)
{
	int len;

	if (nb < 0)
		nb = -nb;
	len = 1;
	while ((nb /= base) > 0)
		len++;
	return (len);
}