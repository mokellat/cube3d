#include "cub3d.h"

void	data_gather()
{
	g_mini_map_factoor = 1;
	g_tile = 100;
	g_width = g_tile * 8;
	g_height = g_tile * 8;
	g_textureheight = g_tile;
	g_texturewidth = g_tile;
}

void	player_config()
{
	data_gather();
	g_new_player.rotation_speed = 3 * (M_PI / 180);
	g_new_player.turn_direction = 0;
	g_new_player.walk_direction = 0;
	g_new_player.pos_x = g_width / 2;
	g_new_player.pos_y = g_height / 2;
	g_new_player.turn_direction = 0;
	g_new_player.rotation_angle = M_PI / 2;
	g_new_player.FOV_angle = M_PI / 3;
	g_new_player.wall_width = 1;
	g_new_player.Num_rays = g_width / g_new_player.wall_width;
	g_new_player.ray_angle = g_new_player.rotation_angle - g_new_player.FOV_angle / 2;
	g_wall_check = 0;
}

void	normalise_angle()
{
	//g_new_player.ray_angle = remainder(2 * M_PI, -2 * M_PI);
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
    int     mapindex_x;
    int     mapindex_y;


    if (x < 0 || x > g_width || y < 0 || y > g_height)
        return (1);
    mapindex_x = (x / g_tile);
    mapindex_y = (y / g_tile);

    if (ptr[mapindex_y][mapindex_x] != 0)
        return(1);
    return (0);
}
