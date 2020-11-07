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
	g_new_player.rotation_speed = 2 * (M_PI / 2);
	g_new_player.move_speed = 2.0;
	// g_new_player.turn_direction = 0;
	// g_new_player.walk_direction = 0;
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

void	rays_directions()
{
	normalise_angle();
	g_new_player.ray_down = (g_new_player.ray_angle > 0 && g_new_player.ray_angle < M_PI);
	g_new_player.ray_up = !(g_new_player.ray_down);
	g_new_player.ray_left = !g_new_player.ray_right;
	g_new_player.ray_right = (g_new_player.ray_angle < 0.5 * M_PI || g_new_player.ray_angle > 1.5 * M_PI);
}

void	line(int x1, int y1, double angle, int var, int color)
{
	int i;
	int j;

	g_rayon = var;
	while (g_rayon--)
	{
		j = (cos(angle) * g_rayon + x1) * g_mini_map_factoor;
		i = (sin(angle) * g_rayon + y1) * g_mini_map_factoor;
		g_mlx.img_data[i * g_width + j] = color;
	}
}

void	horz_intersection_calcul()
{
	rays_directions();
	normalise_angle();
	g_foundawallhorz = 0;
	g_horzwallhitx = 0;
	g_horzwallhity = 0;
	g_yinterupthorz = floor(g_new_player.pos_y / g_tile) * g_tile;
	g_yinterupthorz += g_new_player.ray_down ? g_tile : 0;
	g_xinterupthorz = g_new_player.pos_x + ((g_yinterupthorz - g_new_player.pos_y) / tan(g_new_player.ray_angle));
	g_ystephorz = g_tile;
	g_ystephorz *= g_new_player.ray_up ? -1 : 1;
	g_xstephorz = g_tile / tan(g_new_player.ray_angle);
	g_xstephorz *= (g_new_player.ray_left && g_xstephorz > 0) ? -1 : 1;
	g_xstephorz *= (g_new_player.ray_right && g_xstephorz < 0) ? -1 : 1;
	g_nexthorztouchx = g_xinterupthorz;
	g_nexthorztouchy = g_yinterupthorz;
	if (g_new_player.ray_up)
		g_nexthorztouchy--;
	while (g_nexthorztouchy >= 0 && g_nexthorztouchy <= g_height && g_nexthorztouchx >= 0 && g_nexthorztouchx <= g_width)
	{
		if (ptr[(int)(g_nexthorztouchy / g_tile)][(int)(g_nexthorztouchx / g_tile)] == 1)
		{
			g_foundawallhorz = 1;
			g_horzwallhity = g_nexthorztouchy;
			g_horzwallhitx = g_nexthorztouchx;
			break;
		}
		else
		{
			g_nexthorztouchy += g_ystephorz;
			g_nexthorztouchx += g_xstephorz;
		}
	}
}

void	ver_intersection_calcul()
{
	rays_directions();
	normalise_angle();
	g_foundawallver = 0;
	g_verwallhitx = 0;
	g_verwallhity = 0;
	g_xinteruptver = floor(g_new_player.pos_x / g_tile) * g_tile;
	g_xinteruptver += g_new_player.ray_right ? g_tile : 0;
	g_yinteruptver = g_new_player.pos_y + ((g_xinteruptver - g_new_player.pos_x) * tan(g_new_player.ray_angle));
	g_xstepver = g_tile;
	g_xstepver *= g_new_player.ray_left ? -1 : 1;
	g_ystepver = g_tile * tan(g_new_player.ray_angle);
	g_ystepver *= (g_new_player.ray_up && g_ystepver > 0) ? -1 : 1;
	g_ystepver *= (g_new_player.ray_down && g_ystepver < 0) ? -1 : 1;
	g_nextvertouchx = g_xinteruptver;
	g_nextvertouchy = g_yinteruptver;
	if (g_new_player.ray_left)
		g_nextvertouchx--;
	while (g_nextvertouchy >= 0 && g_nextvertouchy <= g_height && g_nextvertouchx >= 0 && g_nextvertouchx <= g_width)
	{
		if (ptr[(int)(g_nextvertouchy / g_tile)][(int)(g_nextvertouchx / g_tile)] == 1)
		{
			g_foundawallver = 1;
			g_verwallhity = g_nextvertouchy;
			g_verwallhitx = g_nextvertouchx;
			break;
		}
		else
		{
			g_nextvertouchy += g_ystepver;
			g_nextvertouchx += g_xstepver;
		}
	}
}

