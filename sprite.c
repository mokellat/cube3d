#include "cub3d.h"

void	sprite_pos()
{
	int	i;
	int	j;

	i = 0;
	while(i < g_count)
	{
		j = 0;
		while (j < (int)ft_strlen(g_map[i]))
		{
			if(g_map[i][j] == '2')
			{
				g_spr_x = (j + 0.5) * g_tile;
				g_spr_y = (i + 0.5) * g_tile;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites()
{
	int		d_x;
	int		d_y;
	double	distance;
	double	sprite_angle;
	double	size;
	double	x;

	sprite_pos();
	d_x = g_spr_x - g_new_player.pos_x;
	d_y = g_spr_y - g_new_player.pos_y;
	distance = sqrt(d_x * d_x + d_y * d_y);
	sprite_angle = atan2(d_x, d_y) - g_new_player.rotation_angle;
	size = g_width / (cos(sprite_angle) * distance);
	x = tan(sprite_angle) * g_width;
}
