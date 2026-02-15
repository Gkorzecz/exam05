#include "life.h"


void free_board(char **board, int height)
{
    int array = 0;
    while (array < height)
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

char **add_livingcells(int width, int height)
{
    int index = 0;
    int array = 0;
    char buffer;
    char **board = board_creation(width, height);
    bool drawing_status = false;

    while (read(0, &buffer, 1) > 0)
    {
        if (buffer == 'x')
            drawing_status = !drawing_status;
        else if (buffer == 'w' && array - 1 >= 0)
            array--;
        else if (buffer == 'a' && index - 1 >= 0)
            index--;
        else if (buffer == 's' && array + 1 < height)
            array++;
        else if (buffer == 'd' && index + 1 < width)
            index++;
        if (drawing_status == true)
            board[array][index] = '0';
    }
    return(board);
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
    free(board);
    return(updated_board);
}

void game_of_life(int width, int height, int iteration)
{
    char **new_board;
    new_board = add_livingcells(width, height);
    while (iteration--)
        update_board(new_board, width, height);
    print_board(new_board, width, height);
    free_board(new_board, height);
}
