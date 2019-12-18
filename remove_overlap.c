/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_overlap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:52:09 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/18 01:54:31 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	check_overlap(int *a, int *b, int i, int j)
{
	if (a[i] == -1 || b[j] == -1)
		return (-1);
	if (i / 2 + a[1] < j / 2 + b[1])
		return (check_overlap(a, b, i + 2, j));
	if (i / 2 + a[1] > j / 2 + b[1])
		return (check_overlap(a, b, i, j + 2));
	if (a[i] + a[0] <= b[j + 1] + b[0] && b[j] + b[0] <= a[i + 1] + a[0])
		return ((b[0] + b[j + 1]) - (a[0] + a[i]) + 1);
	return (check_overlap(a, b, i + 2, j + 2));
}

static int	check_out_of_bounds(int *a, int i, int map_size)
{
	int		ret;

	if (a[i + 2] != -1)
		ret = check_out_of_bounds(a, i + 2, map_size);
	else
		ret = i / 2 + a[1] > map_size ? -1 : 1;
	return (ret > 0 ? a[i + 1] + a[0] < map_size : ret);
}

static int	move_coord(int *a, int diff, int map_size)
{
	int		ret;

	a[0] += diff;
	while ((ret = check_out_of_bounds(a, 2, map_size)) <= 0)
	{
		if (ret == -1)
			return (0);
		a[0] = 0;
		a[1]++;
	}
	return (1);
}

int			remove_overlap(int pieces[27][11], int map_size, int i)
{
	int		j;
	int		ret;

	if (pieces[i][0] == -1)
		return (1);
	pieces[i][0] = 0;
	pieces[i][1] = 0;
	while (1)
	{
		j = 0;
		while (j < i)
		{
			if ((ret = check_overlap(pieces[i], pieces[j++], 2, 2)) == -1)
				continue ;
			if (!move_coord(pieces[i], ret, map_size))
				return (0);
			j = 0;
		}
		if (remove_overlap(pieces, map_size, i + 1))
			return (1);
		if (!move_coord(pieces[i], 1, map_size))
			return (0);
	}
}
