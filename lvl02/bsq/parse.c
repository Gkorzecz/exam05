#include "bsq.h"

static int parse_header(char *line, t_map *map)
{
    size_t len = ft_strlen(line);
    if (len && line[len - 1] == '\n')
        line[--len] = '\0';

    if (len < 4)
        return (0);

    for (size_t i = 0; i < len - 3; ++i)
        if (!ft_isdigit((unsigned char)line[i]))
            return 0;

    map->full     = line[len - 1];
    map->obstacle = line[len - 2];
    map->empty    = line[len - 3];
    line[len - 3] = '\0';

	if (!is_print(map->obstacle) || !is_print(map->full) || !is_print(map->empty))
    	return (0);

    map->rows = (int)ft_atoi(line);
    map->cols = 0;
    map->grid = NULL;

    return (map->rows > 0 && map->empty != map->obstacle && map->empty != map->full && map->obstacle != map->full);
}

static int store_line(t_map *map, char *line, int idx)
{
	size_t len = ft_strlen(line);
	if (idx == 0)
		map->cols = (int)len;
	if ((int)len != map->cols)
		return (0);
	for (int i = 0; i < map->cols; ++i)
	{
		char c = line[i];
		if (c != map->empty && c != map->obstacle)
			return (0);
	}
	map->grid[idx] = line;
	return (1);
}

int read_map(FILE *fp, t_map *map)
{
	char   *line = NULL;
	size_t  cap  = 0;
	ssize_t n;

	/* ─── 1. read & validate header ───────────────────────── */
	n = getline(&line, &cap, fp);
	if (n <= 0 || line[n - 1] != '\n')
	{
		free(line);
		return (0);
	}

	if (!parse_header(line, map))
	{
		free(line);
		return (0);
	}

	free(line);
	line = NULL;
	cap  = 0;

	/* ─── 2. allocate grid ─────────────────────────────────── */
	if (!safe_alloc((void **)&map->grid, sizeof(char *) * map->rows))
		return (0);

	/* ─── 3. read rows ─────────────────────────────────────── */
	for (int i = 0; i < map->rows; ++i)
	{
		n = getline(&line, &cap, fp);
		if (n <= 0 || line[n - 1] != '\n')   /* ← enforce newline */
		{
			free_map(map);
			free(line);
			return (0);
		}

		line[--n] = '\0';                    /* strip newline */

		if (!store_line(map, line, i))
		{
			free_map(map);
			free(line);
			return (0);
		}

		line = NULL;   /* ownership transferred */
		cap  = 0;
	}

	/* ─── 4. ensure no garbage after map ───────────────────── */
	int c = fgetc(fp);
	if (c != EOF && c != '\n')
	{
		free_map(map);
		return (0);
	}

	return (1);
}
