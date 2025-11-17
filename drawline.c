/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:02 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/17 21:11:13 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

t_point cal_new_data(t_map map, int x, int y)
{
    t_point res;
    double cos_angle = 0.8660254; // cos(30°)
    double sin_angle = 0.5;       // sin(30°)
    double scale = 20.0;
    int offset_x = 400;
    int offset_y = 400;

    res.x = ((map.points[y][x].x - map.points[y][x].y) * cos_angle) * scale + offset_x;
    res.y = ((map.points[y][x].x + map.points[y][x].y) * sin_angle - map.points[y][x].z) * scale + offset_y;

    return res;
}
void my_pixel_put(t_window *w, int x, int y, int color)
{
    // Ekran boyutu sabit 800x800
    if (x < 0 || x >= 800 || y < 0 || y >= 800)
        return;
    
    w->pixel[y * 800 + x ] = color;
}

/*
void draw_line(t_window *w, t_point a, t_point b)
{
	int	dx = abs(b.x - a.x);
	int	dy = abs(b.y - a.y);
	int	sx = (a.x < b.x) ? 1 : -1;
	int	sy = (a.y < b.y) ? 1 : -1;
	int	err = dx - dy;
	int	e2;

	while (1)
	{
		my_pixel_put(w, a.x, a.y, 0xFFFFFF);

		if (a.x == b.x && a.y == b.y)
			break;

		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			a.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			a.y += sy;
		}
	}
}
*/

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
		while (x < map.width)
		{
			a = cal_new_data(map, x, y);
			if (x < map.width - 1)
			{
				b = cal_new_data(map, x + 1, y);
				draw_line(window, a, b);
			}
			if (y < map.height - 1)
			{
				b = cal_new_data(map, x, y + 1);
				draw_line(window, a, b);
			}
			x++;
		}
		y++;
	}

}
