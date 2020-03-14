#include "cub3d.h"

void    player_config()
{
    new_player.pos_x = 400;
    new_player.pos_y = 400;
    new_player.turn_direction = 0;
    new_player.walk_direction = 0;
    new_player.rotation_angle = M_PI / 2;
    wall_check = 0;
}

void    triangle_draw()
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

void    line_draw()
{
    int i;
    int j;
    int rayon;

    rayon = 40;
    while(rayon--)
    {
        j = cos(new_player.rotation_angle) * rayon + new_player.pos_x;
        i = sin(new_player.rotation_angle) * rayon + new_player.pos_y; 
        g_mlx.img_data[i * width + j] = 0xFF0000;
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
                while(m < 100 + y)
                {
                    n = x;
                    while(n < 100 + x)
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
                while(m < 100 + y)
                {
                    n = x;
                    while(n < 100 + x)
                    {
                        g_mlx.img_data[m * width + n] = 0x000000;
                        n++;
                    }
                    m++;
                }
          }
            j++;
            x += 100;
        }
        i++;
        y += 100; 
    }
}

int     print_key(int key, void *param, void *win_ptr)
{
    int     k;
    int     x;
    int     y;

    x = 10 * cos(new_player.rotation_angle);
    y = 10 * sin(new_player.rotation_angle);

    g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, height, width);
    g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
    if(key == 53)
        exit(1);
    else if(key == 126)
    {
        if(ptr[(new_player.pos_y) /100][new_player.pos_x / 100] != 1)
        {
            new_player.pos_y += y;
            new_player.pos_x += x;
        }
    }
    else if(key == 125)
    {
        if(ptr[(new_player.pos_y) /100] [new_player.pos_x / 100] != 1)
        {
            new_player.pos_y -= y;
            new_player.pos_x -= x;
        }
    }
    else if(key == 124)
    {
        if(ptr[(new_player.pos_y) /100][(new_player.pos_x + 4) / 100 ] != 1)
            new_player.rotation_angle += 0.1;   
    }
    else if(key == 123)
    {
        if(ptr[new_player.pos_y /100][(new_player.pos_x - 4) / 100 ] != 1)
            new_player.rotation_angle += 0.1;
    }
    map_draw();
    triangle_draw();
    line_draw();
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

    height = 800;
    width = 800;
    g_mlx.mlx_ptr = mlx_init();
    g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, height, width, "cub3d");
    g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, height, width);
    g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
    //map draw                 
    map_draw();
    // triangle draw
    player_config();
    triangle_draw();
    line_draw();
    mlx_hook(g_mlx.win_ptr, 2, 0, print_key, (void *)0);
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    mlx_loop(g_mlx.mlx_ptr);
}