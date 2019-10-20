/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:47:28 by dlian             #+#    #+#             */
/*   Updated: 2019/05/28 16:47:32 by dlian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <stdlib.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
# include "../get_next_line/get_next_line.h"

typedef struct	s_params
{
	char			**field;
	int				width;
	int				height;
	int				player;
}				t_params;

void			get_size(t_params *field, char *line);
int				get_dist(t_params *board, int k, int l, int pl);
t_params		*genboard(char *line);
t_params		*genpiece(char *line);
void			create_field(t_params *board);
int				check_player();
void			freeboard(t_params *board, t_params *piece);
#endif
