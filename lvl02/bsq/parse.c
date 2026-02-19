#include "bsq.h"

static int parse_header(char *line, t_map *map)
{
    size_t len = ft_strlen(line);
    if (len && line[len - 1] == '\n')
        line[--len] = '\0';

    if (len < 4)
        return 0;

    for (size_t i = 0; i < len - 3; ++i)
        if (!ft_isdigit((unsigned char)line[i]))
            return 0;

    map->full     = line[len - 1];
    map->obstacle = line[len - 2];
    map->empty    = line[len - 3];
    line[len - 3] = '\0';

	if ((unsigned char)map->empty    < 32 || (unsigned char)map->empty    > 126 ||
    (unsigned char)map->obstacle < 32 || (unsigned char)map->obstacle > 126 ||
    (unsigned char)map->full     < 32 || (unsigned char)map->full     > 126)
    	return 0;

    map->rows = (int)ft_atoi(line);
    map->cols = 0;
    map->grid = NULL;

    return map->rows > 0 &&
           map->empty    != map->obstacle &&
           map->empty    != map->full     &&
           map->obstacle != map->full;
}

static int store_line(t_map *map, char *line, int idx)
{
	size_t len = ft_strlen(line);
	if (idx == 0)
		map->cols = (int)len;
	if ((int)len != map->cols)
		return 0;
	for (int i = 0; i < map->cols; ++i)
	{
		char c = line[i];
		if (c != map->empty && c != map->obstacle)
			return 0;
	}
	map->grid[idx] = line;
	return 1;
}

int read_map(FILE *fp, t_map *map)
{
    char   *line = NULL;
    size_t  cap  = 0;
    ssize_t n;

    /* ─── 1. read & validate header ───────────────────────────────────────── */
    n = getline(&line, &cap, fp);
    if (n <= 0)                         /* I/O error or empty file */
        return 0;

    if (!parse_header(line, map)) {     /* bad header → map error  */
        free(line);
        return 0;
    }

    free(line);                         /* free header buffer      */
    line = NULL;
    cap  = 0;                           /* force getline to malloc */

    /* ─── 2. allocate grid pointers ──────────────────────────────────────── */
    if (!safe_alloc((void **)&map->grid,
                    sizeof(char *) * map->rows))
        return 0;                       /* calloc failed           */

    /* ─── 3. read each data row ──────────────────────────────────────────── */
    for (int i = 0; i < map->rows; ++i)
    {
        n = getline(&line, &cap, fp);
        if (n <= 0) {                   /* premature EOF */
            free_map(map);
            free(line);
            return 0;
        }
        if (line[n - 1] == '\n')        /* drop trailing newline   */
            line[--n] = '\0';

        if (!store_line(map, line, i)) {/* width / char check      */
            free_map(map);
            free(line);
            return 0;
        }
        /* ownership of `line` transferred to map->grid[i] */
        line = NULL;                    /* ensure new malloc next loop */
        cap  = 0;
    }

    /* ─── 4. ensure no extra garbage after the map ───────────────────────── */
    int c = fgetc(fp);
    if (c != EOF && c != '\n') {
        free_map(map);
        return 0;
    }
    return 1;                           /* success */
}
