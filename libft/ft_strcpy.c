/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:34:45 by aseppala          #+#    #+#             */
/*   Updated: 2019/11/02 20:45:44 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	if (src == 0)
		return (dst);
	*dst = *src;
	if (*src != 0)
		ft_strcpy(dst + 1, ++src);
	return (dst);
}