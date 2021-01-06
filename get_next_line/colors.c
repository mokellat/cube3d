#include "../cub3d.h"

void    colors_tre_floor(char **g_lines, int k, int i)
{
	k = 2;
	while(g_lines[i][k] != ',')
	{
		g_file.color_r_f = ft_atoi(&g_lines[i][k]);
		break;
	}
	while(g_lines[i][k] != ',')
		k++;
	while(g_lines[i][++k] != ',')
	{
		g_file.color_g_f = ft_atoi(&g_lines[i][k]);
		break;
	}
	while(g_lines[i][k] != ',')
		k++;
	while(g_lines[i][++k])
	{
		g_file.color_b_f = ft_atoi(&g_lines[i][k]);
		break;
	}
}

void	colors_tre_ceilling(char **g_lines, int k, int i)
{
	k = 2;
	while(g_lines[i][k] != ',')
	{
		g_file.color_r_c = ft_atoi(&g_lines[i][k]);
		break;
	}
	while(g_lines[i][k] != ',')
		k++;
	while(g_lines[i][++k] != ',')
	{
		g_file.color_g_c = ft_atoi(&g_lines[i][k]);
		break;
	}
	while(g_lines[i][k] != ',')
		k++;
	while(g_lines[i][++k])
	{
		g_file.color_b_c = ft_atoi(&g_lines[i][k]);
		break;
	}
}
