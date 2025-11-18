/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:22:42 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/18 22:13:26 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdlib.h>

int	close_window(t_window *window)
{
	mlx_destroy_window(window->mlx, window->window);
	mlx_destroy_display(window->mlx);
	free(window-> mlx);
	exit (0);
}

int	hook(int key, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (key == 65307)
	{
		close_window(window);
		exit(0);
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

void	window(t_map map)
{
	t_window	window;
	int		s_len;
	int		bbp;
	int		endian;

	s_len = 1000 * 32;
	bbp = 32;
	endian = 0;
	window.mlx = mlx_init();
	window.window = mlx_new_window(window.mlx, 1000, 1000, "Fdf");
	mlx_key_hook(window.window, hook, &window);
	mlx_hook(window.window, 17, 0, x_hook, &window);
	window.img = mlx_new_image(window.mlx, 1000, 1000);
	window.pixel = (int *)mlx_get_data_addr(window.img, &bbp, &s_len, &endian);
	draw(&window, map);
	mlx_put_image_to_window(window.mlx, window.window, window.img, 0, 0);
	mlx_loop(window.mlx);
}
