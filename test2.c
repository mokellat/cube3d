#include "cub3d.h"

void    data_gather()
{
    tile = 50;
    width = tile * 8;
    height = tile * 8;
}

void    player_config()
{
    data_gather();
    new_player.pos_x = width / 2;
    new_player.pos_y = height / 2;
    new_player.turn_direction = 0;
    new_player.walk_direction = 0;
    new_player.rotation_angle = M_PI / 2;
    new_player.FOV_angle = M_PI / 3;
    new_player.wall_width = 30;
    new_player.Num_rays = width / new_player.wall_width;
    new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    wall_check = 0;
}

void    player_draw()
{
    int i;
    int j;

    i = new_player.pos_y;
    j = new_player.pos_x;
    while(i < new_player.pos_y + 10)
    {
        j = new_player.pos_x;
        while(j < new_player.pos_x + 10)
        {
            g_mlx.img_data[i * width + j] = 0xFF0000;
            j++;
        }
        i++;
    }
}

void    line_draw(double angle, int color)
{
    int i;
    int j;
    int rayon;

    rayon = 100;
    while(rayon--)
    {
        j = cos(angle) * rayon + new_player.pos_x + 5;
        i = sin(angle) * rayon + new_player.pos_y + 5 ; 
        g_mlx.img_data[i * width + j] = color;
    }
}

void    map_draw()
{
    int i;
    int j;
    int m;
    int n;

    i = 0;
    j = 0;
    y = 0;
    //data_gather();
    while(i < 8)
    {
        j = 0;
        x = 0;
        while(j < 8)
        {
          if(ptr[i][j] == 1)
          {   
                m = y;
                wall_check = 1;
                while(m < tile + y)
                {
                    n = x;
                    while(n < tile + x)
                    {
                        g_mlx.img_data[m * width + n] = 0xFFFFFF;
                        n++;
                    }
                    m++;
                }
          }
          else
          {
                wall_check = 0;
                m = y;
                while(m < tile + y)
                {
                    n = x;
                    while(n < tile + x)
                    {
                        g_mlx.img_data[m * width + n] = 0x000000;
                        n++;
                    }
                    m++;
                }
          }
            j++;
            x += tile;
        }
        i++;
        y += tile; 
    }
}

void    castAllRays()
{
    int     col_id;
    int     index;
    int     rayon;
    int     i;
    int     j;

    index = 0;
    //new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    while(index < new_player.Num_rays)
    {
        line_draw(new_player.ray_angle, 0x0000FF);
        new_player.ray_angle += new_player.FOV_angle / new_player.Num_rays;
        index++;
    }
}

int     print_key(int key, void *param, void *win_ptr)
{
    int     k;
    int     x;
    int     y;

    x = 10 * cos(new_player.rotation_angle);
    y = 10 * sin(new_player.rotation_angle);
    new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, height, width);
    g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
    if(key == 65307)
        exit(1);
    if(key == 65364)
    {
        if(ptr[(new_player.pos_y) / tile][new_player.pos_x / tile] == 0)
        {
            if(ptr[(new_player.pos_y + 10) / tile][new_player.pos_x / tile] != 1)
            {
                new_player.pos_y += y;
                new_player.pos_x += x;
            }
        }
    }
    if(key == 65362)
    {
        if(ptr[new_player.pos_y / tile][new_player.pos_x / tile] == 0 )
        {
            if(ptr[(new_player.pos_y - 10) / tile][new_player.pos_x / tile] != 1)
            {
                new_player.pos_y -= y;
                new_player.pos_x -= x;
            }
        }
    }
    if(key == 65361)
    {
        if(ptr[(new_player.pos_y ) / tile][(new_player.pos_x ) / tile ] == 0)
        {
            new_player.rotation_angle += 0.3;
            new_player.ray_angle += new_player.FOV_angle / new_player.Num_rays;
        }
    }
    if(key == 65363)
    {
        if(ptr[new_player.pos_y / tile][(new_player.pos_x) / tile] == 0)
        {
            new_player.rotation_angle -= 0.3;
            new_player.ray_angle -= new_player.FOV_angle / new_player.Num_rays;
        }
    }
    map_draw();
    player_draw();
    line_draw(new_player.rotation_angle, 0xFF0000);
    castAllRays();
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    //mlx_destroy_image(g_mlx.mlx_ptr, g_mlx.img_ptr);
    return (0);
}

int     main()
{
    int         k;
    int         i;
    int         j;
    int         m;
    int         n;

    data_gather();
    g_mlx.mlx_ptr = mlx_init();
    g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, height, width, "cub3d");
    g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, height, width);
    g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
    //map draw                 
    map_draw();
    // triangle draw
    player_config();
    player_draw();
    line_draw(new_player.rotation_angle, 0xFF0000);
    castAllRays();
    mlx_key_hook(g_mlx.win_ptr, print_key, (void *)0);
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    mlx_loop(g_mlx.mlx_ptr);
}