/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:16:20 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/17 15:34:20 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "fdf.h"

void	write_error(void)
{
	write(2, "ERROR\n", 6);
	exit(-1);
}

void	file_type(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 2)
		write_error();
	else
	{
		while (av[1][i])
			i++;
		if (i < 5)
			write_error();
		if (av[1][i - 1] != 'f' || av[1][i - 2] != 'd'
				|| av[1][i - 3] != 'f' || av[1][i - 4] != '.')
			write_error();
	}
}

int	give_height(char **av)
{
	int		height;
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		write_error();
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (height);
}

int	fill_data(t_map *map, int width, char **data, int *y)
{
	int	x;
	int	i;

	x = 0;
	(*map).points[*y] = malloc(sizeof(t_point) * width);
	if ((*map).points[*y] == NULL)
		return (-1);
	while (x < width)
	{
		(*map).points[*y][x].x = x;
		(*map).points[*y][x].y = *y;
		(*map).points[*y][x].z = ft_atoi(data[x]);
		i = 0;
		while (data[x][i] && data[x][i] != ',')
			i++;
		if (data[x][i] == ',')
		{
			i++;
			(*map).points[*y][x].color = ft_atohex(data[x] + i);
		}
		else
			(*map).points[*y][x].color = ft_atohex("0xFFFFFF");
		x++;
	}
	return (0);
}

t_map	take_points(t_map map, int fd, int *flag)
{
	char	*line;
	int		y;
	char	**splited;
	int		x;
	int		i;

	x = 0;
	map.width = 0;
	y = 0;
	while (y < map.height)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			*flag = 0;
			return (map);
		}
		splited = ft_split(line, ' ');
		free(line);
		if (splited == NULL)
		{
			*flag = 0;
			return (map);
		}
		map.width = 0;
		while (splited[map.width] != NULL)
			map.width++;
		if (fill_data(&map, map.width, splited, &y) == -1)
		{
			free_all(splited, map.width);
			*flag = 0;
			return (map);
		}
		i = 0;
		while (i < map.width)
			free(splited[i++]);
		free(splited);
		x++;
		y++;
	}
	return (map);
}

t_map	read_map(char **av)
{
	int		fd;
	t_map	map;
	int		flag;
	int		i;

	i = 0;
	flag = 1;
	map.height = give_height(av);
	map.points = malloc(sizeof(t_point *) * map.height);
	if (map.points == NULL)
		write_error();
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		free(map.points);
		write_error();
	}
	if (map.points == NULL)
		write_error();
	map = take_points(map, fd, &flag);
	if (flag == 0)
	{
		while (i < map.height)
			free(map.points[i++]);
		free(map.points);
	}
	close(fd);
	return (map);
}	
