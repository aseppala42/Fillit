/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseppala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 10:27:42 by aseppala          #+#    #+#             */
/*   Updated: 2019/12/17 21:24:25 by aseppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

int		get_data(int fd, int data[27][11]);
int		remove_overlap(int pieces[27][11], int map_size, int i);
char	*fill_it(int data[27][11], int map_size);

#endif
