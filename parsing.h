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
char			**g_lines;
char			**g_map;
char			*g_line;
int				count;

void    colors_tre_floor(char **g_lines, int k, int i);
void	colors_tre_ceilling(char **g_lines, int k, int i);
void    R_exec(int *k, int i, int *indexx, int x);
int		map_parsing();
int		check_map_elements();
int		check_map_errors();
int		map_surronding();
int		ft_strcmp(char *s1, const char *s2);
