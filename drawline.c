/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:02 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/19 01:53:37 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int max_width(int *widths, int height)
{
	int max = 0;
	for (int i = 0; i < height; i++)
		if (widths[i] > max)
			max = widths[i];
	return max;
}

double	compute_final_scale(t_map *map, int win_w, int win_h)
{
	int x, y;
	int max_z = -2147483648;
	int min_z = 2147483647;
	int max_w;

	max_w = max_width(map->width, map->height);
	if (map->height > 500 || max_w > 500)
		return 0.3;


	double scale_x = (win_w * 0.45) / max_w;
	double scale_y = (win_h * 0.45) / map->height;

	for (y = 0; y < map->height; y++)
		for (x = 0; x < map->width[y]; x++)
		{
			if (map->points[y][x].z > max_z)
				max_z = map->points[y][x].z;
			if (map->points[y][x].z < min_z)
				min_z = map->points[y][x].z;
		}

	double scale_z;
	if (max_z == min_z)
		scale_z = 9999999;
	else
		scale_z = (win_h * 0.45) / (max_z - min_z);

	double final_scale = scale_x;
	if (scale_y < final_scale)
		final_scale = scale_y;
	if (scale_z < final_scale)
		final_scale = scale_z;

	return final_scale;
}

t_point	cal_new_data(t_map map, int x, int y, double scale)
{
	t_point	res;
	double	cos_angle;
	double	sin_angle;

	cos_angle = 0.8660254;
	sin_angle = 0.5;
	res.x = ((map.points[y][x].x - map.points[y][x].y)
			* cos_angle) * scale;

	res.y = ((map.points[y][x].x + map.points[y][x].y)
			* sin_angle - map.points[y][x].z) * scale;

	res.x += 1000 / 2;
	res.y += 1000 / 2;

	return (res);
}

void	my_pixel_put(t_window *w, int x, int y, int color)
{
	if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
		return ;

	w->pixel[y * 1000 + x] = color;
}


void	draw_line(t_window *w, t_point a, t_point b, int colar)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = b.x - a.x;
	dy = b.y - a.y;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;

	x = a.x;
	y = a.y;

	while (steps >= 0)
	{
		my_pixel_put(w, (int)x, (int)y, colar);
		x += x_inc;
		y += y_inc;
		steps--;
	}
}


void	draw(t_window *window, t_map map)
{
	int		x;
	int		y;
	t_point	a;
	t_point	b;
	double	scale;

	y = 0;
	x = 0;
	scale = compute_final_scale(&map, 1000, 1000);
	while (y < map.height)
	{
		x = 0;
		while (x < map.width[y])
		{
			a = cal_new_data(map, x, y, scale);
			if (x < map.width[y] - 1)
			{
				b = cal_new_data(map, x + 1, y, scale);
				draw_line(window, a, b, map.points[y][x].color);
			}
			if (y < map.height - 1 && map.width[y + 1])
			{
				b = cal_new_data(map, x, y + 1, scale);
				draw_line(window, a, b, map.points[y][x].color);
			}
			x++;
		}
		y++;
	}

}
