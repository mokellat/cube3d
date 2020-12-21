#include "cub3d.h"

typedef struct file_parsing
{
	int	width;
	int	height;
	int	color_r_f;
	int	color_g_f;
	int	color_b_f;
	int	color_r_c;
	int	color_g_c;
	int	color_b_c;
	char *ptr;
}	t_parse;

t_parse			g_file;
