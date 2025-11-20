/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:16:20 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 12:11:46 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:16:20 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/18 21:06:43 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "fdf.h"

int	fill_data(t_map *map, int width, char **data, int y)
{
	int	x;
	int	i;

	map->points[y] = malloc(sizeof(t_point) * width);
	if (!map->points[y])
		return (-1);
	x = 0;
	while (x < width)
	{
		map->points[y][x].x = x;
		map->points[y][x].y = y;
		map->points[y][x].z = ft_atoi(data[x]);
		i = 0;
		while (data[x][i] && data[x][i] != ',')
			i++;
		if (data[x][i] == ',')
			map->points[y][x].color = ft_atohex(data[x] + i + 1);
		else
			map->points[y][x].color = ft_atohex("0xFFFFFF");
		x++;
	}
	return (0);
}

void	split_free(char **splited)
{
	int	i;

	if (!splited)
		return ;
	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

int	process_line(t_map *map, char *line, int y)
{
	char	**splited;
	int		width;

	splited = ft_split(line, ' ');
	if (!splited)
	{
		get_next_line(-1);
		return (0);
	}
	width = 0;
	while (splited[width])
		width++;
	map->width[y] = width;
	if (fill_data(map, width, splited, y) == -1)
	{
		split_free(splited);
		return (0);
	}
	split_free(splited);
	return (1);
}

t_map	take_points(t_map map, int fd, int *flag)
{
	char	*line;
	int		y;

	y = 0;
	*flag = 1;
	while (y < map.height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			*flag = 0;
			break ;
		}
		if (!process_line(&map, line, y))
		{
			free(line);
			*flag = 0;
			break ;
		}
		free(line);
		y++;
	}
	return (map);
}

t_map	read_map_allocte(char **av)
{
	t_map	map;

	map.height = give_height(av);
	map.points = malloc(sizeof(t_point *) * map.height);
	if (!map.points)
		write_error();
	map.width = malloc(sizeof(int) * map.height);
	if (!map.width)
	{
		free(map.points);
		write_error();
	}
	return (map);
}

t_map	read_map(char **av)
{
	int		fd;
	t_map	map;
	int		flag;

	map = read_map_allocte(av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free_map(&map);
		write_error();
	}
	map = take_points(map, fd, &flag);
	close(fd);
	if (flag == 0)
	{
		free_map(&map);
		write_error();
	}
	return (map);
}
