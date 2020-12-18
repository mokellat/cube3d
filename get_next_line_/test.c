
#include "../cube3d/cub3d.h"
//#include "../cube3d/parsing.h"

int main(void)
{
	char *line;
	char **lines;
	int i;
	int	k;
	int fd;
	int j;
	char *ptr[] = {"R", "NO", "SO", "WE", "EA", "S", "F", "C"};

	i = 1;
	j = 0;
	fd = open("./file.cub", O_RDONLY);
	while((i = get_next_line(fd, &line)))
	{
		j++;
		lines = realloc(lines, j * sizeof(line));
		lines[j-1] = line;
	}
	i = 0;
	while (i < 8)
	{
		if(lines[i][0] == 'R')
		{
			//printf("1\n");
			k = 2;
			while(lines[i][k] != ' ')
			{
				g_file.height = ft_atoi(&lines[i][k]);
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
		i++;
	}
	printf("%d\n", g_file.height);
	printf("%d\n", g_file.width);
	return 0;
}
