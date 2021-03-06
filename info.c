/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:12 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/07 18:32:26 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_gather(void)
{
	g_mini_map_factoor = 1;
	g_tile = 100;
	g_width = g_file.width;
	g_height = g_file.height;
	g_textureheight = g_tile;
	g_texturewidth = g_tile;
}

void	player_config(void)
{
	data_gather();
	g_new_player.rotation_speed = 2 * (M_PI / 180);
	g_new_player.turn_direction = 0;
	g_new_player.walk_direction = 0;
	g_new_player.turn_direction = 0;
	g_new_player.rotation_angle = M_PI / 2;
	g_new_player.fov_angle = M_PI / 3;
	g_new_player.wall_width = 1;
	g_new_player.num_rays = g_width;
	g_new_player.ray_angle = g_new_player.rotation_angle -
	g_new_player.fov_angle / 2;
	g_wall_check = 0;
}

void	normalise_angle(void)
{
	if (g_new_player.ray_angle < 0)
		g_new_player.ray_angle += 2 * M_PI;
	if (g_new_player.ray_angle > 2 * M_PI)
		g_new_player.ray_angle -= 2 * M_PI;
}

double	distance_between(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int		haswallat(double x, double y)
{
	double		mapindex_x;
	double		mapindex_y;

	mapindex_x = floor(x / g_tile);
	mapindex_y = floor(y / g_tile);
	if (mapindex_y < g_count)
	{
		if (g_map[(int)mapindex_y][(int)mapindex_x] != '0' &&
		g_map[(int)mapindex_y][(int)mapindex_x] != '2')
			return (1);
	}
	return (0);
}
