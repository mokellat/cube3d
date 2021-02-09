/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:52:26 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/08 16:33:14 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_args(int argc, char **argv)
{
	char	*cher_ptr;

	if (argc > 3)
		error(EXIT_FAILURE, "There is more then two arguments !");
	if (argc < 2)
		error(EXIT_FAILURE, "arguments are invalid !");
	cher_ptr = ft_strchr(argv[1], '.');
	if (!cher_ptr)
		error(EXIT_FAILURE, "File name is invalid !");
	else if (ft_strcmp(cher_ptr, ".cub") != 0)
		error(EXIT_FAILURE, "File name is invalid !");
	if (argc == 3)
		if (ft_strcmp(argv[2], "--save") == 0)
		{
			update();
			screenshot();
		}
}

int		main(int argc, char **argv)
{
	int k;

	parsing();
	player_config();
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_width, g_height, "cub3d");
	g_mlx.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_width, g_height);
	g_mlx.img_data = (int *)mlx_get_data_addr(g_mlx.img_ptr, &k, &k, &k);
	get_image();
	add_sprite();
	file_errors();
	if (!map_parsing())
		error(EXIT_FAILURE, "map is invalid");
	get_args(argc, argv);
	mlx_hook(g_mlx.win_ptr, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(g_mlx.win_ptr, 3, 1L << 1, key_released, (void *)0);
	mlx_hook(g_mlx.win_ptr, 17, 0, red_cross, NULL);
	mlx_loop_hook(g_mlx.mlx_ptr, update, (void *)0);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_mlx.img_ptr, 0, 0);
	mlx_loop(g_mlx.mlx_ptr);
}
