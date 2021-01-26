#include "cub3d.h"

int		key_pressed(int key)
{
	if (key == 53)
		exit(1);
	if(key == 126)
	{
		g_new_player.walk_direction = 1;
	}
	if(key == 125)
	{
		g_new_player.walk_direction = -1;
	}
	if(key == 123)
	{
		g_new_player.turn_direction = -1;
	}
	if(key == 124)
	{
		g_new_player.turn_direction = 1;
	}
	return 0;
}

int		key_released(int key)
{
	if(key == 126)
	{
		g_new_player.walk_direction = 0;
	}
	if(key == 125)
	{
		g_new_player.walk_direction = 0;
	}
	if(key == 123)
	{
		g_new_player.turn_direction = 0;
	}
	if(key == 124)
	{
		g_new_player.turn_direction = 0;
	}
	return 0;
}

int		update()
{
	double	move_step;
	double	move_speed;
	int		k;

	move_speed = 5.0;
	mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_width, g_height);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	g_new_player.rotation_angle += g_new_player.turn_direction * g_new_player.rotation_speed;
	move_step = g_new_player.walk_direction * move_speed;
	g_new_player.new_pos_x = g_new_player.pos_x + cos(g_new_player.rotation_angle) * move_step;
	g_new_player.new_pos_y = g_new_player.pos_y + sin(g_new_player.rotation_angle) * move_step;
	if (!haswallat(g_new_player.new_pos_x , g_new_player.new_pos_y))
	{
		g_new_player.pos_x = g_new_player.new_pos_x;
		g_new_player.pos_y = g_new_player.new_pos_y;
	}
	// Map();
	//  player_draw(g_new_player.pos_y, g_new_player.pos_x, 0XFF0000);
	// line(g_new_player.pos_x, g_new_player.pos_y, g_new_player.rotation_angle, 50, 0XFF0000);
	// // castAllRays();
	project_3D_Draw();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	return 0;
}
