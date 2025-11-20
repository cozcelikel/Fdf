/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:35:23 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 11:52:15 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "fdf.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atohex(const char *str)
{
	int	i;
	int	result;
	int	value;

	i = 0;
	result = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = str[i] - 'a' + 10;
		else
			break ;
		result = result * 16 + value;
		i++;
	}
	return (result);
}

void	write_error(void)
{
	write(2, "ERROR\n", 6);
	exit(-1);
}

void	file_type(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 2)
		write_error();
	while (av[1][i])
		i++;
	if (i < 5)
		write_error();
	if (av[1][i - 1] != 'f' || av[1][i - 2] != 'd'
		|| av[1][i - 3] != 'f' || av[1][i - 4] != '.')
		write_error();
}

int	give_height(char **av)
{
	int		height;
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		write_error();
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}
