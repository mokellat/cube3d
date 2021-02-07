/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 08:21:01 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/07 11:05:50 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrice(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i] && i < g_file_lenght)
		free(ptr[i++]);
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

void	free_mem()
{
	if(g_map)
		free_map(g_map);
	if(g_lines)
		free_matrice(g_lines);
}
