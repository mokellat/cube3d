#include "cub3d.h"

int		main(int argc, char **argv)
{
	int k;

	parsing();
	player_config();
	g_sp_image.image = NULL;
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_width, g_height, "cub3d");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_width, g_height);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	get_image();
	file_errors();
	if(!map_parsing())
		error(EXIT_FAILURE, "map is invalid");
	if(argc > 3)
		error(EXIT_FAILURE, "There is more then two arguments");
	if(argc < 2)
		error(EXIT_FAILURE, "arguments are invalid");
	if(argc == 3)
		if(ft_strcmp(argv[2], "--save") == 0)
		{
			update();
			screenshot();
		}
	mlx_hook(g_mlx.win_ptr,2, 1L<<0, key_pressed, (void *)0);
	mlx_hook(g_mlx.win_ptr,3, 1L<<1, key_released, (void *)0);
	mlx_loop_hook(g_mlx.mlx_ptr, update, (void *)0);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	mlx_loop(g_mlx.mlx_ptr);
}
