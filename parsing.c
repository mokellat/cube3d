#include "cub3d.h"

void	beg_errors(int indexx)
{
	char	**ptr;
	int		i;

	i = 0;
	while(i < indexx - 1)
	{
		i++;
		ptr = realloc(ptr, i * sizeof(g_lines[i - 1]));
		ptr[i - 1] = ft_strtrim(g_lines[i - 1], " ");
		if(ptr[i - 1][0] != 'R' && ptr[i - 1][0] != 'N' && ptr[i - 1][0] != 'S' && ptr[i - 1][0] != 'W'
		&& ptr[i  - 1][0] != 'E' && ptr[i - 1][0] != 'S' && ptr[i - 1][0] != 'F' && ptr[i - 1][0] != 'C'
		&& ptr[i - 1][0] != '\0')
			error(EXIT_FAILURE, "File is invalid !");
	}
}

void	lenght_calcul()
{
	int i;

	i = 0;
	while(g_map[i] && i + 1 < g_count)
	{
		if(ft_strlen(g_map[i]) < ft_strlen(g_map[i + 1]))
			g_b_lenght = (int)ft_strlen(g_map[i + 1]);
		else
			g_b_lenght = (int)ft_strlen(g_map[i]);
		i++;
	}
}

void	parsing(void)
{
	int	i;
	int	k;
	int	fd;
	int	j;
	int x;
	int indexx;

	i = 1;
	j = 0;
	indexx = 0;
	g_count = 0;
	x = 0;
	k = -1;
	g_counter = 0;
	fd = open("./file.cub", O_RDONLY);
	progrmm_init();
	while((i = get_next_line(fd, &g_line)))
	{
		j++;
		g_lines = realloc(g_lines, j * sizeof(g_line));
		g_lines[j - 1] = g_line;
	}
	i = 0;
	while (i < j)
	{
		while(k++ < (int)ft_strlen(g_lines[i]))
		{
			if(g_lines[i][0] == '\0')
				indexx++;
			if(g_lines[i][k] == 'R')
				R_exec(&k, i, &indexx, x);
			else if(g_lines[i][k] == 'N' && g_lines[i][k + 1] == 'O')
				g_files_tex.no_tex = textures_work(&k, &indexx, i);
			else if(g_lines[i][k] == 'S' && g_lines[i][k + 1] == 'O')
				g_files_tex.so_tex = textures_work(&k, &indexx, i);
			else if(g_lines[i][k] == 'W' && g_lines[i][k + 1] == 'E')
				g_files_tex.we_tex = textures_work(&k, &indexx, i);
			else if(g_lines[i][k] == 'E' && g_lines[i][k + 1] == 'A')
				g_files_tex.ea_tex = textures_work(&k, &indexx, i);
			else if(g_lines[i][k] == 'S')
				g_files_tex.sp_tex = textures_work(&k, &indexx, i);
			else if(g_lines[i][k] == 'F')
			{
				colors_tre_floor(g_lines, k, i);
				indexx++;
				g_counter++;
			}
			else if(g_lines[i][k] == 'C')
			{
				colors_tre_ceilling(g_lines, k, i);
				indexx++;
				g_counter++;
			}
			if(i >= indexx && (g_lines[i][k] == '1' || g_lines[i][k] == '\0'))
			{
				g_count++;
				g_map = realloc(g_map, g_count * sizeof(g_lines[i]));
				g_map[g_count - 1] = g_lines[i];
				break ;
			}
		}
		i++;
		k = -1;
	}
	if(g_map == NULL)
		error(EXIT_FAILURE, "there is no map !");
	beg_errors(indexx);
	lenght_calcul();
	i = -1;
	// while(++i < g_count)
	// 	printf("%s\n", g_map[i]);
	// printf("%s\n",g_files_tex.no_tex);
	// printf("%s\n",g_files_tex.so_tex);
	// printf("%s\n",g_files_tex.we_tex);
	// printf("%s\n",g_files_tex.ea_tex);
	// printf("%s\n",g_files_tex.sp_tex);
	// printf("%d\n", g_file.height);
	// printf("%d\n", g_file.width);
	// printf("%d\n", g_file.color_r_f);
	// printf("%d\n", g_file.color_g_f);
	// printf("%d\n", g_file.color_b_f);
	// printf("%d\n", g_file.color_r_c);
	// printf("%d\n", g_file.color_g_c);
	// printf("%d\n", g_file.color_b_c);
	// g_lines[i][k] == '1' || g_lines[i][k] == '0' || g_lines[i][k] == ' '
	// 		|| g_lines[i][k] == '\0')
}
