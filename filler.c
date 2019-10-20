/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:26:32 by dlian             #+#    #+#             */
/*   Updated: 2019/05/28 16:26:35 by dlian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		check_player(void)
{
	char	*line;
	int		result;

	result = 0;
	get_next_line(0, &line);
	if (ft_strstr(line, "dlian"))
	{
		if (ft_strstr(line, "$$$ exec p1"))
			result = 1;
		else if (ft_strstr(line, "$$$ exec p2"))
			result = 2;
	}
	free(line);
	return (result);
}

void	create_field(t_params *board)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	board->field = (char **)malloc(sizeof(char*) *
		board->height + sizeof(char*));
	while (i < board->height && get_next_line(0, &line) > 0)
	{
		j = 0;
		k = 0;
		board->field[i] = (char *)malloc(sizeof(char) *
			board->width + sizeof(char));
		while (line[k] != '\0' && j < board->width)
		{
			if (ft_strchr(".XxOo*", line[k]))
				board->field[i][j++] = line[k];
			k++;
		}
		board->field[i][j] = '\0';
		free(line);
		i++;
	}
	board->field[i] = NULL;
}

int		is_placed(t_params *board, t_params *piece, int *b_pos, int pl)
{
	int		i;
	int		j;
	int		emp;
	int		cnt_fillcell;
	char	ch;

	i = -1;
	emp = 0;
	cnt_fillcell = 0;
	while (++i < piece->height)
	{
		j = -1;
		while (++j < piece->width)
			if (piece->field[i][j] == '*')
			{
				ch = board->field[b_pos[0] + i][b_pos[1] + j];
				cnt_fillcell = ((ch == '.') ? cnt_fillcell + 1 : cnt_fillcell);
				if (ft_strchr((pl == 2) ? "Xx" : "Oo", ch) && emp != -1)
					emp = (emp == 1) ? -1 : 1;
				if (ft_strchr((pl == 2) ? "Oo" : "Xx", ch))
					emp = -1;
			}
	}
	return ((emp <= 0) ? -1 : cnt_fillcell);
}

void	find_place(t_params *board, t_params *piece, int pl)
{
	int i;
	int j;
	int *result;
	int count_filling_cell;
	int dist;

	i = -1;
	result = (int[4]){ 0 };
	count_filling_cell = 0;
	while (++i < board->height - piece->height + 1)
	{
		j = -1;
		while (++j < board->width - piece->width + 1)
		{
			count_filling_cell = is_placed(board, piece, (int[]){i, j}, pl);
			dist = get_dist(board, i, j, pl);
			if ((count_filling_cell > 0 && dist < result[3]) ||
				count_filling_cell > result[2])
				result = (int[4]){ i, j, count_filling_cell, dist};
		}
	}
	ft_putnbr(result[0]);
	write(1, " ", 1);
	ft_putnbr(result[1]);
	write(1, "\n", 1);
}

int		main(void)
{
	t_params	*board;
	t_params	*piece;
	char		*line;
	int			pl;

	pl = check_player();
	if (!pl)
	{
		write(1, "Bad player info", 15);
		return (0);
	}
	while (get_next_line(0, &line) > 0 && line[0] != '\0')
	{
		if (ft_strstr(line, "Plateau "))
			board = genboard(line);
		else if (ft_strstr(line, "Piece "))
		{
			piece = genpiece(line);
			find_place(board, piece, pl);
			freeboard(board, piece);
		}
		else
			free(line);
	}
	return (0);
}
