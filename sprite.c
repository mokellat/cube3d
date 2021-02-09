/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:53:14 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/08 14:59:27 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_count)
	{
		j = 0;
		while (j < (int)ft_strlen(g_map[i]))
		{
			if (g_map[i][j] == '2')
			{
				g_sprites[g_sprite_index].x = (j + 0.5) * g_tile;
				g_sprites[g_sprite_index].y = (i + 0.5) * g_tile;
				g_sprite_index++;
			}
			j++;
		}
		i++;
	}
}

void	draw_sprites(int x, double distance, double height)
{
	int i;
	int j;
	int y_offset;
	int color;

	i = x;
	while (i <= x + height)
	{
		j = (g_height - height) / 2;
		y_offset = 0;
		if (i >= 0 && i < g_width && distance < g_place_hold[i])
		{
			while (j < (g_height + height) / 2 - 1)
			{
				color = g_sp_image.data[(int)
				(y_offset / height * g_sp_image.height)
				* g_sp_image.width +
				(int)((i - x) / height * g_sp_image.width)];
				draw_one_pixel(j, i, color);
				j++;
				y_offset++;
			}
		}
		i++;
	}
}

void	replace(int i)
{
	t_sprite tmp;

	if (g_sprites[i].distance < g_sprites[i + 1].distance)
	{
		tmp = g_sprites[i];
		g_sprites[i] = g_sprites[i + 1];
		g_sprites[i + 1] = tmp;
	}
}

void	sprites_sort(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_sprite_index)
	{
		g_sprites[i].distance = distance(g_sprites[i].x, g_sprites[i].y);
		i++;
	}
	i = 0;
	while (i < g_sprite_index - 1)
	{
		j = 0;
		while (j < g_sprite_index - 1 - i)
		{
			replace(j);
			j++;
		}
		i++;
	}
}

void	render_sprite(void)
{
	int			i;

	sprites_sort();
	i = 0;
	while (i < g_sprite_index)
	{
		g_sprites[i].distance = distance(g_sprites[i].x, g_sprites[i].y);
		g_angle = atan2(g_sprites[i].y - g_new_player.pos_y, g_sprites[i].x -
		g_new_player.pos_x);
		normalise_rotation_angle();
		if ((g_new_player.rotation_angle - g_new_player.fov_angle / 2)
		- g_angle > M_PI)
			g_angle = g_angle + 2 * M_PI;
		if (g_angle - (g_new_player.rotation_angle -
		g_new_player.fov_angle / 2) > M_PI)
			g_angle = g_angle - 2 * M_PI;
		g_sprite_height = (g_tile / g_sprites[i].distance) *
						g_distanceprojplane;
		g_column_index = (g_angle - (g_new_player.rotation_angle -
		g_new_player.fov_angle / 2)) / (g_new_player.fov_angle / g_width) -
		(g_sprite_height / 2);
		draw_sprites(g_column_index, g_sprites[i].distance, g_sprite_height);
		i++;
	}
}
