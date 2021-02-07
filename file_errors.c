/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:07 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/07 18:27:24 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_errors(void)
{
	if (g_map == NULL)
		error(EXIT_FAILURE, "There is no map !");
	if (g_file.color_r_f == -1 || g_file.color_g_f == -1 ||
	g_file.color_b_f == -1)
		error(EXIT_FAILURE, "colors are invalid !");
	if (g_file.color_r_c == -1 || g_file.color_g_c == -1
	|| g_file.color_b_c == -1)
		error(EXIT_FAILURE, "colors are invalid !");
	if (g_file.height == -1 || g_file.width == -1)
		error(EXIT_FAILURE, "dimensions are invalid !");
	if (g_files_tex.no_tex == NULL || g_files_tex.so_tex == NULL
	|| g_files_tex.we_tex == NULL
	|| g_files_tex.ea_tex == NULL || g_files_tex.sp_tex == NULL)
		error(EXIT_FAILURE, "textures are invalid !");
	if (g_map == NULL)
		error(EXIT_FAILURE, "there is no map !");
	if (g_counter > 8)
		error(EXIT_FAILURE, "duplicate Element in the file !");
}
