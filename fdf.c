#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "fdf.h"
void error(int ac, char **av, int fd)
{
    int i;
    
    i = 0;
    while (av[1][i] != '\0')
        i++;
    if(i < 4 )
    {
        write(2, "Error\n", 6);
        exit(-1);
    }
    if (av[1][i-1] !='f' || av[1][i-2] != 'd'
        ||av[1][i-3] != 'f' ||  av[1][i-4] != '.' || fd < 0)
    {
        write(2, "Error\n", 6);
        exit(-1);
    }
}
int read_file_len(int fd)
{
    char    *buf;
    int     len;
    int     n;

    buf = malloc(sizeof(char) * 1000);
    if (buf == NULL)
    {
        write(2, "Memory Error\n", 14);
        exit (-1);
    }
    n = 0;
    len = 0;
 
    while((n = read(fd, buf, 1000)) > 0)
    {
        len = n + len ;
    }
    if (n == -1)
    {
        write(2, "Read error\n", 11);
        free(buf);
        exit(-1);
    }
    free(buf);
    return (len);
}
char    *ft_copy_file(int len, char **av, int ac)
{
    char    *buf;
    int fd;

    buf = malloc(sizeof(char) * len + 1);
    if(buf == NULL)
        return (NULL);
    fd = open(av[1], O_RDONLY);
    error(ac, av, fd);
    if(-1 == read(fd,buf,len))
    {
        write(2, "Read error \n", 13);
        free(buf);
        exit(-1);
    }
    buf[len] = '\0';
    close (fd);
    return (buf);
}
char    *take_file(int ac, char **av)
{
    int     fd;
    int     len;
    char    *str;
    if (ac != 2)
    {
        write(2, "Error\n", 6);
        exit (-1);
    }
    fd = open(av[1], O_RDONLY);
    error(ac, av, fd);
    len = read_file_len(fd);
    close(fd);
    str = ft_copy_file(len, av, ac);
    if(str == NULL)
    {
        write(2, "Memory Error\n", 14);
        exit (-1);
    }
    return (str);
}
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
void    free_split(char **str)
{
    int i;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int *num_count(char **str)
{
    int line;
    int i;
    int *number_amount;

    i = 0;
    line = 0;
    while(str[line] != NULL)
        line++;
    number_amount = malloc(sizeof(int) * line);
    if( number_amount == NULL)
    {
        free_split(str);
        write(2, "Memory Error\n", 14);
        exit(1);
    }
    while(str[i] != NULL)
    {
        number_amount[i] = ft_wordcount(str[i], ' ');
        i++;
    }
    return (number_amount);
}

int **martixing(char **str, int *num_amount)
{
    int **matrix;
    int i;
    int j;
    int start;
    int k;

    i = 0;
    while (str[i])
        i++;
    matrix = malloc(sizeof(int *) * (i + 1));
    if (!matrix)
    {
        free(num_amount);
        free_split(str);
        write(2, "MATRIX Error\n", 13);
        exit(1);
    }
    i = 0;
    while (str[i])
    {
        matrix[i] = malloc(sizeof(int) * num_amount[i]);
        if (!matrix[i])
        {
            while (i--)
                free(matrix[i]);
            free(matrix);
            free(num_amount);
            free_split(str);
            write(2, "MALLOC Error\n", 13);
            exit(1);
        }
        k = 0;
        j = 0; 
        while (str[i][k] && j < num_amount[i])
        {
            while (str[i][k] == ' '  && str[i][k] !='\0')
                k++;
            start = k;
            if (str[i][k] != ' ' && str[i][k] != '\0')
            {
                while (str[i][k] != ' ' && str[i][k] != '\0')
                    k++;
                matrix[i][j] = ft_atoi(&str[i][start]);
                j++;
            }
        }
        i++;
    }
    return (matrix);
}

int main(int ac, char**av)
{
    char *arg;
    char **str;
    
    arg = take_file(ac,av);
    str = ft_split(arg,'\n');
    free(arg);
    if (str == NULL)
    {
        write(2, "FT_SPLİT Error\n", 16);
        free(arg);
        return (-1);
    }
    int *num_amount = num_count(str);
    int lines =11;
    // 4️⃣ Matrix’i oluştur ve doldur
    int **mat = martixing(str, num_amount);

    // 5️⃣ Matrix’i yazdır
    int i = 0, j;
   for (i = 0; i < lines; i++) {
    for (j = 0; j < num_amount[i]; j++)
        printf("%d ", mat[i][j]);
    printf("\n");
}

    // 6️⃣ Heap temizle
  for (i = 0; i < lines; i++)
    free(mat[i]);
free(mat);
    free_split(str);
    
}
