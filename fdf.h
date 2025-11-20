/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:15:11 by cozcelik          #+#    #+#             */
/*   Updated: 2025/11/20 18:42:47 by cozcelik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stddef.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		*width;
	int		height;
	t_point	**points;
}	t_map;

typedef struct s_window
{
	void	*mlx;
	void	*window;
	void	*img;
	int		*pixel;
	t_map	*map;
}	t_window;

typedef struct s_line
{
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
}	t_line;

typedef struct s_scale
{
	float	x;
	float	z;
	float	y;
	float	f;
}	t_scale;

char	**ft_split(char const *s, char c);
int		ft_wordcount(char *str, char c);
void	file_name(int ac, char **av);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	file_type(int ac, char **av);
void	write_error(void);
t_map	read_map(char **av);
void	free_all(char **arr, int j);
int		ft_atoi(const char *str);
int		ft_atohex(const char *str);
void	window(t_map *map, int s_len, int endian, int bbp);
void	draw(t_window *window, t_map map, double scale, int y);
void	draw_line(t_window *window, t_point a, t_point b, int colar);
void	free_map(t_map *map);
int		give_height(char **av);
int		compute_z_range(t_map *map);
double	compute_final_scale(t_map *map, int win_w, int win_h, int z_range);
void	my_pixel_put(t_window *w, int x, int y, int color);
void	error_pixel(t_window window, t_map *map);
void	error_window(t_window window, t_map *map);
void	error_img(t_window window, t_map *map);
void	error_mlx(t_map *map);
void	split_free(char **splited);
char	*free_two_and_null(char *s1, char *s2);

#endif
