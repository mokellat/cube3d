#include "cub3d.h"

double	player_direc()
{
	int		i;
	int		k;
	double	return_val;
	char	ii;

	i = -1;
	return_val = 0;

	while(++i < g_count)
	{
		k = 0;
		while (k < (int)ft_strlen(g_map[i]))
		{
			ii = g_map[i][k];
			if(g_map[i][k] == 'N')
				return_val = M_PI / 2;
			else if(g_map[i][k] == 'W')
				return_val = -1 * M_PI;
			else if(g_map[i][k] == 'E')
				return_val = M_PI;
			else if(g_map[i][k] == 'S')
				return_val = -1 * M_PI / 2;
			k++;
		}
	}
	return (return_val);
}
