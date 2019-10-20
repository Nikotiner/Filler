/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:26:43 by dlian             #+#    #+#             */
/*   Updated: 2019/05/28 16:26:47 by dlian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_size(t_params *field, char *line)
{
	char **split;

	split = ft_strsplit(line, ' ');
	field->width = ft_atoi(split[2]);
	field->height = ft_atoi(split[1]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
}

int			get_dist(t_params *board, int k, int l, int pl)
{
	int i;
	int j;
	int result;
	int dist;

	i = 0;
	j = 0;
	result = -1;
	while (i < board->height)
	{
		j = 0;
		while (j < board->width)
		{
			dist = ((i - k) * (i - k)) + ((j - l) * (j - l));
			if (pl == 1 && ft_strchr("Xx", board->field[i][j]))
				result = (dist < result || result == -1) ? dist : result;
			else if (pl == 2 && ft_strchr("Oo", board->field[i][j]))
				result = (dist < result || result == -1) ? dist : result;
			j++;
		}
		i++;
	}
	return (result);
}

t_params	*genboard(char *line)
{
	t_params	*board;

	board = (t_params *)malloc(sizeof(t_params));
	get_size(board, line);
	free(line);
	get_next_line(0, &line);
	free(line);
	create_field(board);
	return (board);
}

t_params	*genpiece(char *line)
{
	t_params	*piece;

	piece = (t_params *)malloc(sizeof(t_params));
	get_size(piece, line);
	free(line);
	create_field(piece);
	return (piece);
}

void		freeboard(t_params *board, t_params *piece)
{
	int i;

	i = 0;
	if (!board)
		return ;
	while (board->field[i] != NULL)
	{
		free(board->field[i]);
		i++;
	}
	free(board->field);
	free(board);
	i = 0;
	if (!piece)
		return ;
	while (piece->field[i] != NULL)
	{
		free(piece->field[i]);
		i++;
	}
	free(piece->field);
	free(piece);
}
