#include "life.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

void	free_board(char **board, int height)
{
	if (!board)
		return;
	for (int i = 0; i < height; i++)
		free(board[i]);
	free(board);
}

void	print_board(char **board, int width, int height)
{
	if (!board)
		return;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			putchar(board[y][x]);
		putchar('\n');
	}
}

char	**board_creation(int width, int height)
{
	char	**board;

	board = calloc((size_t)height, sizeof *board);
	if (!board)
		return NULL;

	for (int y = 0; y < height; y++)
	{
		board[y] = calloc((size_t)width + 1, sizeof **board);
		if (!board[y])
		{
			free_board(board, y);
			return NULL;
		}
		for (int x = 0; x < width; x++)
			board[y][x] = ' ';
		board[y][width] = '\0';
	}
	return board;
}

char	**add_livingcells(int width, int height)
{
	char	buf;
	int		x = 0;
	int		y = 0;
	bool	drawing = false;
	char	**board = board_creation(width, height);

	if (!board)
		return NULL;

	while (read(0, &buf, 1) > 0)
	{
		if (buf == 'x')
			drawing = !drawing;
		else if (buf == 'w' && y > 0)
			y--;
		else if (buf == 'a' && x > 0)
			x--;
		else if (buf == 's' && y + 1 < height)
			y++;
		else if (buf == 'd' && x + 1 < width)
			x++;

		if (drawing)
			board[y][x] = '0';
	}
	return board;
}

char	**update_board(char **board, int width, int height)
{
	char	**updated = board_creation(width, height);
	if (!updated)
		return board;  // keep old board if allocation fails

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int n = 0;

			for (int dy = -1; dy <= 1; dy++)
			{
				for (int dx = -1; dx <= 1; dx++)
				{
					if (dx == 0 && dy == 0)
						continue;

					int ny = y + dy;
					int nx = x + dx;

					if (nx >= 0 && nx < width &&
						ny >= 0 && ny < height &&
						board[ny][nx] == '0')
						n++;
				}
			}

			if (board[y][x] == '0')
			{
				if (n == 2 || n == 3)
					updated[y][x] = '0';
			}
			else
			{
				if (n == 3)
					updated[y][x] = '0';
			}
		}
	}

	free_board(board, height);
	return updated;
}

void	game_of_life(int width, int height, int iteration)
{
	char	**board;

	board = add_livingcells(width, height);
	if (!board)
		return;

	while (iteration--)
		board = update_board(board, width, height);

	print_board(board, width, height);
	free_board(board, height);
}