void	total_intesection_calcul()
{
	//rays_directions();
	data_gather();
	normalise_angle();
	horz_intersection_calcul();
	ver_intersection_calcul();
	g_horzdistance = (g_foundawallhorz) ? distance_between(g_new_player.pos_x, g_new_player.pos_y, g_horzwallhitx, g_horzwallhity) : INT_MAX;
	g_verdistance = (g_foundawallver) ? distance_between(g_new_player.pos_x, g_new_player.pos_y, g_verwallhitx, g_verwallhity) : INT_MAX;
	g_new_player.wallHitX = (g_horzdistance < g_verdistance) ? g_horzwallhitx : g_verwallhitx;
	g_new_player.wallHitY = (g_horzdistance < g_verdistance) ? g_horzwallhity : g_verwallhity;
	g_distance = (g_horzdistance < g_verdistance) ? g_horzdistance : g_verdistance;
	g_new_player.wasHitVertical = (g_verdistance < g_horzdistance);
	line(g_new_player.pos_x, g_new_player.pos_y, g_new_player.ray_angle, g_distance,0xFF0000);
}

void	texture_work()
{
	int k;

	g_mlx.texture_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "img1.xpm", &g_textureheight, &g_texturewidth);
	g_mlx.redbrick_data = (int *) mlx_get_data_addr(g_mlx.texture_xpm, &k, &k, &k);
}

void	total_intersection_3D(int index)
{
	int y;

	texture_work();
	// data_gather();
	// normalise_angle();
	// horz_intersection_calcul();
	// ver_intersection_calcul();
	// g_horzdistance = (g_foundawallhorz) ? distance_between(g_new_player.pos_x, g_new_player.pos_y, g_horzwallhitx, g_horzwallhity) : INT_MAX;
	// g_verdistance = (g_foundawallver) ? distance_between(g_new_player.pos_x, g_new_player.pos_y, g_verwallhitx, g_verwallhity) : INT_MAX;
	// g_new_player.wallHitX = (g_horzdistance < g_verdistance) ? g_horzwallhitx : g_verwallhitx;
	// g_new_player.wallHitY = (g_horzdistance < g_verdistance) ? g_horzwallhity : g_verwallhity;
	// g_distance = (g_horzdistance < g_verdistance) ? g_horzdistance : g_verdistance;
	// g_new_player.wasHitVertical = (g_verdistance < g_horzdistance);
	total_intesection_calcul();
	g_correctdistance = g_distance * cos(g_new_player.ray_angle - g_new_player.rotation_angle);
	g_distanceprojplane = (g_width / 2) / tan(g_new_player.FOV_angle / 2);
	g_wallstripg_height = ((g_tile / g_correctdistance) * g_distanceprojplane);
	g_walltoppixel =  (g_height / 2) - (g_wallstripg_height / 2);
	g_wallbottompixel =  (g_height / 2) + (g_wallstripg_height / 2);
	g_wallbottompixel = (g_wallbottompixel > g_height) ? g_height : g_wallbottompixel;
	g_textureoffsetx = (g_new_player.wasHitVertical) ? (int) g_new_player.wallHitY % g_tile : (int) g_new_player.wallHitX % g_tile ;
	y = 0;
	while(y < g_walltoppixel)
	{
		g_mlx.img_data[g_width * y + index] = 0xb0e0e6;
		y++;
	}
	y = g_walltoppixel;
	while (y < g_wallbottompixel)
	{
		g_distancefromtop = y + (g_wallstripg_height / 2) - (g_height / 2);
		g_textureoffsety = g_distancefromtop * ((float)(g_textureheight / g_wallstripg_height));
		g_textureoffsety = (g_textureoffsety < 0) ? 0 : g_textureoffsety;
		g_colorshading = g_mlx.redbrick_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)];
		g_mlx.img_data[(g_width * y++) + index] = g_colorshading;
	}
	y = g_wallbottompixel;
	while (y < g_height)
	{
		g_mlx.img_data[g_width * y + index] = 0xA79D9D;
		y++;
	}
}

void	project_3D_Draw()
{
	int index;

	index = 0;
	g_new_player.ray_angle = g_new_player.rotation_angle - g_new_player.FOV_angle / 2;
	while (index < g_new_player.Num_rays)
	{
		total_intersection_3D(index++);
		g_new_player.ray_angle += g_new_player.FOV_angle / g_new_player.Num_rays;
	}
}

void	player_draw()
{
	int i;
	int j;

	i = g_new_player.pos_y;
	j = g_new_player.pos_x;
	while (i < (g_new_player.pos_y + 1) * g_mini_map_factoor)
	{
		j = g_new_player.pos_x * g_mini_map_factoor;
		while (j < (g_new_player.pos_x  + 1) * g_mini_map_factoor )
		{
			g_mlx.img_data[i * g_width + j] = 0xFF0000;
			j++;
		}
		i++;
	}
}

