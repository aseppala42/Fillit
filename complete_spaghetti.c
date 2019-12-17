#include "fillit.h"

int		check_overlap(int *a, int *b, int i, int j)
{
	if (a[i] == -1 || b[j] == -1)
		return (-1);
	if (i / 2 + a[1] != j / 2 + b[1])
		return (i / 2 + a[1] < j / 2 + b[1] ? check_overlap(a, b, i + 2, j) :
				check_overlap(a, b, i, j + 2));
	if (a[i] + a[0] <= b[j + 1] + b[0] && b[j] + b[0] <= a[i + 1] + a[0])
		return (b[j + 1]);
	return (check_overlap(a, b, i + 2, j + 2));
}

int		check_out_of_bounds(int *a, int i, int map_size)
{
	int		ret;

	if (a[i + 2] != -1)
		ret = check_out_of_bounds(a, i + 2, map_size);
	else
		ret = i / 2 + a[1] > map_size ? -1 : 1;
	if (ret <= 0)
		return (ret);
	else
		return (a[i + 1] + a[0] < map_size);
}

int		move_coord(int *a, int diff, int map_size)
{
	int			ret;

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

int		remove_overlap(int pieces[27][11], int map_size, int i)
{
	int		j;
	int		ret;

	if (pieces[i][0] == 3 && pieces[i][1] == 3)
		return (1);
	pieces[i][0] = 0;
	pieces[i][1] = 0;
	j = 0;
	while (1)
	{
		while (j < i)
		{
			if ((ret = check_overlap(pieces[i], pieces[j++], 2, 2)) == -1)
				continue ;
			if (!move_coord(pieces[i], ret + 1, map_size))
				return (0);
			j = 0;
		}
		if (remove_overlap(pieces, map_size, i + 1))
			return (1);
		if (!move_coord(pieces[i], 1, map_size))
			return (0);
	}
}

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

int		is_error(char tet[5][5])
{
	int			num_filled;
	int			i;
	int			j;

	num_filled = 0;
	i = -1;
	while (tet[++i][0])
	{
		j = -1;
		while (tet[i][++j])
		{
			if (tet[i][j] == '#')
			{
				if (num_filled && (!i || tet[i - 1][j] != '#') && (!j || tet[i][j - 1] != '#')
						&& (j == 3 || tet[i][j + 1] != '#'))
					return (0);
				num_filled++;
			}
			else if (tet[i][j] != '.')
				return (0);
		}
	}
	return (num_filled == 4);
}

static void data_init(int data[27][11])
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
			return (i == 4 ? 0 : -1);
		if (i == 4 && *line != 0)
			return (-1);
		if (i != 4 && ft_strlen(line) != 4)
			return (-1);
		ft_strcpy(tet[i], line);
		ft_strdel(&line);
	}
	return (1);
}

static int	get_data(int fd, int data[27][11])
{
	int		ret;
	int		temp; //
	int		i;
	char	tet[5][5];

	i = 0;
	data_init(data);
	tet[4][0] = 0;
	while (1)
	{
		if ((ret = get_next_tet(fd, tet)) == -1)
			return (1);
		if (!is_error(tet))
			return (1);
		if (i > 26)
			return (1);
		set_coordinates(data[i++], tet, 0);
		temp = 0;//
		while (data[i - 1][temp] != -1)//
			printf("%d", data[i - 1][temp++]);//
		printf("\n");//
		if (ret == 0)
			return (0);
	}
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

	map_s = 4;
	if (ac == 2)
		opener(++av, data);
	else
		ft_putstr("usage: ./fillit source_file\n");
	while (map_s++)
		if (remove_overlap(data, map_s, 0) == 1)
			break ;
//	while (1) {}
	return (0);
}
