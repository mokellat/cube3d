#include "cub3d.h"

void	player_direc()
{
	int	i;
	int k;

	i = -1;

	while(++i < g_count)
	{
		k = 0;
		while (k < (int)ft_strlen(g_map[i]))
		{
			if(g_map[i][k] == 'N')
				g_new_player.FOV_angle = M_PI / 2;
			else if(g_map[i][k] == 'W')
				g_new_player.FOV_angle = -1 * M_PI;
			else if(g_map[i][k] == 'E')
				g_new_player.FOV_angle = M_PI;
			else if(g_map[i][k] == 'S')
				g_new_player.FOV_angle = -1 * M_PI / 2;
		}

	}
}
