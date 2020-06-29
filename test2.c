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

double  normalise_angle(double angle)
{
    if(angle < 0)
        angle = 2 * M_PI + angle;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI; 
    return (angle);
}

double  distance_between(int x1, int y1, int x2, int y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    rays_directions()
{
    new_player.ray_up = new_player.ray_angle > 0 && new_player.ray_angle < M_PI;
    new_player.ray_down = !(new_player.ray_up);
    new_player.ray_right = new_player.ray_angle <  M_PI * 0.5 || new_player.ray_angle > M_PI * 1.5;
    new_player.ray_left = !(new_player.ray_right);
}

void    horz_intersection_calcul()
{
    rays_directions();
    foundAwallHorz = 0;
    horzWallHitX = 0;
    horzWallHitY = 0;
    yinterupt = floor(new_player.pos_y / tile) * tile;
    yinterupt += new_player.ray_down ? tile : 0;
    xinterupt = new_player.pos_x + ((yinterupt - new_player.pos_y) / tan(new_player.ray_angle));
    ystep = tile;
    ystep *= new_player.ray_up ? -1 : 1;
    xstep = ystep / tan(new_player.ray_angle);
    xstep *= new_player.ray_left && xstep > 0 ? -1 : 1;
    xstep *= new_player.ray_right && xstep < 0 ? -1 : 1;
    nextHorzTouchX = xinterupt;
    nextHorzTouchY = yinterupt;
    if(new_player.ray_up)
        nextHorzTouchY--;
    while(nextHorzTouchY >= 0 && nextHorzTouchY <= width && nextHorzTouchX >= 0 && nextHorzTouchX <= height)
    {
        if(ptr[nextHorzTouchX / tile][nextHorzTouchY / tile] == 1)
        {
            foundAwallHorz = 1;
            horzWallHitY = nextHorzTouchY;
            horzWallHitX = nextHorzTouchX;
            break ;   
        }
        else
        {
            nextHorzTouchY += ystep;
            nextHorzTouchX += xstep;
        }   
    }
}

void    ver_intersection_calcul()
{
    rays_directions();
    foundAwallVer = 0;
    verWallHitX = 0;
    verWallHitY = 0;
    xinterupt = floor(new_player.pos_x / tile) * tile;
    xinterupt += new_player.ray_right ? tile : 0;
    yinterupt = new_player.pos_y + ((xinterupt - new_player.pos_x) * tan(new_player.ray_angle));
    xstep = tile;
    xstep *= new_player.ray_left ? -1 : 1;
    ystep = tile * tan(new_player.ray_angle);
    ystep *= new_player.ray_up && ystep > 0 ? -1 : 1;
    ystep *= new_player.ray_down && ystep < 0 ? -1 : 1;
    nextVerTouchX = xinterupt;
    nextVerTouchY = yinterupt;
    if(new_player.ray_up)
        nextVerTouchX--;
    while(nextVerTouchY >= 0 && nextVerTouchY <= width && nextVerTouchX >= 0 && nextVerTouchX <= height)
    {
        if(ptr[nextVerTouchX / tile][nextVerTouchY / tile] == 1)
        {
            foundAwallVer = 1;
            verWallHitY = nextVerTouchY;
            verWallHitX = nextVerTouchX;
            break ;   
        }
        else
        {
            nextVerTouchY += ystep;
            nextVerTouchX += xstep;
        }   
    }
}

void    total_intesection_calcul()
{
    horz_intersection_calcul();
    ver_intersection_calcul();
    horzDistance = (foundAwallHorz) ? distance_between(new_player.pos_x, new_player.pos_y, horzWallHitX, horzWallHitY) : INT_MAX;
    verDistance = (foundAwallVer) ? distance_between(new_player.pos_x, new_player.pos_y, verWallHitX, verWallHitY) : INT_MAX;
    new_player.wallHitX = (horzDistance < verDistance) ? horzWallHitX : verWallHitX;
    new_player.wallHitY = (horzDistance < verDistance) ? horzWallHitY : verWallHitY;
    new_player.Distance = (horzDistance < verDistance) ? horzDistance : verDistance;
    new_player.wasHitVertical = (verDistance < horzDistance);
    //line(new_player.ray_angle);
    //line_draw(new_player.pos_x, new_player.pos_y, new_player.wallHitX, new_player.wallHitY);
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