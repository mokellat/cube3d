#include "cub3d.h"

int	map_parsing()
{
	int		i;
	size_t	j;

	i = 0;
	j = -1;
	while(i < count)
	{
		 j = -1;
		while(++j < ft_strlen(g_map[i]))
		{
			if(check_map_elements())
			{
				if(map_surronding() && check_map_errors())
					return (1);
				else
					return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	check_map_elements()
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		j = 0;
		while(j < ft_strlen(g_map[i]))
		{
			if(g_map[i][j] == '1' || g_map[i][j] == '0' || g_map[i][j] == '2' || g_map[i][j] == ' '
			|| g_map[i][j] == 'N' || g_map[i][j] == 'E' || g_map[i][j] == 'S' || g_map[i][j] == 'W')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_map_errors()
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		j = 0;
		while(j < ft_strlen(g_map[i]))
		{
			if((g_map[i][j] == '0' || g_map[i][j] == '2') && j > 0 && i > 0 && j + 1 < ft_strlen(g_map[i])
			&& i + 1 < count)
			{
				if((g_map[i][j + 1] == ' ' || g_map[i][j - 1] == ' ' || g_map[i + 1][j] == ' '
				|| g_map[i - 1][j] == ' '))
					return (0);
				if((j >= ft_strlen(g_map[i + 1]) || j >= ft_strlen(g_map[i - 1])))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map_surronding()
{
	int		i;
	size_t	j;
	int		k;

	i = 0;
	k = 0;
	while(i < count)
	{
		j = ft_strlen(g_map[i]);
		if((g_map[i][0] == '1' || g_map[i][j - 1] == '1') || (g_map[i][0] == ' ' || g_map[i][j - 1] == ' '))
		{
			k = 0;
			while(k < (int)j && (i == 0 || i == count - 1))
			{
				if(g_map[i][k] != '1' && g_map[i][k] != ' ')
					return (0);
				k++;
			}
			i++;
		}
		else
			return (0);
	}
	return (1);
}
