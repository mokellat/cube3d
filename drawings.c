/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:00 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/09 09:57:09 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_draw(double y, double x, int color)
{
	g_mlx.img_data[(int)y * g_width + (int)x] = color;
}

void	project_3d_draw(void)
{
	int indexx;

	indexx = 0;
	g_new_player.ray_angle = g_new_player.rotation_angle -
	g_new_player.fov_angle / 2;
	while (indexx < g_new_player.num_rays)
	{
		total_intersection_3d(indexx++);
		g_place_hold[indexx] = g_distance;
		g_new_player.ray_angle += g_new_player.fov_angle /
		g_new_player.num_rays;
	}
}
