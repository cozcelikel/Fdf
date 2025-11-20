/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 06:01:47 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 16:14:04 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	compute_z_range(t_map *map)
{
	int	x;
	int	y;
	int	max_z;
	int	min_z;

	max_z = -2147483648;
	min_z = 2147483647;
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

void	my_pixel_put(t_window *w, int x, int y, int color)
{
	if (x < 0 || x >= 1500 || y < 0 || y >= 1500)
		return ;
	w->pixel[y * 1500 + x] = color;
}
