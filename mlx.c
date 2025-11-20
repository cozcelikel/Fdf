/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:22:42 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 16:15:51 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>

int	close_window(t_window *window)
{
	if (window->img)
		mlx_destroy_image(window->mlx, window->img);
	if (window->window)
		mlx_destroy_window(window->mlx, window->window);
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	if (window->map)
		free_map(window->map);
	get_next_line(-1);
	exit (0);
}

int	hook(int key, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (key == 65307)
	{
		close_window(window);
	}
	return (0);
}

int	x_hook(void *param)
{
	t_window	*win;

	win = (t_window *)param;
	close_window(win);
	return (0);
}

void	window(t_map *map, int s_len, int endian, int bbp)
{
	t_window	window;
	double		scale;

	window.mlx = mlx_init();
	if (window.mlx == NULL)
		error_mlx(map);
	window.window = mlx_new_window(window.mlx, 1500, 1500, "Fdf");
	if (window.window == NULL)
		error_window(window, map);
	mlx_key_hook(window.window, hook, &window);
	mlx_hook(window.window, 17, 0, x_hook, &window);
	window.img = mlx_new_image(window.mlx, 1500, 1500);
	if (window.img == NULL)
		error_img(window, map);
	window.pixel = (int *)mlx_get_data_addr(window.img, &bbp, &s_len, &endian);
	if (window.pixel == NULL)
		error_pixel(window, map);
	window.map = map;
	scale = compute_final_scale(map, 1500, 1500);
	draw(&window, *map, scale, 0);
	mlx_put_image_to_window(window.mlx, window.window, window.img, 0, 0);
	mlx_loop(window.mlx);
}
