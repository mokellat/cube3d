/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:51:49 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/07 17:26:02 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void		colors_tre_floor(char **g_lines, int k, int i)
{
	k = k + 1;
	while (g_lines[i][k] != ',')
	{
		g_file.color_r_f = ft_atoi(&g_lines[i][k]);
		break ;
	}
	while (g_lines[i][k] != ',')
		k++;
	while (g_lines[i][++k] != ',')
	{
		if (ft_atoi(&g_lines[i][k]) || g_lines[i][k] == 48)
			g_file.color_g_f = ft_atoi(&g_lines[i][k]);
		break ;
	}
	while (g_lines[i][k] != ',')
		k++;
	while (g_lines[i][++k])
	{
		if (ft_atoi(&g_lines[i][k]) || g_lines[i][k] == 48)
			g_file.color_b_f = ft_atoi(&g_lines[i][k]);
		break ;
	}
}

void		colors_tre_ceilling(char **g_lines, int k, int i)
{
	k = k + 1;
	while (g_lines[i][k] != ',')
	{
		g_file.color_r_c = ft_atoi(&g_lines[i][k]);
		break ;
	}
	while (g_lines[i][k] != ',')
		k++;
	while (g_lines[i][++k] != ',')
	{
		g_file.color_g_c = ft_atoi(&g_lines[i][k]);
		break ;
	}
	while (g_lines[i][k] != ',')
		k++;
	while (g_lines[i][++k])
	{
		g_file.color_b_c = ft_atoi(&g_lines[i][k]);
		break ;
	}
}
