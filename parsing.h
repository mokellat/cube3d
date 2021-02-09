/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:51 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/08 15:55:06 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"

typedef struct	s_file_parsing
{
	int			width;
	int			height;
	int			color_r_f;
	int			color_g_f;
	int			color_b_f;
	int			color_r_c;
	int			color_g_c;
	int			color_b_c;
	char		*ptr;
}				t_parse;
t_parse			g_file;
char			**g_lines;
char			**g_map;
char			*g_line;
int				g_count;
int				g_counter;
int				g_b_lenght;
int				g_file_lenght;
void			colors_tre_floor(char **g_lines, int k, int i);
void			colors_tre_ceilling(char **g_lines, int k, int i);
void			big_r_exec(int *k, int i, int *indexx, int x);
int				r_exec(int *k, int i, int *x);
char			*textures_work(int *k, int *indexx, int i);
void			player_init();
double			player_direc();
void			error(int etat, char *string);
void			ft_putstr(char *s);
void			file_errors();
void			progrmm_init();
int				map_parsing();
void			file_errors_beg(int j, int indexx);
int				check_map_elements();
int				check_map_errors();
int				map_surronding();
int				ft_strcmp(char *s1, const char *s2);
void			r_and_tex(int *indexx, int *i, int *k, int *x);
void			c_f_traitement(int *indexx, int *i, int *k);
int				map_traitement(int i, int k, int indexx);
void			get_next_line_work(int *fd, int *i, int *j);
void			parsing_work(int *i, int j, int *k, int *indexx, int *x);
#endif
