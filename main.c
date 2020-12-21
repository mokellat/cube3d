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
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	mlx_hook(g_mlx.win_ptr,2, 1L<<0, key_pressed, (void *)0);
	mlx_hook(g_mlx.win_ptr,3, 1L<<1, key_released, (void *)0);
	mlx_loop_hook(g_mlx.mlx_ptr, update, (void *)0);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	mlx_loop(g_mlx.mlx_ptr);

}

void parsing(void)
{
	char *line;
	char **lines;
	int i;
	int	k;
	int fd;
	int j;
	//char *ptr[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};

	i = 1;
	j = 0;
	fd = open("./file.cub", O_RDONLY);
	while((i = get_next_line(fd, &line)))
	{
		j++;
		lines = realloc(lines, j * sizeof(line));
		lines[j - 1] = line;
	}
	i = 0;
	while (i < j)
	{
		if(lines[i][0] == 'R')
		{
			k = 2;
			while(lines[i][k] != ' ')
			{
				g_file.height = ft_atoi(&lines[i][k]);
				puts("VALUE WAS ASSIGNED");
				break;
			}
			while(lines[i][k] != ' ')
				k++;
			while(lines[i][k + 1] != '\0')
			{
				g_file.width = ft_atoi(&lines[i][k]);
				break;
			}
		}
		if(lines[i][0] == 'N' && lines[i][1] == 'O')
		{
			k = 2;
			while(lines[i][k++] != '\0')
			{
				g_files_tex.no_tex = &lines[i][k];
				break;
			}
		}
		if(lines[i][0] == 'S' && lines[i][1] == 'O')
		{
			k = 2;
			while(lines[i][k++] != '\0')
			{
				g_files_tex.so_tex = &lines[i][k];
				break;
			}
		}
		if(lines[i][0] == 'W' && lines[i][1] == 'E')
		{
			k = 2;
			while(lines[i][k++] != '\0')
			{
				g_files_tex.we_tex = &lines[i][k];
				break;
			}
		}
		if(lines[i][0] == 'E' && lines[i][1] == 'A')
		{
			k = 2;
			while(lines[i][k++] != '\0')
			{
				g_files_tex.ea_tex = &lines[i][k];
				break;
			}
		}
		if(lines[i][0] == 'S')
		{
			k = 1;
			while(lines[i][k++] != '\0')
			{
				g_files_tex.sp_tex = &lines[i][k];
				break;
			}
		}
		if(lines[i][0] == 'F')
			colors_tre_floor(lines, k, i);
		if(lines[i][0] == 'C')
			colors_tre_ceilling(lines, k, i);
		i++;
	}
	printf("%d\n", g_file.height);
	printf("%d\n", g_file.width);
	printf("%s\n", g_files_tex.no_tex);
	printf("%s\n", g_files_tex.so_tex);
	printf("%s\n", g_files_tex.we_tex);
	printf("%s\n", g_files_tex.ea_tex);
	printf("%s\n", g_files_tex.sp_tex);
	printf("%d\n", g_file.color_r_f);
	printf("%d\n", g_file.color_g_f);
	printf("%d\n", g_file.color_b_f);
	printf("%d\n", g_file.color_r_c);
	printf("%d\n", g_file.color_g_c);
	printf("%d\n", g_file.color_b_c);

}
