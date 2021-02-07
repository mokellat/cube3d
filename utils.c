/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:53:54 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/06 14:53:55 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, const char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return (s1[x] - s2[x]);
}

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
	}
}

double		distance(double x, double y)
{
	return (sqrt((x - g_new_player.pos_x) * (x - g_new_player.pos_x) +
			(y - g_new_player.pos_y) * (y - g_new_player.pos_y)));
}

void	draw_one_pixel(int y, int x, double color)
{
	if (y < g_height && y >= 0 && color != 0x000000)
		g_mlx.img_data[(y) * g_width + (x)] = color;
}
