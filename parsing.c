#include "cub3d.h"

void parsing(void)
{
	int	i;
	int	k;
	int	fd;
	int	j;
	int index;
	//char *ptr[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};

	i = 1;
	j = 0;
	index = 0;
	count = 0;
	fd = open("./file.cub", O_RDONLY);
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
			index++;
		if(g_lines[i][0] == 'R')
		{
			k = 2;
			while(g_lines[i][k] != ' ')
			{
				g_file.height = ft_atoi(&g_lines[i][k]);
				index++;
				break;
			}
			while(g_lines[i][k] != ' ')
				k++;
			while(g_lines[i][k + 1] != '\0')
			{
				g_file.width = ft_atoi(&g_lines[i][k]);
				break;
			}
		}
		else if(g_lines[i][0] == 'N' && g_lines[i][1] == 'O')
		{
			k = 2;
			index++;
			while(g_lines[i][k++] != '\0')
			{
				g_files_tex.no_tex = &g_lines[i][k];
				break;
			}
		}
		else if(g_lines[i][0] == 'S' && g_lines[i][1] == 'O')
		{
			k = 2;
			index++;
			while(g_lines[i][k++] != '\0')
			{
				g_files_tex.so_tex = &g_lines[i][k];
				break;
			}
		}
		else if(g_lines[i][0] == 'W' && g_lines[i][1] == 'E')
		{
			k = 2;
			index++;
			while(g_lines[i][k++] != '\0')
			{
				g_files_tex.we_tex = &g_lines[i][k];
				break;
			}
		}
		else if(g_lines[i][0] == 'E' && g_lines[i][1] == 'A')
		{
			k = 2;
			index++;
			while(g_lines[i][k++] != '\0')
			{
				g_files_tex.ea_tex = &g_lines[i][k];
				break;
			}
		}
		else if(g_lines[i][0] == 'S')
		{
			k = 1;
			index++;
			while(g_lines[i][k++] != '\0')
			{
				g_files_tex.sp_tex = &g_lines[i][k];
				break;
			}
		}
		else if(g_lines[i][0] == 'F')
		{
			colors_tre_floor(g_lines, k, i);
			index++;
		}
		else if(g_lines[i][0] == 'C')
		{
			colors_tre_ceilling(g_lines, k, i);
			index++;
		}
		else if((g_lines[i][0] == '1' || g_lines[i][0] == '0' || g_lines[i][0] == ' '
		|| g_lines[i][0] == '\0') && i >= index)
		{
			count++;
			g_map = realloc(g_map, count * sizeof(g_lines[i]));
			g_map[count - 1] = g_lines[i];
		}
		i++;
	}
}
