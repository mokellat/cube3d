#include "cub3d.h"

int		create_trgb(int r, int g, int b)
{
	if((r > 255 || g > 255 || b > 255) && (r < 0 || g < 0 || b <0))
		error(EXIT_FAILURE, "colors are invalid");
	return(r << 16 | g << 8 | b);
}
