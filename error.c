/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:03 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/13 09:47:19 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(int etat, char *string)
{
	mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	ft_putstr(string);
	free_mem();
	exit(etat);
}
