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


// char	**board_creation(int width, int height)
// {
// 	char **empty_board;
// 	int	index = 0;
// 	int	array = 0;

// 	empty_board = (char **)calloc(height, sizeof(char *));
// 	while (array < height)
// 	{
// 		empty_board[array] = (char *)calloc(width + 1, sizeof(char));
// 		index = 0;
// 		while (index < width)
// 			empty_board[array][index++] = ' ';
// 		empty_board[array][index] = '\0';
// 		array++;
// 	}
// 	return(empty_board);
// }

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

// char	**update_board(char **new_board, int width, int height)
// {
// 	char **updated_board = board_creation(width, height);
// 	int	index = 0;
// 	int	array = 0;
// 	int	left = 0;
// 	int	right = 0;
// 	int	cell_counter = 0;

// 	while (array < height)
// 	{
// 		index = 0;
// 		while (index < width)
// 		{
// 			left = index - 1;
// 			if (left < 0)
// 				left = 0;
// 			right = index + 1;
// 			if (right >= width)
// 			{
// 				right = width - 1;
// 				if (width < 0)
// 					right++;
// 			}

// 			cell_counter = 0;
// 			if (array - 1 >= 0)
// 			{
// 				if (left != index && new_board[array - 1][left] == '0')
// 					cell_counter++;
// 				if (new_board[array - 1][index] == '0')
// 					cell_counter++;
// 				if (right != index && new_board[array - 1][right] == '0')
// 					cell_counter++;
// 			}
// 			if (array + 1 <= height - 1)
// 			{
// 				if (left != index && new_board[array + 1][left] == '0')
// 					cell_counter++;
// 				if (new_board[array + 1][index] == '0')
// 					cell_counter++;
// 				if (right != index && new_board[array + 1][right] == '0')
// 					cell_counter++;
// 			}
// 			if (left != index && new_board[array][left] == '0')
// 					cell_counter++;
// 			if (right != index && new_board[array][right] == '0')
// 					cell_counter++;
// 			if (((cell_counter == 2 || cell_counter == 3) && new_board[array][index] == '0') || (cell_counter == 3 && new_board[array][index] == ' '))
// 				updated_board[array][index] = '0';
// 			index++;
// 		}
// 		array++;
// 	}
// 	free_board(new_board, height);
// 	return (updated_board);
// }

// char **update_board(char **board, int width, int height)
// {
//     char **next = board_creation(width, height);
//     if (!next)
//         return NULL;

//     for (int y = 0; y < height; y++)
//     {
//         for (int x = 0; x < width; x++)
//         {
//             int n = 0;

//             for (int dy = -1; dy <= 1; dy++)
//             {
//                 for (int dx = -1; dx <= 1; dx++)
//                 {
//                     if (dy == 0 && dx == 0)
//                         continue;

//                     int ny = y + dy;
//                     int nx = x + dx;

//                     if (ny >= 0 && ny < height && nx >= 0 && nx < width)
//                     {
//                         if (board[ny][nx] == '0')
//                             n++;
//                     }
//                 }
//             }

//             if (board[y][x] == '0')
//             {
//                 if (n == 2 || n == 3)
//                     next[y][x] = '0';
//             }
//             else
//             {
//                 if (n == 3)
//                     next[y][x] = '0';
//             }
//         }
//     }

//     free_board(board, height);
//     return next;
// }

// char** update_board(char **board, int width, int height)
// {
//     char** updated_board = board_creation(int width, int height)
//     if (!updated_board)
//         return(NULL);
//     for (int y = 0; y < height; y++)
//     {
//         for (int y = 0; x < width; x++)
//         {
//             int n = 0;
//             for (int dy = -1; dy <= 1; dy++)
//             {
//                 for (int dx = -1; dy <= 1; dy++)
//                 {
//                     if (dx == 0 && dy == 0)
//                         continue;
//                     int nx = x + dx;
//                     int ny = y + dy;

//                     if (nx >= 0 && nx < width && ny >= 0 && ny < height)
//                     {
//                         if (board[ny][nx] == '0')
//                             n++;
//                     }
//                 }
//             }
//             if (board[y][x] == '0')
//             {
//                 if (n == 3 || n == 2)
//                     updated_board[y][x] = '0';
//             }
//             else
//             {
//                 if (n == 3)
//                     updated_board[y][x] = '0';
//             }
//         }
//     }
//     free(board, height);
//     return(updated_board);
// }

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

void	game_of_life(int width, int height, int iteration)
{
	char	**new_board;

	new_board = add_livingcells(width, height);
	while (iteration--)
		new_board = update_board(new_board, width, height);

	print_board(new_board, width, height);
	free_board(new_board);
}
