/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:33:13 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/18 12:32:46 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	args_count(int i, int k, char c, int count)
{
	int		indexx;
	int		j;

	indexx = 0;
	j = k + 1;

	while (g_lines[i][j] == ' ')
		j++;
	while (j + 1 < (int)ft_strlen(g_lines[i]))
	{
		if (g_lines[i][j] == c && (ft_isdigit(g_lines[i][j + 1])))
			indexx++;
		j++;
	}
	if(indexx >= count && count == 2)
		error(EXIT_FAILURE, "Dimensions are invalid !");
}

void	args_count_col(int i)
{
	int		indexx;
	int		j;

	indexx = 0;
	j = 0;
	while (j < (int)ft_strlen(g_lines[i]))
	{
		if (g_lines[i][j] == ',')
			indexx++;
		j++;
	}
	if(indexx > 2 || indexx < 2)
		error(EXIT_FAILURE, "colors are invalid !");
}
