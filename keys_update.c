/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:51:25 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/12 18:51:16 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int key)
{
	if (key == EXIT)
	{
		free_mem();
		exit(EXIT_SUCCESS);
	}
	if (key == W)
		g_new_player.walk_direction = 1;
	if (key == S)
		g_new_player.walk_direction = -1;
	if (key == LEFT)
		g_new_player.turn_direction = -1;
	if (key == RIGHT)
		g_new_player.turn_direction = 1;
	if (key == A)
		g_new_player.side_direction = 1;
	if (key == D)
		g_new_player.side_direction = -1;
	return (0);
}

int		key_released(int key)
{
	if (key == W)
		g_new_player.walk_direction = 0;
	if (key == S)
		g_new_player.walk_direction = 0;
	if (key == LEFT)
		g_new_player.turn_direction = 0;
	if (key == RIGHT)
		g_new_player.turn_direction = 0;
	if (key == A)
		g_new_player.side_direction = 0;
	if (key == D)
		g_new_player.side_direction = 0;
	return (0);
}

int		red_cross(void)
{
	mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	free_mem();
	exit(EXIT_SUCCESS);
}

void	player_move(double g_angle, double move_step, double move_speed)
{
	if (g_new_player.side_direction != 0)
	{
		g_angle = g_new_player.rotation_angle - M_PI / 2;
		move_step = g_new_player.side_direction * move_speed;
		g_new_player.new_pos_x = g_new_player.pos_x + cos(g_angle) * move_step;
		g_new_player.new_pos_y = g_new_player.pos_y + sin(g_angle) * move_step;
	}
	else
	{
		g_new_player.rotation_angle += g_new_player.turn_direction
		* g_new_player.rotation_speed;
		move_step = g_new_player.walk_direction * move_speed;
		g_new_player.new_pos_x = g_new_player.pos_x +
		cos(g_new_player.rotation_angle) * move_step;
		g_new_player.new_pos_y = g_new_player.pos_y +
		sin(g_new_player.rotation_angle) * move_step;
	}
}

int		update(void)
{
	double	move_step;
	double	move_speed;
	int		k;
	double	g_angle;

	move_speed = 10.0;
	g_angle = 0.0;
	move_step = 0.0;
	mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_width, g_height);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	player_move(g_angle, move_step, move_speed);
	if (!haswallat(g_new_player.new_pos_x, g_new_player.new_pos_y))
	{
		g_new_player.pos_x = g_new_player.new_pos_x;
		g_new_player.pos_y = g_new_player.new_pos_y;
	}
	project_3d_draw();
	render_sprite();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	return (0);
}