void	map_draw()
{
	int	i;
	int	j;
	int	m;
	int	n;
	int	y;
	int	x;

	i = 0;
	j = 0;
	y = 0;
	while (i < 8)
	{
		j = 0;
		x = 0;
		while (j < 8)
		{
			if (ptr[i][j] == 1)
			{
				m = y;
				g_wall_check = 1;
				while (m < g_tile * g_mini_map_factoor + y)
				{
					n = x;
					while (n < g_tile * g_mini_map_factoor + x)
					{
						g_mlx.img_data[m * g_width + n] = 0x000000;
						n++;
					}
					m++;
				}
			}
			else
			{
				g_wall_check = 0;
				m = y;
				while (m < g_tile * g_mini_map_factoor + y - 1)
				{
					n = x;
					while (n < g_tile * g_mini_map_factoor + x - 1)
					{
						g_mlx.img_data[m * g_width + n] = 0xFFFFFF;
						n++;
					}
					m++;
				}
			}
			j++;
			x += g_tile * g_mini_map_factoor;
		}
		i++;
		y += g_tile * g_mini_map_factoor;
	}
}

void	castAllRays()
{
	int index;
	int g_rayon;
	int i;
	int j;

	index = 0;
	g_new_player.ray_angle = g_new_player.rotation_angle - g_new_player.FOV_angle / 2;
	while (index < g_new_player.Num_rays)
	{
		total_intesection_calcul();
		g_new_player.ray_angle += g_new_player.FOV_angle / g_new_player.Num_rays;
		index++;
	}
}

int		print_key(int key, void *param, void *win_ptr)
{
	int k;
	int x;
	int y;

	x = (10 * cos(g_new_player.rotation_angle));
	y = (10 * sin(g_new_player.rotation_angle));
	g_new_player.ray_angle = g_new_player.rotation_angle - g_new_player.FOV_angle / 2;
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_height, g_width);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	if (key == 53)
		exit(1);
	if (key == 126)
	{
		if (ptr[(int)(g_new_player.pos_y / g_tile)][(int)(g_new_player.pos_x / g_tile)] == 0)
		{
			if (ptr[(int)((g_new_player.pos_y + 10 ) / g_tile)][(int)(g_new_player.pos_x / g_tile)] != 1)
			{
				g_new_player.pos_y += y;
				g_new_player.pos_x += x;
			}
		}
	}
	if (key == 125)
	{
		if (ptr[(int)(g_new_player.pos_y / g_tile)][(int)(g_new_player.pos_x / g_tile)] != 1)
		{
			if (ptr[(int)((g_new_player.pos_y - 10) / g_tile)][(int)(g_new_player.pos_x / g_tile)] == 0)
			{
				g_new_player.pos_y -= y;
				g_new_player.pos_x -= x;
			}
		}
	}
	if (key == 123)
	{
		if (ptr[(int)((g_new_player.pos_y) / g_tile)][(int)((g_new_player.pos_x ) / g_tile)] == 0)
		{
			g_new_player.rotation_angle += 0.1;
			g_new_player.ray_angle += g_new_player.FOV_angle / g_new_player.Num_rays;
		}
	}
	if (key == 124)
	{
		if (ptr[(int)(g_new_player.pos_y / g_tile)][(int)((g_new_player.pos_x) / g_tile)] == 0)
		{
			g_new_player.rotation_angle -= 0.1;
			g_new_player.ray_angle -= g_new_player.FOV_angle / g_new_player.Num_rays;
		}
	}
	//map_draw();
	//player_draw();
	//castAllRays();
	project_3D_Draw();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	return (0);
}

int		update()
{
	double	move_step;
	int		k;


	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_height, g_width);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	g_new_player.rotation_angle += g_new_player.turn_direction * g_new_player.rotation_speed;
	move_step = g_new_player.walk_direction * g_move_speed;
	g_new_player.pos_x += cos(g_new_player.rotation_angle) * move_step;
	g_new_player.pos_y += sin(g_new_player.rotation_angle) * move_step;
	map_draw();
	player_draw();
	line(g_new_player.pos_x, g_new_player.pos_y, g_new_player.rotation_angle, 50, 0x00FFFF);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	//mlx_hook(g_mlx.win_ptr,2, 1L<<0, key_pressed, (void *)0);
	return 0;
}

int		key_pressed(int key ,void *param, void *wind_ptr)
{
	//update();
	if (key == 53)
		exit(1);
	if(key == 126)
	{
		g_new_player.walk_direction += 1;
		update();
	}
	if(key == 125)
	{
		g_new_player.walk_direction -= 1;
		update();
	}
	if(key == 123)
	{
		g_new_player.turn_direction += 1;
		update();
	}
	if(key == 124)
	{
		g_new_player.turn_direction -= 1;
		update();
	}
	//update();
	return 0;
}

/*int		key_released(int key)
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
}*/

int		main()
{
	int k;

	data_gather();
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_height, g_width, "cub3d");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_height, g_width);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	player_config();
	map_draw();
	//player_draw();
	line(g_new_player.pos_x, g_new_player.pos_y, g_new_player.rotation_angle, 50,0xFF0000);
	//castAllRays();
	project_3D_Draw();
	//update();
	mlx_hook(g_mlx.win_ptr,2, 1L<<0, print_key, (void *)0);
	//mlx_hook(g_mlx.win_ptr,2, 1L<<0, key_released, (void *)0);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	//mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
	mlx_loop(g_mlx.mlx_ptr);
}
