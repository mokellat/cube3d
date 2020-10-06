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

void    normalise_angle()
{
    if(new_player.ray_angle < 0)
        new_player.ray_angle += 2 * M_PI;
    if(new_player.ray_angle> 2 * M_PI)
        new_player.ray_angle -= 2 * M_PI; 
}

double  distance_between(int x1, int y1, int x2, int y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    rays_directions()
{
    normalise_angle();
    new_player.ray_down = ((new_player.ray_angle) > 0 && (new_player.ray_angle < M_PI));
    new_player.ray_up = !(new_player.ray_down);
    new_player.ray_left = ((new_player.ray_angle >=  M_PI) * 0.5 && (new_player.ray_angle <= M_PI * 1.5));
    new_player.ray_right = !(new_player.ray_left);
}

void    line(int x1, int y1, double angle, int var)
{
    int i;
    int j;

    rayon = var;
    while(rayon --)
    {
        proof = (angle);
        j = cos(proof) * rayon + x1 ;
        i = sin(proof) * rayon + y1 ;
        g_mlx.img_data[i * width + j] = 0x0000FF;
    }
}

void    horz_intersection_calcul()
{
    rays_directions();
    normalise_angle();
    foundAwallHorz = 0;
    horzWallHitX = 0;
    horzWallHitY = 0;
    yinteruptHorz = floor(new_player.pos_y / tile) * tile;
    yinteruptHorz += new_player.ray_down ? tile : 0;
    xinteruptHorz = new_player.pos_x + ((yinteruptHorz - new_player.pos_y) / tan(new_player.ray_angle));
    ystepHorz = tile;
    ystepHorz *= new_player.ray_up ? -1 : 1;
    xstepHorz = tile / tan(new_player.ray_angle);
    xstepHorz *= (new_player.ray_left && xstepHorz > 0) ? -1 : 1;
    xstepHorz *= (new_player.ray_right && xstepHorz < 0) ? -1 : 1;
    nextHorzTouchX = xinteruptHorz;
    nextHorzTouchY = yinteruptHorz;
    if(new_player.ray_up)
        nextHorzTouchY--;
    while(nextHorzTouchY >= 0 && nextHorzTouchY <= height && nextHorzTouchX >= 0 && nextHorzTouchX <= width)
    {
        if(ptr[nextHorzTouchY / tile][nextHorzTouchX / tile] == 1)
        {
            foundAwallHorz = 1;
            horzWallHitY = nextHorzTouchY;
            horzWallHitX = nextHorzTouchX;
            break ;   
        }
        else
        {
            nextHorzTouchY += ystepHorz;
            nextHorzTouchX += xstepHorz;
        }   
    }
}

void    ver_intersection_calcul()
{
    rays_directions();
    normalise_angle();
    foundAwallVer = 0;
    verWallHitX = 0;
    verWallHitY = 0;
    xinteruptVer = floor(new_player.pos_x / tile) * tile;
    xinteruptVer += new_player.ray_right ? tile : 0;
    yinteruptVer = new_player.pos_y + ((xinteruptVer - new_player.pos_x) * tan(new_player.ray_angle));
    xstepVer = tile;
    xstepVer *= new_player.ray_left ? -1 : 1;
    ystepVer = tile * tan(new_player.ray_angle);
    ystepVer *= (new_player.ray_up && ystepVer > 0) ? -1 : 1;
    ystepVer *= (new_player.ray_down && ystepVer < 0) ? -1 : 1;
    nextVerTouchX = xinteruptVer;
    nextVerTouchY = yinteruptVer;
    if(new_player.ray_left)
        nextVerTouchX--;
    while(nextVerTouchY >= 0 && nextVerTouchY <= height && nextVerTouchX >= 0 && nextVerTouchX <= width)
    {
        if(ptr[nextVerTouchY / tile][nextVerTouchX / tile] == 1)
        {
            foundAwallVer = 1;
            verWallHitY = nextVerTouchY;
            verWallHitX = nextVerTouchX;
            break ;   
        }
        else
        {
            nextVerTouchY += ystepVer;
            nextVerTouchX += xstepVer;
        }   
    }
}

void    total_intesection_calcul()
{
    //rays_directions();
    horz_intersection_calcul();
    ver_intersection_calcul();
    normalise_angle();
    horzDistance = (foundAwallHorz) ? distance_between(new_player.pos_x, new_player.pos_y, horzWallHitX, horzWallHitY) : INT_MAX;
    verDistance = (foundAwallVer) ? distance_between(new_player.pos_x, new_player.pos_y, verWallHitX, verWallHitY) : INT_MAX;
    new_player.wallHitX = (horzDistance < verDistance) ? horzWallHitX : verWallHitX;
    new_player.wallHitY = (horzDistance < verDistance) ? horzWallHitY : verWallHitY;
    new_player.Distance = (horzDistance < verDistance) ? horzDistance : verDistance;
    new_player.wasHitVertical = (verDistance < horzDistance);
    line(new_player.pos_x, new_player.pos_y, new_player.ray_angle, new_player.Distance);
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
                        g_mlx.img_data[m * width + n] = 0x000000;
                        n++;
                    }
                    m++;
                }
          }
          else
          {
                wall_check = 0;
                m = y;
                while(m < tile + y - 1)
                {
                    n = x;
                    while(n < tile + x - 1)
                    {
                        g_mlx.img_data[m * width + n] = 0xFFFFFF;
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
        line(new_player.pos_x, new_player.pos_y,(new_player.ray_angle), new_player.Distance);
        new_player.ray_angle += new_player.FOV_angle / new_player.Num_rays;
        index++;
    }
}

int     print_key(int key, void *param, void *win_ptr)
{
    int     k;
    int     x;
    int     y;

    x = 10 * cos(new_player.ray_angle);
    y = 10 * sin(new_player.ray_angle);
    //new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
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
    total_intesection_calcul();
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    printf("%d\n", horzDistance);
    printf("%d\n", verDistance);
    printf("%d\n",new_player.Distance);
    printf("%f\n",(new_player.ray_angle));
    printf("%d\n",new_player.ray_up);
    printf("%d\n",new_player.ray_down);
    printf("%d\n",new_player.ray_left);
    printf("%d\n",new_player.ray_right);
    printf("\n");
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
    total_intesection_calcul();
    mlx_key_hook(g_mlx.win_ptr, print_key, (void *)0);
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    mlx_loop(g_mlx.mlx_ptr);
}