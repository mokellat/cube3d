#include "cub3d.h"

int		main()
{
	int k;

	player_config();
	g_sp_image.image = NULL;
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_height, g_width, "cub3d");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_height, g_width);
	parsing();
	get_image();
	map_parsing();
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	mlx_hook(g_mlx.win_ptr,2, 1L<<0, key_pressed, (void *)0);
	mlx_hook(g_mlx.win_ptr,3, 1L<<1, key_released, (void *)0);
	mlx_loop_hook(g_mlx.mlx_ptr, update, (void *)0);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	mlx_loop(g_mlx.mlx_ptr);

}

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
