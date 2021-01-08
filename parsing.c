#include "cub3d.h"

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
	k = 0;
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
		if(g_lines[i][0] == '\0')
			indexx++;
		if(g_lines[i][0] == 'R')
			R_exec(&k, i, &indexx, x);
		else if(g_lines[i][0] == 'N' && g_lines[i][1] == 'O')
			g_files_tex.no_tex = textures_work(&k, &indexx, i);
		else if(g_lines[i][0] == 'S' && g_lines[i][1] == 'O')
			g_files_tex.so_tex = textures_work(&k, &indexx, i);
		else if(g_lines[i][0] == 'W' && g_lines[i][1] == 'E')
			g_files_tex.we_tex = textures_work(&k, &indexx, i);
		else if(g_lines[i][0] == 'E' && g_lines[i][1] == 'A')
			g_files_tex.ea_tex = textures_work(&k, &indexx, i);
		else if(g_lines[i][0] == 'S')
			g_files_tex.sp_tex = textures_work(&k, &indexx, i);
		else if(g_lines[i][0] == 'F')
		{
			colors_tre_floor(g_lines, k, i);
			indexx++;
		}
		else if(g_lines[i][0] == 'C')
		{
			colors_tre_ceilling(g_lines, k, i);
			indexx++;
		}
		else if((g_lines[i][0] == '1' || g_lines[i][0] == '0' || g_lines[i][0] == ' '
		|| g_lines[i][0] == '\0') && i >= indexx)
		{
			count++;
			g_map = realloc(g_map, count * sizeof(g_lines[i]));
			g_map[count - 1] = g_lines[i];
		}
		i++;
	}
}
