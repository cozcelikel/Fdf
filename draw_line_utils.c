/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 06:01:47 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 14:31:54 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int compute_z_range(t_map *map)
{
	int x, y;
	int max_z = -2147483648;
	int min_z = 2147483647;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width[y])
		{
			if (map->points[y][x].z > max_z)
				max_z = map->points[y][x].z;
			if (map->points[y][x].z < min_z)
				min_z = map->points[y][x].z;
			x++;
		}
		y++;
	}

	return (max_z - min_z);
}
