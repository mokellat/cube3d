/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:38:19 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/18 14:32:52 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_error(int i)
{
	char	*ptr;
	int		indexx;

	indexx = 1;
	ptr = (ft_strtrim(g_lines[i], " "));
	while (indexx < (int)ft_strlen(ptr))
	{
		if (ptr[indexx] != ' ' && !ft_isdigit(ptr[indexx])
		&& ptr[indexx] != ',')
		{
			free(ptr);
			error(EXIT_FAILURE, "colors are invalid !");
		}
		indexx++;
	}
	free(ptr);
}
