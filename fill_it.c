/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:59:43 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/17 23:50:14 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	init_fillit(char *map, int map_size, int i)
{
	if (i == map_size * (map_size + 1))
		return ;
	if (!((i + 1) % (map_size + 1)))
		map[i] = '\n';
	else
		map[i] = '.';
	init_fillit(map, map_size, i + 1);
}

char		*fill_it(int data[27][11], int map_size)
{
	char	*map;
	int		i;
	int		j;

	i = 0;
	if (!(map = ft_strnew(map_size * (map_size + 1))))
		return (0);
	init_fillit(map, map_size, 0);
	while (data[i][0] != -1)
	{
		j = 2;
		while (data[i][j] != -1)
		{
			while (data[i][j] <= data[i][j + 1])
			{
				map[data[i][1] * (map_size + 1) +
					data[i][0] + data[i][j]] = 'A' + i;
				data[i][j]++;
			}
			data[i][1]++;
			j = j + 2;
		}
		i++;
	}
	return (map);
}
