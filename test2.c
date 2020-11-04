#include "cub3d.h"

void data_gather()
{
    Mini_map_factoor = 0.3;
    tile = 100;
    width = tile * 8;
    height = tile * 8;
    textureHeight = tile;
    textureWidth = tile;
}

void player_config()
{
    data_gather();
    new_player.pos_x = width / 2;
    new_player.pos_y = height / 2;
    new_player.turn_direction = 0;
    new_player.walk_direction = 0;
    new_player.rotation_angle = M_PI / 2;
    new_player.FOV_angle = M_PI / 3;
    new_player.wall_width = 1;
    new_player.Num_rays = width / new_player.wall_width;
    new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    wall_check = 0;
}

void normalise_angle()
{
    //new_player.ray_angle = remainder(2 * M_PI, -2 * M_PI);
    if (new_player.ray_angle < 0)
        new_player.ray_angle += 2 * M_PI;
    if (new_player.ray_angle > 2 * M_PI)
        new_player.ray_angle -= 2 * M_PI;
}

double distance_between(int x1, int y1, int x2, int y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void rays_directions()
{
    normalise_angle();
    new_player.ray_down = (new_player.ray_angle > 0 && new_player.ray_angle < M_PI);
    new_player.ray_up = !(new_player.ray_down);
    new_player.ray_left = !new_player.ray_right;
    new_player.ray_right = (new_player.ray_angle < 0.5 * M_PI || new_player.ray_angle > 1.5 * M_PI);
}

void line(int x1, int y1, double angle, int var, int color)
{
    int i;
    int j;

    rayon = var;
    while (rayon--)
    {
        j = (cos(angle) * rayon + x1) * Mini_map_factoor;
        i = (sin(angle) * rayon + y1) * Mini_map_factoor;
        g_mlx.img_data[i * width + j] = color;
    }
}

void horz_intersection_calcul()
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
    if (new_player.ray_up)
        nextHorzTouchY--;
    while (nextHorzTouchY >= 0 && nextHorzTouchY <= height && nextHorzTouchX >= 0 && nextHorzTouchX <= width)
    {
        if (ptr[(int)(nextHorzTouchY / tile)][(int)(nextHorzTouchX / tile)] == 1)
        {
            foundAwallHorz = 1;
            horzWallHitY = nextHorzTouchY;
            horzWallHitX = nextHorzTouchX;
            break;
        }
        else
        {
            nextHorzTouchY += ystepHorz;
            nextHorzTouchX += xstepHorz;
        }
    }
}

void ver_intersection_calcul()
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
    if (new_player.ray_left)
        nextVerTouchX--;
    while (nextVerTouchY >= 0 && nextVerTouchY <= height && nextVerTouchX >= 0 && nextVerTouchX <= width)
    {
        if (ptr[(int)(nextVerTouchY / tile)][(int)(nextVerTouchX / tile)] == 1)
        {
            foundAwallVer = 1;
            verWallHitY = nextVerTouchY;
            verWallHitX = nextVerTouchX;
            break;
        }
        else
        {
            nextVerTouchY += ystepVer;
            nextVerTouchX += xstepVer;
        }
    }
}

/*void rectangle_3D_draw(int x1, unsigned int y1, int x2, int y2, int color) 
{

    int m;
    int n;
    int x;
    int y;

    x = x1;
    y = y1;
    m = y;
    while (m < y2 + y && m < height)
    {
        (m < 0) ? (m = 0) : m;
        n = x;
        while (n < x2 + x && n < width)
        {
             (n < 0) ? (n = 0) : n;
            g_mlx.img_data[m * width + n] = 0xFFFFFF;
            n++;
        }
        m++;
    }
    x += x1;
    y += y1;
}*/

void total_intesection_calcul()
{
    //rays_directions();
    data_gather();
    normalise_angle();
    horz_intersection_calcul();
    ver_intersection_calcul();
    horzDistance = (foundAwallHorz) ? distance_between(new_player.pos_x, new_player.pos_y, horzWallHitX, horzWallHitY) : INT_MAX;
    verDistance = (foundAwallVer) ? distance_between(new_player.pos_x, new_player.pos_y, verWallHitX, verWallHitY) : INT_MAX;
    new_player.wallHitX = (horzDistance < verDistance) ? horzWallHitX : verWallHitX;
    new_player.wallHitY = (horzDistance < verDistance) ? horzWallHitY : verWallHitY;
    Distance = (horzDistance < verDistance) ? horzDistance : verDistance;
    new_player.wasHitVertical = (verDistance < horzDistance);
    line(new_player.pos_x, new_player.pos_y, new_player.ray_angle, Distance, 0x0000FF);

}

void texture_work()
{
    int k;
    
    g_mlx.texture_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "redbrick.xpm", &textureHeight, &textureWidth);
    g_mlx.redbrick_data = (int *) mlx_get_data_addr(g_mlx.texture_xpm, &k, &k, &k);
}

