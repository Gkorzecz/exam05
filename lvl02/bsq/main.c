#include "bsq.h"

static int process_stream(FILE *fp)
{
	t_map map;
	if (!read_map(fp, &map))
		return map_error();
	if (!solve_map(&map))
	{
		free_map(&map);
		return map_error();
	}
	print_map(&map);
	free_map(&map);
	return 0;
}

int main(int argc, char **argv)
{
	int status = 0;

	if (argc == 1)
		status = process_stream(stdin);
	else
	{
		for (int i = 1; i < argc; i++)
		{
			FILE *fp = fopen(argv[i], "r");
			if (!fp)
				status = map_error();
			else
			{
				if (process_stream(fp) != 0)
					status = 1;
				fclose(fp);
			}
			if (i + 1 < argc)
				fputc('\n', stdout);
		}
	}
	return (status);
}
