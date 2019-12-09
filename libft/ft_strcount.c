/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:55:37 by aseppala          #+#    #+#             */
/*   Updated: 2019/11/03 13:33:06 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcount(const char *s, char c)
{
	if (*s == 0)
		return (0);
	if (*s != c && (*(s + 1) == c || *(s + 1) == 0))
		return (1 + ft_strcount(++s, c));
	return (ft_strcount(++s, c));
}