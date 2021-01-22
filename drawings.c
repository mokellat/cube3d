#include "cub3d.h"

void	line(int x1, int y1, double angle, int var, int color)
{
	int i;
	int j;
    int rayon;

	rayon = var;
	while (rayon--)
	{
		j = (cos(angle) * g_rayon + x1) * g_mini_map_factoor;
		i = (sin(angle) * g_rayon + y1) * g_mini_map_factoor;
		g_mlx.img_data[i * g_width + j] = color;
	}
}

void	player_draw(double y, double x, int color)
{
	g_mlx.img_data[(int)y * g_width + (int)x] = color;
}

int		drawing_cub_walls()
{
    int x,y;
    x = g_tile + tilex;
    y = g_tile + tiley;
    while (tiley < y)
    {
        while (tilex < x)
        {
            g_mlx.img_data[tiley * g_width + tilex] = tilecolor;
            tilex++;
        }
        tilex -= g_tile;
        tiley++;
    }
    return (0);
}

void	Map()
{
    int i;
    int j;

    tilex = 0;
    tiley = 0;
    i = 0;
    while (i < g_count)
    {
        j = 0;
        while (j < (int)ft_strlen(g_map[i]))
        {
            tilex = j * g_tile;
            tiley = i * g_tile;
            if(g_map[i][j] == '1')
            {
                tilecolor = 0xFFFFFF;
                drawing_cub_walls();
            }
            else if(g_map[i][j] == '0')
            {
                tilecolor = 0x000000;
                drawing_cub_walls();
            }
            else if(g_map[i][j] == 'N')
            {
                tilecolor = 0x0000FF;
                drawing_cub_walls();
            }
            j++;
        }
        i++;
    }
}

void	project_3D_Draw()
{
	int indexx;

	indexx = 0;
	g_new_player.ray_angle = g_new_player.rotation_angle - g_new_player.FOV_angle / 2;
	while (indexx < g_new_player.Num_rays)
	{
		total_intersection_3D(indexx++);
		g_new_player.ray_angle += g_new_player.FOV_angle / g_new_player.Num_rays;
	}
}
