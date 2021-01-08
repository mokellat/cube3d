#include "cub3d.h"

void	file_errors()
{
	if(g_file.color_r_f ==  -1 || g_file.color_g_f == -1 || g_file.color_b_f == -1)
		error(EXIT_FAILURE, "colors are invalid");
	if(g_file.color_r_c ==  -1 || g_file.color_g_c == -1 || g_file.color_b_c == -1)
		error(EXIT_FAILURE, "colors are invalid");
	if(g_file.height == -1 || g_file.width == -1)
		error(EXIT_FAILURE, "dimensions are invalid");
}
