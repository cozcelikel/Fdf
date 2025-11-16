/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:16:25 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/16 03:50:35 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>

void free_map(t_map *map)
{
    int y = 0;

    if (!map || !map->points)
        return;

    while (y < map->height)
    {
        if (map->points[y])
            free(map->points[y]);
        y++;
    }
    free(map->points);
    map->points = NULL;
    map->height = 0;
    map->width = 0;
}

int	main(int ac, char **av)
{
	t_map map;
	
	file_type(ac, av);
	map = read_map(av);
	 for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            printf("z:%d col:%d   ",
                map.points[y][x].z,
                map.points[y][x].color);
        }
        printf("\n");
    }
	get_next_line(-1);
	free_map(&map);
}
