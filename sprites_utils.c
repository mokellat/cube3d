/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:09:51 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/08 15:09:57 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalise_rotation_angle(void)
{
	if (g_new_player.rotation_angle < 0)
		g_new_player.rotation_angle += 2 * M_PI;
	if (g_new_player.rotation_angle > 2 * M_PI)
		g_new_player.rotation_angle -= 2 * M_PI;
}
