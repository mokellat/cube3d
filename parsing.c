/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:46 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/06 14:52:47 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	beg_errors(int indexx)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = (char **)malloc(sizeof(char));
	while (i < indexx - 1)
	{
		i++;
		ptr = realloc(ptr, i * sizeof(g_lines[i - 1]));
		ptr[i - 1] = ft_strtrim(g_lines[i - 1], " ");
		if (ptr[i - 1][0] != 'R' && ptr[i - 1][0] != 'N' && ptr[i - 1][0] != 'S'
		&& ptr[i - 1][0] != 'W' && ptr[i - 1][0] != 'E' && ptr[i - 1][0] != 'S'
		&& ptr[i - 1][0] != 'F' && ptr[i - 1][0] != 'C' && ptr[i - 1][0] != '\0')
			error(EXIT_FAILURE, "File is invalid !");
	}
}

void	lenght_calcul()
{
	int		i;

	i = 0;
	while (g_map[i] && i + 1 < g_count)
	{
		if ((int)ft_strlen(g_map[i]) > g_b_lenght)
			g_b_lenght = (int)ft_strlen(g_map[i]);
		i++;
	}
}

void	parsing(void)
{
	int	i;
	int	k;
	int	fd;
	int	j;
	int	x;
	int	indexx;

	i = 1;
	j = 0;
	indexx = 0;
	g_count = 0;
	fd = 0;
	x = 0;
	k = -1;
	g_counter = 0;
	i = 0;
	get_next_line_work(&fd, &i, &j);
	parsing_work(&i, j, &k, &indexx, &x);
	if (g_map == NULL)
		error(EXIT_FAILURE, "there is no map !");
	beg_errors(indexx);
	lenght_calcul();
}
