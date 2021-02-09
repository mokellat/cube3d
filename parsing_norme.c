/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_norme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:37 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/08 14:32:53 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	r_and_tex(int *indexx, int *i, int *k, int *x)
{
	if (g_lines[*i][*k] == 'R')
		big_r_exec(k, *i, indexx, *x);
	else if (g_lines[*i][*k] == 'N' && g_lines[*i][*k + 1] == 'O')
		g_files_tex.no_tex = textures_work(k, indexx, *i);
	else if (g_lines[*i][*k] == 'S' && g_lines[*i][*k + 1] == 'O')
		g_files_tex.so_tex = textures_work(k, indexx, *i);
	else if (g_lines[*i][*k] == 'W' && g_lines[*i][*k + 1] == 'E')
		g_files_tex.we_tex = textures_work(k, indexx, *i);
	else if (g_lines[*i][*k] == 'E' && g_lines[*i][*k + 1] == 'A')
		g_files_tex.ea_tex = textures_work(k, indexx, *i);
	else if (g_lines[*i][*k] == 'S')
		g_files_tex.sp_tex = textures_work(k, indexx, *i);
}

void	c_f_traitement(int *indexx, int *i, int *k)
{
	if (g_lines[*i][*k] == 'F')
	{
		colors_tre_floor(g_lines, *k, *i);
		(*indexx)++;
		g_counter++;
	}
	else if (g_lines[*i][*k] == 'C')
	{
		colors_tre_ceilling(g_lines, *k, *i);
		(*indexx)++;
		g_counter++;
	}
}

int		map_traitement(int i, int k, int indexx)
{
	int result;

	result = 0;
	if (i >= indexx && (g_lines[i][k] == '1' || g_lines[i][k] == '\0'))
	{
		result = 1;
		g_count++;
		g_map = realloc(g_map, g_count * sizeof(g_lines[i]));
		g_map[g_count - 1] = g_lines[i];
	}
	return (result);
}

void	get_next_line_work(int *fd, int *i, int *j)
{
	*fd = open("./file.cub", O_RDONLY);
	progrmm_init();
	while ((*i = get_next_line(*fd, &g_line)))
	{
		(*j)++;
		g_lines = realloc(g_lines, *j * sizeof(g_line));
		g_lines[*j - 1] = g_line;
	}
}

void	parsing_work(int *i, int j, int *k, int *indexx, int *x)
{
	while (*i < j)
	{
		while ((*k)++ < (int)ft_strlen(g_lines[*i]))
		{
			if (g_lines[*i][0] == '\0')
				(*indexx)++;
			r_and_tex(indexx, i, k, x);
			c_f_traitement(indexx, i, k);
			if (map_traitement(*i, *k, *indexx))
				break ;
		}
		(*i)++;
		*k = -1;
	}
}
