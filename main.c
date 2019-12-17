/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:50:12 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/17 21:23:38 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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

	map_s = 4;
	if (ac == 2)
		opener(++av, data);
	else
		ft_putstr("usage: ./fillit source_file\n");
	while (map_s++)
		if (remove_overlap(data, map_s, 0) == 1)
			break ;
	map = fill_it(data, map_s);
	if (map)
		write(1, map, map_s * (map_s + 1));
	ft_strdel(&map);
//	while (1) {}
	return (0);
}
