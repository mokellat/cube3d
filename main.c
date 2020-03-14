/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:32:17 by mokellat          #+#    #+#             */
/*   Updated: 2020/03/08 18:42:31 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

typedef struct  s_vars 
{
    void    *mlx;
    void    *win;
    void    *img;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}


int main()
{
    int     i;
    int     j;
    t_vars  vars;
    
    i = -1;
    j = -1;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 800, 800, "med ali");
    while(++j <= 400)
    {
        i = -1;
        while (++i <= 400)
        {
            mlx_pixel_put(vars.mlx, vars.win, i, j, 0xFFFFFF);
        }
    }
    j = 399;
    while(++j <= 800)
    {
        i = 399;
        while (++i <= 800)
        {
            mlx_pixel_put(vars.mlx, vars.win, i, j, 0x00FFFF);
        }
    }
    mlx_loop(vars.mlx);
}