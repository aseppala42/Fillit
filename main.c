/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:50:12 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/18 02:03:29 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	error(void)
{
	ft_putstr("error\n");
	exit(1);
}

static int	map_size_opt(int data[27][11])
{
	int		map_size;
	int		i;

	map_size = 4;
	i = 1;
	while (data[i][0] != -1)
		i++;
	while (map_size * map_size < i * 4)
		map_size++;
	return (map_size);
}

static void	opener(char **av, int data[27][11])
{
	int		fd;

	if ((fd = open(*av, O_RDONLY)) == -1)
		error();
	if (get_data(fd, data))
		error();
	if (close(fd) == -1)
		error();
}

int			main(int ac, char **av)
{
	int		data[27][11];
	int		map_s;
	char	*map;

	if (ac == 2)
		opener(++av, data);
	else
	{
		ft_putstr("usage: ./fillit source_file\n");
		return (0);
	}
	map_s = map_size_opt(data);
	while (map_s++)
		if (remove_overlap(data, map_s, 0) == 1)
			break ;
	map = fill_it(data, map_s);
	if (map)
		write(1, map, map_s * (map_s + 1));
	ft_strdel(&map);
	return (0);
}
