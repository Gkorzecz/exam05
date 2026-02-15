#include "life.h"

void free_board(char **board)
{
    int array = 0;
    while (board[array] != NULL)
    {
        free(board[array]);
        array++;
    }
	free(board);
}


void print_board(char **board, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            putchar(board[i][j]);
        putchar('\n');
    }
}

char** board_creation(int width, int height)
{
    char **empty_board = (char **)calloc(height + 1, sizeof(char *));
    int index = 0;
    for (int array = 0; array < height; array++)
    {
        index = 0;
        empty_board[array] = (char *)calloc(width + 1, sizeof(char));
        while (index < width)
        {
            empty_board[array][index] = ' ';
            index++;
        }
        empty_board[array][index] = '\0';
    }
    empty_board[height] = NULL;
    return(empty_board);
}

char	**add_livingcells(int width, int height)
{
	char buf;
	int	index = 0;
	int	array = 0;
	bool drawing_status = false;
	char **empty_board = board_creation(width, height);

	while (read(0, &buf, 1) > 0)
	{
		if (buf == 'x')
			drawing_status = !drawing_status;
		else if (buf == 'w' && (array - 1 >= 0))
			array--;
		else if (buf == 'a' && (index - 1 >= 0))
			index --;
		else if (buf == 's' && (array + 1 < height))
			array++;
		else if (buf == 'd' && (index + 1 < width))
			index++;

		if (drawing_status == true)
			empty_board[array][index] = '0';
	}
	return (empty_board);
}

char** update_board(char **board, int width, int height)
{
    char** updated_board = board_creation(width, height);
    if (!updated_board)
        return(NULL);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int n = 0;
            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        if (board[ny][nx] == '0')
                            n++;
                    }
                }
            }
            if (board[y][x] == '0')
            {
                if (n == 3 || n == 2)
                    updated_board[y][x] = '0';
            }
            else
            {
                if (n == 3)
                    updated_board[y][x] = '0';
            }
        }
    }
    free_board(board);
    return(updated_board);
}

void	game_of_life(int width, int height, int iteration)
{
	char	**new_board;

	new_board = add_livingcells(width, height);
	while (iteration--)
		new_board = update_board(new_board, width, height);

	print_board(new_board, width, height);
	free_board(new_board);
}
