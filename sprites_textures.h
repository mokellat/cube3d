/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_textures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:53:19 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/08 15:09:27 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_TEXTURES_H
# define SPRITES_TEXTURES_H

# include "cub3d.h"

typedef struct		s_sprite
{
	int				x;
	int				y;
	float			distance;
}					t_sprite;
t_sprite			g_sprites[500];

typedef struct		s_image
{
	int				*data;
	void			*image;
	int				width;
	int				height;
	int				bpp;
	int				sl;
	int				end;
	int				status;
}					t_image;
t_image				g_sp_image;

typedef struct		s_info
{
	void			*texture_xpm;
	int				*redbrick_data;
	void			*texture1_xpm;
	int				*redbrick_data2;
	void			*texture2_xpm;
	int				*eagle_data;
	void			*texture3_xpm;
	int				*grey_stone_data;

}					t_info;
t_info				g_tex;

typedef struct		s_files_tex_get
{
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			*ea_tex;
	char			*sp_tex;
}					t_files_tex;
t_files_tex			g_files_tex;

int					g_spr_x;
int					g_spr_y;
int					g_place_hold[INT_MAX];
double				g_angle;
double				g_sprite_height;
int					g_column_index;
int					g_sprite_index;
void				add_sprite(void);
void				draw_sprites(int x, double distance, double height);
void				replace(int i);
void				sprites_sort(void);
void				render_sprite(void);
void				get_image();
double				distance(double x, double y);
void				draw_one_pixel(int y, int x, double color);
void				normalise_rotation_angle();
#endif
