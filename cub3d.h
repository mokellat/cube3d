/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:39:11 by mokellat          #+#    #+#             */
/*   Updated: 2020/03/14 20:27:53 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stdarg.h>
# include <limits.h>
# include "mlx.h"
# include <stdbool.h>
# include <math.h>

int     x;
int     y;
int     height;
int     width;
int     wall_check;
int     tile;
int     nbr_rows;
int     nbr_cols;
int     xinteruptHorz;
int     yinteruptHorz;
int     xstepHorz;
int     ystepHorz;
int     xinteruptVer;
int     yinteruptVer;
int     xstepVer;
int     ystepVer;
int     nextHorzTouchX;
int     nextHorzTouchY;
int     foundAwallHorz;
int     horzWallHitX;
int     horzWallHitY;
int     nextVerTouchX;
int     nextVerTouchY;
int     foundAwallVer;
int     verWallHitX;
int     verWallHitY;
int     horzDistance;
int     verDistance;
int     rayon;
double     proof;

int ptr[8][8]= {{1,1,1,1,1,1,1,1},
                     {1,0,0,0,0,0,0,1},
                     {1,0,0,0,0,1,0,1},
                     {1,0,0,0,0,0,0,1},
                     {1,0,1,0,0,1,0,1},
                     {1,0,0,0,1,0,0,1},
                     {1,0,0,1,0,0,0,1},
                     {1,1,1,1,1,1,1,1}};
                     
typedef struct  s_player 
{
    int     pos_x;
    int     pos_y;
    int     radius;
    int     turn_direction;
    int     walk_direction;
    double  rotation_angle;
    double  FOV_angle;
    int     Num_rays;
    int     wall_width;
    double  ray_angle;
    bool    ray_up;
    bool    ray_down;
    bool    ray_left;
    bool    ray_right;
    int     wallHitX;
    int     wallHitY;
    int     Distance;
    bool    wasHitVertical;
}               t_player;

t_player    new_player;

typedef struct s_mlx
{
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img_ptr;
    int         *img_data;
    
}           t_mlx;
t_mlx       g_mlx;
#endif