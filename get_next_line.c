/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:11:35 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/16 02:41:06 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <stdlib.h>

static char	*ft_read_store(int fd, char *remainder)
{
	char	*temp;
	char	*new_remainder;
	ssize_t	bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	while (!ft_strchr(remainder, '\n'))
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(temp), free(remainder), NULL);
		if (bytes == 0)
			break ;
		temp[bytes] = '\0';
		new_remainder = ft_strjoin(remainder, temp);
		if (!new_remainder)
			return (free(remainder), free(temp), NULL);
		free(remainder);
		remainder = new_remainder;
	}
	free(temp);
	return (remainder);
}

static char	*ft_extract_line(char *remainder)
{
	char	*newline_pos;
	size_t	len;

	newline_pos = ft_strchr(remainder, '\n');
	if (newline_pos)
		len = newline_pos - remainder + 1;
	else
		len = ft_strlen(remainder);
	return (ft_substr(remainder, 0, len));
}

static char	*ft_update_remainder(char *remainder)
{
	char	*newline_pos;
	char	*new_remainder;

	newline_pos = ft_strchr(remainder, '\n');
	if (!newline_pos)
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_substr(remainder, (newline_pos - remainder) + 1,
			ft_strlen(remainder) - (newline_pos - remainder + 1));
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;

	if (fd == -1)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_read_store(fd, remainder);
	if (!remainder || remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = ft_extract_line(remainder);
	remainder = ft_update_remainder(remainder);
	return (line);
}
