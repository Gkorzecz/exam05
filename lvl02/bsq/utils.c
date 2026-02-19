#include "bsq.h"

void free_map(t_map *map)
{
	if (!map || !map->grid)
		return;
	for (int i = 0; i < map->rows; ++i)
		free(map->grid[i]);
	free(map->grid);
	map->grid = NULL;
}

// int is_print(char c)
// {

// }

int map_error(void)
{
	fputs("map error\n", stderr);
	return 1;
}

size_t ft_strlen(const char *s)
{
	size_t i = 0;
	while (s && s[i])
		++i;
	return i;
}

int ft_isdigit(int c) { return c >= '0' && c <= '9'; }

long ft_atoi(const char *s)
{
	long n = 0;
	while (*s && ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		++s;
	}
	return n;
}

int ft_min3(int a, int b, int c)
{
	int m = a;
	if (b < m) m = b;
	if (c < m) m = c;
	return m;
}

int safe_alloc(void **p, size_t sz)
{
	*p = calloc(1, sz);
	return *p != NULL;
}
