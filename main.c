/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:50:12 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/18 00:54:02 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
		ft_putstr("error\n");
	else if (get_data(fd, data))
		ft_putstr("error\n");
	else if (close(fd) == -1)
		ft_putstr("error\n");
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
	write(1, "\n", 1); //
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 11; j++)
			ft_putnbr(data[i][j]);
		write(1, "\n", 1);
	}
	map = fill_it(data, map_s);
	if (map)
		write(1, map, map_s * (map_s + 1));
	ft_strdel(&map);

//	while (1) {}
	return (0);
}
