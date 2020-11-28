#include "cub3d.h"

void get_image()
{
	int k;

	g_tex.texture_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "images/img1.xpm", &g_textureheight, &g_texturewidth);
	g_tex.redbrick_data = (int *) mlx_get_data_addr(g_tex.texture_xpm, &k, &k, &k);
	//////////////////////////////////
	g_tex.texture1_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "images/redbrick.xpm", &g_textureheight, &g_texturewidth);
	g_tex.redbrick_data2 = (int *) mlx_get_data_addr(g_tex.texture1_xpm, &k, &k, &k);
	//////////////////////////////////
	g_tex.texture2_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "images/eagle.xpm", &g_textureheight, &g_texturewidth);
	g_tex.eagle_data = (int *) mlx_get_data_addr(g_tex.texture2_xpm, &k, &k, &k);
	//////////////////////////////////
	g_tex.texture3_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, "images/grey_stone.xpm", &g_textureheight, &g_texturewidth);
	g_tex.grey_stone_data = (int *) mlx_get_data_addr(g_tex.texture3_xpm, &k, &k, &k);
	//////////////////////////////////
	g_sp_image.image = mlx_xpm_file_to_image(g_mlx.mlx_ptr,"images/barrel.xpm" , &(g_sp_image.width), &(g_sp_image.height));
	g_sp_image.data = (int *)mlx_get_data_addr(g_mlx.mlx_ptr, &k, &k, &k);
}
