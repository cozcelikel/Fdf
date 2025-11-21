/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:16:25 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/21 10:50:51 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "mlx.h"

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

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	if (map->points)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->points[y])
				free(map->points[y]);
			y++;
		}
		free(map->points);
	}
	if (map->width)
		free(map->width);
}

int	main(int ac, char **av)
{
	t_map	map;
	int		s_len;

	s_len = 1500 * 32;
	file_type(ac, av);
	map = read_map(av);
	window(&map, s_len, 32, 0);
}
