#include "bsq.h"

static int allocate_dp(int **prev, int **curr, int cols)
{
	if (!safe_alloc((void **)prev, sizeof(int) * cols))
		return (0);
	if (!safe_alloc((void **)curr, sizeof(int) * cols))
	{
		free(*prev);
		*prev = NULL;
		return (0);
	}
	return (1);
}

int solve_map(t_map *map)
{
	int *prev = NULL, *curr = NULL;
	if (!allocate_dp(&prev, &curr, map->cols)) return 0;

	int best_sz = 0;
	int best_i = 0;
	int best_j = 0;

	for (int i = 0; i < map->rows; ++i)
	{
		for (int j = 0; j < map->cols; ++j)
		{
			if (map->grid[i][j] == map->obstacle)
				curr[j] = 0;
			else if (i == 0 || j == 0)
				curr[j] = 1;
			else
				curr[j] = ft_min3(prev[j], curr[j - 1], prev[j - 1]) + 1;

			if (curr[j] > best_sz)
			{
				best_sz = curr[j];
				best_i  = i;
				best_j  = j;
			}
		}
		int *tmp = prev;
		prev = curr;
		curr = tmp;
	}
	free(prev);
    free(curr);
	if (best_sz == 0)
        return (1);

	for (int y = best_i; y >= best_i - best_sz + 1; --y)
		for (int x = best_j; x >= best_j - best_sz + 1; --x)
			map->grid[y][x] = map->full;
	return (1);
}

void print_map(t_map *map)
{
	for (int i = 0; i < map->rows; i++)
	{
		fputs(map->grid[i], stdout);
		fputc('\n', stdout);
	}
}
