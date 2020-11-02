/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:39:11 by mokellat          #+#    #+#             */
/*   Updated: 2020/11/02 14:45:17 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include "mlx.h"
#include <stdbool.h>
#include <math.h>
//#include "./ft_printf/libftprintf.h"

int x;
int y;
int height;
int width;
int wall_check;
int tile;
int nbr_rows;
int nbr_cols;
double xinteruptHorz;
double yinteruptHorz;
double xstepHorz;
double ystepHorz;
double xinteruptVer;
double yinteruptVer;
double xstepVer;
double ystepVer;
double nextHorzTouchX;
double nextHorzTouchY;
int foundAwallHorz;
double horzWallHitX;
double horzWallHitY;
double nextVerTouchX;
double nextVerTouchY;
int foundAwallVer;
double verWallHitX;
double verWallHitY;
double horzDistance;
double verDistance;
double Distance;
int rayon;
double proof;
double Mini_map_factoor;
double distanceProjPlane;
double wallStripHeight;
int colorShading;
int     textureHeight;
int     textureWidth;
 double  correctDistance;
int     wallTopPixel;
int     wallBottomPixel;
int     textureOffSetY;
int    textureOffSetX;
int     textIndex;
int     DistanceFromTop;
     
int ptr[8][8] = {{1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 0, 0, 0, 0, 1, 0, 1},
                 {1, 0, 0, 0, 0, 0, 0, 1},
                 {1, 1, 0, 0, 0, 0, 1, 1},
                 {1, 0, 1, 0, 0, 1, 0, 1},
                 {1, 0, 1, 0, 1, 0, 0, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    int radius;
    int turn_direction;
    int walk_direction;
    double rotation_angle;
    double FOV_angle;
    int Num_rays;
    int wall_width;
    double ray_angle;
    bool ray_up;
    bool ray_down;
    bool ray_left;
    bool ray_right;
    int wallHitX;
    int wallHitY;
    bool wasHitVertical;
} t_player;

t_player new_player;

typedef struct s_mlx
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int *img_data;
    void *texture_xpm;
    int *redbrick_data;
} t_mlx;
t_mlx g_mlx;
#endif