/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:55:06 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 16:29:01 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "mlx.h"

void	error_pixel(t_window window, t_map *map)
{
	if (window.pixel == NULL)
	{
		mlx_destroy_image(window.mlx, window.img);
		mlx_destroy_window(window.mlx, window.window);
		mlx_destroy_display(window.mlx);
		free(window.mlx);
		free_map(map);
		get_next_line(-1);
		write_error();
	}
}

void	error_window(t_window window, t_map *map)
{
	mlx_destroy_display(window.mlx);
	free(window.mlx);
	free_map(map);
	get_next_line(-1);
	write_error();
}

void	error_img(t_window window, t_map *map)
{
	mlx_destroy_window(window.mlx, window.window);
	mlx_destroy_display(window.mlx);
	free(window.mlx);
	free_map(map);
	get_next_line(-1);
	write_error();
}

void	error_mlx(t_map *map)
{
	get_next_line(-1);
	free_map(map);
	write_error();
}

char	*free_two_and_null(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}
