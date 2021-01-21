#include "cub3d.h"

void	progrmm_init()
{
	g_file.height = -1;
	g_file.width = -1;
	g_file.color_r_f = -1;
	g_file.color_g_f = -1;
	g_file.color_b_f = -1;
	g_file.color_r_c = -1;
	g_file.color_g_c = -1;
	g_file.color_b_c = -1;
}

int		r_exec(int *k, int i, int *x)
{
	int		variable;

	(*k)++;
	variable = -1;
	*x = (int) g_lines[i][*k];
	while(*x < 48 || *x > 59)
	{
		if(*x == 32)
			(*k)++;
		else
			error(EXIT_FAILURE, "dimensions are invalid !");
		*x = (int) g_lines[i][*k];
	}
	variable = ft_atoi(&g_lines[i][*k]);
	return (variable);
}

void	R_exec(int *k, int i, int *indexx, int x)
{
	int	j;

	j = *k + 1;
	while(g_lines[i][j])
	{
		if(!ft_isdigit(g_lines[i][j]) && g_lines[i][j] != ' ')
			error(EXIT_FAILURE, "dimensions are invalid !");
		j++;
	}
	g_file.height = r_exec(k, i, &x);
	(*indexx)++;
	g_counter++;
	while(x >= 48 && x <= 59)
	{
		(*k)++;
		x = (int) g_lines[i][*k];
	}
	g_file.width = r_exec(k--, i, &x);
}

char	*textures_work(int *k, int *indexx, int i)
{
	char	*variable;

	variable = NULL;
	*k = *k + 2;
	while(g_lines[i][*k] == ' ')
		(*k)++;
	(*indexx)++;
	g_counter++;
	variable = &g_lines[i][*k];
	return (variable);
}
