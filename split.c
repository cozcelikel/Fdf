/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:44:41 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/15 22:30:12 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "fdf.h"


int	ft_wordcount(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	*ft_copy(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	free_all(char **arr, int j)
{
	while (j > 0)
	{
		j--;
		free(arr[j]);
	}
	free(arr);
}

int	fill_result(const char *s, char c, char **result, int i)
{
	int	j;
	int	start;

	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[j] = ft_copy(s, start, i);
			if (!result[j])
			{
				free_all(result, j);
				return (-1);
			}
			j++;
		}
	}
	result[j] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (ft_wordcount((char *)s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	if (fill_result(s, c, result, i) == -1)
		return (NULL);
	return (result);
}
