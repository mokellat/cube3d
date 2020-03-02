/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:32:17 by mokellat          #+#    #+#             */
/*   Updated: 2020/03/01 15:28:19 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int main()
{
    void    *mlx_ptr;
    void    *win_ptr;
    int     i;
    int     j;
    
    i = -1;
    j = -1;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 800, "med ali");
    while(++j <= 400)
    {
        i = -1;
        while (++i <= 400)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFFFFFF);
        }
    }
    j = 399;
    while(++j <= 800)
    {
        i = 399;
        while (++i <= 800)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0x00FFFF);
        }
    }
    mlx_loop(mlx_ptr);
}