void total_intersection_3D(int index)
{
    int y;

    texture_work();
    data_gather();
    normalise_angle();
    horz_intersection_calcul();
    ver_intersection_calcul();
    horzDistance = (foundAwallHorz) ? distance_between(new_player.pos_x, new_player.pos_y, horzWallHitX, horzWallHitY) : INT_MAX;
    verDistance = (foundAwallVer) ? distance_between(new_player.pos_x, new_player.pos_y, verWallHitX, verWallHitY) : INT_MAX;
    new_player.wallHitX = (horzDistance < verDistance) ? horzWallHitX : verWallHitX;
    new_player.wallHitY = (horzDistance < verDistance) ? horzWallHitY : verWallHitY;
    Distance = (horzDistance < verDistance) ? horzDistance : verDistance;
    new_player.wasHitVertical = (verDistance < horzDistance);
    correctDistance = Distance * cos(new_player.ray_angle - new_player.rotation_angle);
    distanceProjPlane = (width / 2) / tan(new_player.FOV_angle / 2);
    wallStripHeight = ((tile / correctDistance) * distanceProjPlane);
    wallTopPixel =  (height / 2) - (wallStripHeight / 2);
    wallBottomPixel =  (height / 2) + (wallStripHeight / 2);
    textureOffSetX = (new_player.wasHitVertical) ? (int) new_player.wallHitY % tile : (int) new_player.wallHitX % tile ;
    y = 0;
    while(y < wallTopPixel)
    {
        g_mlx.img_data[width * y + index] = 0xb0e0e6;
        y++;
    }
    y = wallTopPixel;
    while (y < wallBottomPixel && textureOffSetX < height && textureOffSetY >= 0)
    {
        DistanceFromTop = y + (wallStripHeight / 2) - (height / 2);
        textureOffSetY = DistanceFromTop * ((double)(textureHeight / wallStripHeight));
        colorShading = g_mlx.redbrick_data[(int)((textureWidth * textureOffSetY) + textureOffSetX)];
        g_mlx.img_data[(width * y++) + index] = colorShading;
    }
    y = wallBottomPixel;
    while (y < height)
    {
        g_mlx.img_data[width * y + index] = 0xA79D9D;
        y++;
    }
}

void project_3D_Draw()
{
    int index;

    index = 0;
    new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    while (index < new_player.Num_rays)
    {
        total_intersection_3D(index++);
        new_player.ray_angle += new_player.FOV_angle / new_player.Num_rays;
    }
}

void player_draw()
{
    int i;
    int j;

    i = new_player.pos_y * Mini_map_factoor;
    j = new_player.pos_x * Mini_map_factoor;
    while (i < (new_player.pos_y + 10) * Mini_map_factoor)
    {
        j = new_player.pos_x * Mini_map_factoor;
        while (j < (new_player.pos_x  + 10 ) * Mini_map_factoor )
        {
            g_mlx.img_data[i * width + j] = 0xFF0000;
            j++;
        }
        i++;
    }
}

void map_draw()
{
    int i;
    int j;
    int m;
    int n;

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
                wall_check = 1;
                while (m < tile * Mini_map_factoor + y)
                {
                    n = x;
                    while (n < tile * Mini_map_factoor + x)
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
                while (m < tile * Mini_map_factoor + y - 1)
                {
                    n = x;
                    while (n < tile * Mini_map_factoor + x - 1)
                    {
                        g_mlx.img_data[m * width + n] = 0xFFFFFF;
                        n++;
                    }
                    m++;
                }
            }
            j++;
            x += tile * Mini_map_factoor;
        }
        i++;
        y += tile * Mini_map_factoor;
    }
}

void castAllRays()
{
    int index;
    int rayon;
    int i;
    int j;

    index = 0;
    new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    while (index < new_player.Num_rays)
    {
        total_intesection_calcul();
        new_player.ray_angle += new_player.FOV_angle / new_player.Num_rays;
        index++;
    }
}

int print_key(int key, void *param, void *win_ptr)
{
    int k;
    int x;
    int y;

    x = (10 * cos(new_player.rotation_angle));
    y = (10 * sin(new_player.rotation_angle));
    new_player.ray_angle = new_player.rotation_angle - new_player.FOV_angle / 2;
    g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, height, width);
    g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
    if (key == 53)
        exit(1);
    if (key == 126)
    {
        if (ptr[(int)((new_player.pos_y) / tile)][(int)(new_player.pos_x / tile)] == 0)
        {
            if (ptr[(int)((new_player.pos_y + 10 * Mini_map_factoor) / tile)][(int)(new_player.pos_x / tile)] != 1)
            {
                new_player.pos_y += y;
                new_player.pos_x += x;
            }
        }
    }
    if (key == 125)
    {
        if (ptr[(int)(new_player.pos_y / tile)][(int)(new_player.pos_x / tile)] != 1)
        {
            if (ptr[(int)((new_player.pos_y - 10 * Mini_map_factoor) / tile)][(int)(new_player.pos_x / tile)] == 0)
            {
                new_player.pos_y -= y;
                new_player.pos_x -= x;
            }
        }
    }
    if (key == 123)
    {
        if (ptr[(int)((new_player.pos_y) / tile)][(int)((new_player.pos_x) / tile)] == 0)
        {
            new_player.rotation_angle += 0.2;
            new_player.ray_angle += new_player.FOV_angle / new_player.Num_rays;
        }
    }
    if (key == 124)
    {
        if (ptr[(int)(new_player.pos_y / tile)][(int)((new_player.pos_x) / tile)] == 0)
        {
            new_player.rotation_angle -= 0.2;
            new_player.ray_angle -= new_player.FOV_angle / new_player.Num_rays;
        }
    }
    map_draw();
    player_draw();
    line(new_player.pos_x, new_player.pos_y, new_player.rotation_angle, 50, 0xFF0000);
    castAllRays();
    project_3D_Draw();
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    return (0);
}

int main()
{
    int k;
    
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
    line(new_player.pos_x, new_player.pos_y, new_player.rotation_angle, 50, 0xFF0000);
    castAllRays();
    project_3D_Draw();
    mlx_key_hook(g_mlx.win_ptr, print_key, (void *)0);
    mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
    mlx_loop(g_mlx.mlx_ptr);
}