#include "cub3d.h"

int		g_sprite_index;

typedef struct		s_sprite
{
	int		x;
	int		y;
	float	distance;
}					t_sprite;
t_sprite			g_sprites[500];

typedef struct		s_image
{
	int		*data;
	void	*image;
	int		width;
	int		height;
	int		bpp;
	int		sl;
	int		end;
	//char	*texture;
	int		status;
}					t_image;
t_image				g_sp_image;

typedef struct		info
{
	void	*texture_xpm;
	int		*redbrick_data;
	void	*texture1_xpm;
	int		*redbrick_data2;
	void	*texture2_xpm;
	int		*eagle_data;
	void	*texture3_xpm;
	int		*grey_stone_data;

}					t_info;
t_info				g_tex;

typedef struct		files_tex_get
{
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	char	*sp_tex;
}					t_files_tex;
t_files_tex			g_files_tex;


void	add_sprite(void);
void	draw_sprites(int x, double height);
void	swap(int i);
void	sort_sprites(void);
void	render_sprite(void);
void	get_image();