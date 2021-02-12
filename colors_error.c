/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:38:19 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/12 18:55:48 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_error(int i)
{
	char	**ptr;
	int		indexx;
	int		k;

	indexx = 0;
	k = 0;
	ptr = (char **)malloc(sizeof(char) * ft_strlen(g_lines[i]));
	ptr[indexx] = (ft_strtrim(g_lines[i], " "));
	while (++k < (int)ft_strlen(ptr[indexx]))
	{
		if (ptr[indexx][k] != ' ' && !ft_isdigit(ptr[indexx][k])
		&& ptr[indexx][k] != ',')
			error(EXIT_FAILURE, "colors are invalid !");
	}
}
