/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:32 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/06 14:52:33 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_parsing()
{
	int		i;
	size_t	j;

	i = 0;
	j = -1;
	g_new_player.rotation_angle = player_direc();
	player_init();
	while(i < g_count)
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
	return (1);
}

int		check_map_elements()
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < g_count)
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

int		check_map_errors()
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < g_count)
	{
		j = 0;
		while(j < ft_strlen(g_map[i]))
		{
			if((g_map[i][j] == '0' || g_map[i][j] == 'N'  || g_map[i][j] == 'W' || g_map[i][j] == 'E'
			|| g_map[i][j] == 'S') && j > 0 && i > 0 && j + 1 < ft_strlen(g_map[i]) && i + 1 < g_count)
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

int		map_surronding()
{
	int		i;
	size_t	j;
	int		k;

	i = 0;
	k = 0;
	while(i < g_count)
	{
		j = ft_strlen(g_map[i]);
		if((g_map[i][0] == '1' || g_map[i][0] == ' ') && (g_map[i][j - 1] == '1' || g_map[i][j - 1] == ' '))
		{
			k = 0;
			while(k < (int)j && (i == 0 || i == g_count - 1))
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

void	player_init()
{
	int	i;
	int	j;
	int indexx;

	i = 0;
	indexx = 0;
	while(i < g_count)
	{
		j = 0;
		while(j < (int) ft_strlen(g_map[i]))
		{
			if(g_map[i][j] == 'N' || g_map[i][j] == 'W' || g_map[i][j] == 'S'
			|| g_map[i][j] == 'E')
			{
				g_new_player.pos_x = (j + 0.5) * g_tile;
				g_new_player.pos_y = (i + 0.5) * g_tile;
				g_map[i][j] = '0';
				indexx++;
			}
			j++;
		}
		i++;
	}
	if(indexx == 0)
		error(EXIT_FAILURE, "There is no player !");
	if(indexx > 1)
		error(EXIT_FAILURE, "There is more then one player !");
}
