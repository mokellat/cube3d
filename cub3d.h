/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:39:11 by mokellat          #+#    #+#             */
/*   Updated: 2020/11/14 19:36:31 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H
#define	CUB3D_H

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

int		g_height;
int		g_width;
int		g_wall_check;
int		g_tile;
double	g_xinterupthorz;
double	g_yinterupthorz;
double	g_xstephorz;
double	g_ystephorz;
double	g_xinteruptver;
double	g_yinteruptver;
double	g_xstepver;
double	g_ystepver;
double	g_nexthorztouchx;
double	g_nexthorztouchy;
int		g_foundawallhorz;
double	g_horzwallhitx;
double	g_horzwallhity;
double	g_nextvertouchx;
double	g_nextvertouchy;
int		g_foundawallver;
double	g_verwallhitx;
double	g_verwallhity;
double	g_horzdistance;
double	g_verdistance;
double	g_distance;
int		g_rayon;
double	g_proof;
double	g_mini_map_factoor;
double	g_distanceprojplane;
double	g_wallstripg_height;
int		g_colorshading;
int		g_textureheight;
int		g_texturewidth;
double	g_correctdistance;
int		g_walltoppixel;
int		g_wallbottompixel;
int		g_textureoffsety;
int		g_textureoffsetx;
int		g_distancefromtop;
int		g_move_speed;
double	g_move_step;
int		tilecolor;
int		tilex;
int		tiley;

static int ptr[8][8] =	{{1, 1, 1, 1, 1, 1, 1, 1},
				{1, 1, 1, 1, 1, 1, 1, 1},
				{1, 0, 0, 0, 0, 1, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 1},
				{1, 1, 0, 0, 0, 0, 1, 1},
				{1, 0, 1, 0, 0, 1, 0, 1},
				{1, 0, 1, 0, 1, 0, 0, 1},
				{1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	int		radius;
	double	rotation_angle;
	double	FOV_angle;
	double	Num_rays;
	double	wall_width;
	double	ray_angle;
	bool	ray_up;
	bool	ray_down;
	bool	ray_left;
	bool	ray_right;
	double	wallHitX;
	double	wallHitY;
	bool	wasHitVertical;
	int		turn_direction;
	int		walk_direction;
	double	rotation_speed;
}	t_player;
t_player	g_new_player;
typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*img_data;
	void	*texture_xpm;
	int		*redbrick_data;
}	t_mlx;
t_mlx		g_mlx;
////////////////////////////////////////////////////////////////
void	data_gather();
void	player_config();
void	normalise_angle();
double	distance_between(int x1, int y1, int x2, int y2);
int		haswallat(double x, double y);
void	rays_directions();
void	line(int x1, int y1, double angle, int var, int color);
void	horz_intersection_calcul();
void	ver_intersection_calcul();
void	total_intesection_calcul();
void	total_intersection_3D(int index);
void	project_3D_Draw();
void	player_draw();
int		drawing_cub_walls();
void	Map();
void	castAllRays();
int		key_pressed(int key ,void *param, void *wind_ptr);
int		key_released(int key);
int		update();
void	help_inter_horz();
void	help_inter_ver();
///////////////////////////////////////////////////////////////
#include <time.h>
clock_t b;
#define TIME(x) b = clock(); x printf("time taken: %lf\n", ((double)(clock() - b) * (CLOCKS_PER_SEC / 1000000) /1000));
#endif
