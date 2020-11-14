#include "cub3d.h"

int		main()
{
	int k;

	player_config();
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_height, g_width, "cub3d");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_height, g_width);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	g_mlx.texture_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "images/img1.xpm", &g_textureheight, &g_texturewidth);
	g_mlx.redbrick_data = (int *) mlx_get_data_addr(g_mlx.texture_xpm, &k, &k, &k);
	mlx_hook(g_mlx.win_ptr,2, 1L<<0, key_pressed, (void *)0);
	mlx_hook(g_mlx.win_ptr,3, 1L<<1, key_released, (void *)0);
	mlx_loop_hook(g_mlx.mlx_ptr, update, (void *)0);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	mlx_loop(g_mlx.mlx_ptr);
}
