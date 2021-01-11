#include "cub3d.h"

void	beg_errors(int j)
{
	char **ptr;
	int	i;

	i = 0;
	while(i < j)
	{
		i++;
		ptr = realloc(g_lines, i * sizeof(g_lines));
		ptr[i - 1] = ft_strtrim(g_lines[i - 1], " ");
	}
}

void parsing(void)
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
	count = 0;
	x = 0;
	k = -1;
	counter = 0;
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
				counter++;
			}
			else if(g_lines[i][k] == 'C')
			{
				colors_tre_ceilling(g_lines, k, i);
				indexx++;
				counter++;
			}
			else if((g_lines[i][k] == '1' || g_lines[i][k] == '0' || g_lines[i][k] == ' '
			|| g_lines[i][k] == '\0') && i > indexx)
			{
				count++;
				g_map = realloc(g_map, count * sizeof(g_lines[i]));
				g_map[count - 1] = g_lines[i];
				break;
			}
		}
		i++;
		k = -1;
	}
	beg_errors(j);
	// i = -1;
	// while(++i < count)
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
}

