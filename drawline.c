/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:02 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/21 10:46:29 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include <math.h>
#include <stdlib.h>

int	max_width(int *widths, int height)
{
	int	max;
	int	i;

	i = 0;
	max = 0;
	while (i < height)
	{
		if (widths[i] > max)
			max = widths[i];
		i++;
	}
	return (max);
}

double	compute_final_scale(t_map *map, int win_w, int win_h, int z_range)
{
	int		max_w;
	t_scale	scale;

	max_w = max_width(map->width, map->height);
	scale.x = (win_w * 0.45) / max_w;
	scale.y = (win_h * 0.45) / map->height;
	scale.f = scale.x;
	if (scale.x < 0.3 || scale.y < 0.3)
	{
		if (scale.y < scale.x)
			return (scale.y);
		else
			return (scale.x);
	}
	if (map->height > 500 || max_w > 500)
		return (0.3);
	if (z_range == 0)
		scale.z = 9999999;
	else
		scale.z = (win_h * 0.45) / z_range;
	if (scale.y < scale.f)
		scale.f = scale.y;
	if (scale.z < scale.f)
		scale.f = scale.z;
	return (scale.f);
}

t_point	cal_new_data(t_map map, int x, int y, double scale)
{
	t_point	res;
	double	cos_angle;
	double	sin_angle;

	cos_angle = 0.860254;
	sin_angle = 0.5;
	res.x = ((map.points[y][x].x - map.points[y][x].y)
			* cos_angle) * scale;
	res.y = ((map.points[y][x].x + map.points[y][x].y)
			* sin_angle - map.points[y][x].z) * scale;
	res.x += 750;
	res.y += 700;
	return (res);
}

void	draw_line(t_window *w, t_point a, t_point b, int colar)
{
	int		dx;
	int		dy;
	int		steps;
	t_line	line;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	line.x_inc = dx / (float)steps;
	line.y_inc = dy / (float)steps;
	line.x = a.x;
	line.y = a.y;
	while (steps >= 0)
	{
		my_pixel_put(w, (int)line.x, (int)line.y, colar);
		line.x += line.x_inc;
		line.y += line.y_inc;
		steps--;
	}
}

void	draw(t_window *window, t_map map, double scale, int y)
{
	int		x;
	t_point	a;
	t_point	b;

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
			if (y < map.height - 1 && x < map.width[y + 1])
			{
				b = cal_new_data(map, x, y + 1, scale);
				draw_line(window, a, b, map.points[y][x].color);
			}
			x++;
		}
		y++;
	}
}
