#include "cub3d.h"

void	R_exec(int *k, int i, int *indexx, int x)
{
	x = (int) g_lines[i][*k];
	while(x < 48 || x > 59)
	{
		(*k)++;
		x = (int) g_lines[i][*k];
	}
	g_file.height = ft_atoi(&g_lines[i][*k]);
	(*indexx)++;
	while(g_lines[i][*k] != ' ')
		(*k)++;
	g_file.width = ft_atoi(&g_lines[i][*k]);
}

char	*textures_work(int *k, int *indexx, int i)
{
	char	*variable;

	variable = NULL;
	*k = 2;
	while(g_lines[i][*k] == ' ')
		(*k)++;
	(*indexx)++;
	variable = &g_lines[i][*k];
	return (variable);
}
