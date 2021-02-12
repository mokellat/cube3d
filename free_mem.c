/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 08:21:01 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/12 18:56:27 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrice(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_map(char **ptr)
{
	int i;

	i = 0;
	while (i < g_count)
		free(ptr[i++]);
	free(ptr);
}

void	free_mem(void)
{
	if (g_lines)
		free_matrice(g_lines);
}
