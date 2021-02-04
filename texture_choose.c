#include "cub3d.h"

void get_image()
{
	int k;

	g_tex.texture_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_files_tex.no_tex, &g_textureheight, &g_texturewidth);
	g_tex.texture1_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_files_tex.so_tex, &g_textureheight, &g_texturewidth);
	g_tex.texture2_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_files_tex.we_tex, &g_textureheight, &g_texturewidth);
	g_tex.texture3_xpm = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_files_tex.ea_tex, &g_textureheight, &g_texturewidth);
	g_sp_image.image = mlx_xpm_file_to_image(g_mlx.mlx_ptr,g_files_tex.sp_tex , &(g_sp_image.width), &(g_sp_image.height));
	if(g_tex.texture_xpm && g_tex.texture1_xpm && g_tex.texture2_xpm && g_tex.texture3_xpm && g_sp_image.image)
	{
		g_tex.redbrick_data = (int *) mlx_get_data_addr(g_tex.texture_xpm, &k, &k, &k);
		g_tex.redbrick_data2 = (int *) mlx_get_data_addr(g_tex.texture1_xpm, &k, &k, &k);
		g_tex.eagle_data = (int *) mlx_get_data_addr(g_tex.texture2_xpm, &k, &k, &k);
		g_tex.grey_stone_data = (int *) mlx_get_data_addr(g_tex.texture3_xpm, &k, &k, &k);
		g_sp_image.data = (int *)mlx_get_data_addr(g_sp_image.image, &k, &k, &k);
	}
	else
		error(EXIT_FAILURE, "there is no texture with that name !");
}
