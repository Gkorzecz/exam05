#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
	int   rows;
	int   cols;
	char  empty;
	char  obstacle;
	char  full;
	char **grid;
}	t_map;

/* parse.c */
int  read_map(FILE *fp, t_map *map);

/* solve.c */
int  solve_map(t_map *map);
void print_map(t_map *map);

/* utils.c */
void	free_map(t_map *map);
int		map_error(void);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
long	ft_atoi(const char *s);
int		ft_min3(int a, int b, int c);
int		safe_alloc(void **p, size_t sz);
// int		is_print(char c);

#endif
