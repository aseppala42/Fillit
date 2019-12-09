/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:29:14 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/09 18:17:41 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void adjust_coordinates(int **data, int i)
{
	if (*data[i] == -1)
		return ;
	*data[i] = *data[i] - *data[0];
	adjust_coordinates(data, ++i);
}

static void	set_coordinates(int **data, char **tet, int i)
{
	if (i == 16)
		return ;
	if (tet[i / 4][i % 4] == '#')
	{
		i % 4 < *data[0] ? *data[0] = i % 4 : 0;
		i / 4 < *data[1] ? *data[1] = i / 4 : 0;
	}
	set_coordinates(data, i + 1);
	if (tet[i / 4][i % 4] == '#')
	{
		if (i / 4 != i + 1 / 4 || tet[(i + 1) / 4][(i + 1) % 4] == '.')
			*data[((i / 4) - data[1]) * 2 + 3] = i % 4 - *data[0];
		if (i / 4 != i - 1 / 4 || tet[(i - 1) / 4][(i - 1) % 4] == '.')
			*data[((i / 4) - data[1]) * 2 + 2] = i % 4 - *data[0];
	}
}

static void	set_coordinates(int **data, char **tet)
{
	int		y;
	int		x;
	int		i;

	y = -1;
	x = 0;
	i = 2;
	while (tet[++y][x])
	{
		while (tet[y][x])
		{
			if (tet[y][x] == '#')
			{
				x < *data[0] ? *data[0] = x : 0;
				y < *data[1] ? *data[1] = y : 0;
				data[i] = x;
				if (!(i % 2))
					i++;
			}
		}
		x = 4;
		i++;
	}
	adjust_coordinates(data, 2);
}

static void data_init(int data[27][11])
{
	int		y;
	int		x;

	y = 28;
	x = 12;
	while (y--)
	{
		while (x--)
			data[y][x] = x > 2 ? 3 : -1;
		if (x)
			x = 12;
	}
}
/*
static int	is_error(char tet[5][5])
{
	int		y;
	int		x;

	y = 4;
	x = 4;
	while (y--)
	{
		while (x--)
			if (tet[y][x] != '#')
				if (tet[y][x] != '.')
					return (1);
		x = 4;
	}
	return (0);
}
*/
static int	get_next_tet(int fd, char tet[5][5])
{
	char	*line;
	int		ret;
	int		i;

	i = -1;
	line = 0;
	while (i++ < 5)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (-1);
		if (!ret)
			return (!i ? 0 : -1);
		if (i == 5 && *line != 0)
			return (-1);
		else if (ft_strlen(line) != 4)
			return (-1);
		ft_strcpy(tet[i], line);
		ft_strdel(&line);
	}
	return (1);
}

static int	get_data(fd)
{
	int		data[27][11];
	int		ret;
	int		i;
	char	tet[5][5];

	i = 0;
	data_init(data);
	while ((ret = get_next_tet(fd, tet)))
	{
		if (ret == -1)
			return (1);
		if (is_error(tet))
			return (1);
		if (i > 27)
			return (1);
//		set_coordinates(&data[i++], tet);
	}
	return (0);

	
}

static void	opener(char **av)
{
	int		fd;

	if ((fd = open(*av, O_RDONLY)) == -1)
		ft_putstr("error\n");
	if (get_data(fd))
		ft_putstr("error\n");
	if (close(fd) == -1)
		ft_putstr("error\n");
}

int			main(int ac, char **av)
{
	if (ac == 2)
		opener(++av);
	else
		ft_putstr("usage: ./fillit source_file\n");
//	while (1) {}
	return (0);
}
