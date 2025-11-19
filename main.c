/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:16:25 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/19 16:12:05 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	if (!map || !map->points)
		return ;

	while (y < map->height)
	{
		if (map->points[y])
		{
			free(map->points[y]);
		}
		y++;
	}
	free(map->width);
	free(map->points);
	map->points = NULL;
	map->height = 0;
	map->width = 0;
}

int	main(int ac, char **av)
{
	t_map	map;

	file_type(ac, av);
	map = read_map(av);
	get_next_line(-1);
	window(&map);
	free_map(&map);
}
