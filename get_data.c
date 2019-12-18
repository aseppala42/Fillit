/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:48:04 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/18 02:59:03 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	set_coordinates(int data[11], char tet[5][5], int i)
{
	if (i == 16)
		return ;
	if (tet[i / 4][i % 4] == '#')
	{
		i % 4 < data[0] ? data[0] = i % 4 : 0;
		i / 4 < data[1] ? data[1] = i / 4 : 0;
	}
	set_coordinates(data, tet, i + 1);
	if (tet[i / 4][i % 4] == '#')
	{
		if (i / 4 != (i + 1) / 4 || tet[(i + 1) / 4][(i + 1) % 4] == '.')
			data[((i / 4) - data[1]) * 2 + 3] = i % 4 - data[0];
		if (!i || i / 4 != (i - 1) / 4 || tet[(i - 1) / 4][(i - 1) % 4] == '.')
			data[((i / 4) - data[1]) * 2 + 2] = i % 4 - data[0];
	}
}

static int	is_error(char tet[5][5], int num_filled, int num_con, int i)
{
	if (num_filled > 4)
		return (0);
	if (i == 16)
		return (num_con > 5);
	if (tet[i / 4][i % 4] == '#')
	{
		num_filled++;
		num_con += i / 4 ? tet[i / 4 - 1][i % 4] == '#' : 0;
		num_con += i / 4 < 3 ? tet[i / 4 + 1][i % 4] == '#' : 0;
		num_con += i % 4 ? tet[i / 4][i % 4 - 1] == '#' : 0;
		num_con += i % 4 < 3 ? tet[i / 4][i % 4 + 1] == '#' : 0;
	}
	else if (tet[1 / 4][i % 4] != '.')
		return (0);
	return (is_error(tet, num_filled, num_con, i + 1));
}

static void	data_init(int data[27][11])
{
	int		y;
	int		x;

	y = 27;
	x = 11;
	while (y--)
	{
		while (x--)
			data[y][x] = x < 2 ? 3 : -1;
		x = 11;
	}
}

static int	get_next_tet(int fd, char tet[5][5])
{
	char	*line;
	int		ret;
	int		i;

	i = -1;
	line = 0;
	while (++i < 5)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (-1);
		if (!ret)
		{
			ft_strdel(&line);
			return (i == 4 ? 0 : -1);
		}
		if (i == 4 && *line != 0)
			return (-1);
		if (i != 4 && ft_strlen(line) != 4)
			return (-1);
		ft_strcpy(tet[i], line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (1);
}

int			get_data(int fd, int data[27][11])
{
	int		ret;
	int		i;
	char	tet[5][5];

	i = 0;
	data_init(data);
	tet[4][0] = 0;
	while (1)
	{
		if ((ret = get_next_tet(fd, tet)) == -1)
			return (1);
		if (!is_error(tet, 0, 0, 0))
			return (1);
		if (i > 26)
			return (1);
		set_coordinates(data[i++], tet, 0);
		if (ret == 0)
		{
			data[i][0] = -1;
			return (0);
		}
	}
}
