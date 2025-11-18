/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:02 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/18 22:03:26 by cozcelik         ###   ########.fr       */
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

double cal_scale(t_map map, double cos, double sin)
{
	double	scale_x;
	double	scale_y;
	double	diag;
	int max;

	max = max_width(map.width, map.height);
	diag = (double)map.height + (double)max;
	scale_x = diag * cos;
	scale_y = diag * sin;
	scale_x = 600 / scale_x;
	scale_y = 600 / scale_y;
	if (scale_x >= scale_y)
		scale_x = scale_y;
	scale_x = scale_x * 0.9;
	return (scale_x);
}

t_point cal_new_data(t_map map, int x, int y)
{
	t_point res;
	double cos_angle = 0.8660254;
	double sin_angle = 0.5;
	double scale;
	
	scale = cal_scale(map, cos_angle, sin_angle);

	res.x = ((map.points[y][x].x - map.points[y][x].y) * cos_angle) * scale + 400;
	res.y = ((map.points[y][x].x + map.points[y][x].y) * sin_angle - map.points[y][x].z ) * scale + 400;

	return res;
}
void my_pixel_put(t_window *w, int x, int y, int color)
{
	if (x < 0 || x >= 800 || y < 0 || y >= 800)
		return;
	
	w->pixel[y * 800 + x] = color;
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

	y = 0;
	x = 0;

	while (y < map.height)
	{
		x = 0;
		while (x < map.width[y])
		{
			a = cal_new_data(map, x, y);
			if (x < map.width[y] - 1)
			{
				b = cal_new_data(map, x + 1, y);
				draw_line(window, a, b, map.points[y][x].color);
			}
			if (y < map.height - 1 && map.width[y + 1])
			{
				b = cal_new_data(map, x, y + 1);
				draw_line(window, a, b, map.points[y][x].color);
			}
			x++;
		}
		y++;
	}

}
