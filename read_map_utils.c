/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:35:23 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/16 03:40:35 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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