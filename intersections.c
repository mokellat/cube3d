#include "cub3d.h"

void	rays_directions()
{
	normalise_angle();
	g_new_player.ray_down = (g_new_player.ray_angle > 0 && g_new_player.ray_angle < M_PI);
	g_new_player.ray_up = !(g_new_player.ray_down);
	g_new_player.ray_left = !g_new_player.ray_right;
	g_new_player.ray_right = (g_new_player.ray_angle < 0.5 * M_PI || g_new_player.ray_angle > 1.5 * M_PI);
}

void	help_inter_horz()
{
	while (g_nexthorztouchy >= 0 && g_nexthorztouchy <= g_tile * g_count && g_nexthorztouchx >= 0 && g_nexthorztouchx <= g_tile * 20)
	{
		if (haswallat(g_nexthorztouchx , g_nexthorztouchy - (g_new_player.ray_up ? 1 : 0)))
		{
			g_foundawallhorz = 1;
			g_horzwallhity = g_nexthorztouchy;
			g_horzwallhitx = g_nexthorztouchx;
			break;
		}
		else
		{
			g_nexthorztouchy += g_ystephorz;
			g_nexthorztouchx += g_xstephorz;
		}
	}
}

void	help_inter_ver()
{
	while (g_nextvertouchy >= 0 && g_nextvertouchy <= g_tile * g_count && g_nextvertouchx >= 0 && g_nextvertouchx <= g_tile * 20)
	{
		if (haswallat(g_nextvertouchx, g_nextvertouchy - (g_new_player.ray_left ? 1 : 0)))
		{
			g_foundawallver = 1;
			g_verwallhity = g_nextvertouchy;
			g_verwallhitx = g_nextvertouchx;
			break;
		}
		else
		{
			g_nextvertouchy += g_ystepver;
			g_nextvertouchx += g_xstepver;
		}
	}
}

void	horz_intersection_calcul()
{
	rays_directions();
	normalise_angle();
	g_foundawallhorz = 0;
	g_horzwallhitx = 0;
	g_horzwallhity = 0;
	g_yinterupthorz = floor(g_new_player.pos_y / g_tile) * g_tile;
	g_yinterupthorz += g_new_player.ray_down ? g_tile : 0;
	g_xinterupthorz = g_new_player.pos_x + ((g_yinterupthorz - g_new_player.pos_y) / tan(g_new_player.ray_angle));
	g_ystephorz = g_tile;
	g_ystephorz *= g_new_player.ray_up ? -1 : 1;
	g_xstephorz = g_tile / tan(g_new_player.ray_angle);
	g_xstephorz *= (g_new_player.ray_left && g_xstephorz > 0) ? -1 : 1;
	g_xstephorz *= (g_new_player.ray_right && g_xstephorz < 0) ? -1 : 1;
	g_nexthorztouchx = g_xinterupthorz;
	g_nexthorztouchy = g_yinterupthorz;
	if (g_new_player.ray_up)
		g_nexthorztouchy--;
	help_inter_horz();
}

void	ver_intersection_calcul()
{
	rays_directions();
	normalise_angle();
	g_foundawallver = 0;
	g_verwallhitx = 0;
	g_verwallhity = 0;
	g_xinteruptver = floor(g_new_player.pos_x / g_tile) * g_tile;
	g_xinteruptver += g_new_player.ray_right ? g_tile : 0;
	g_yinteruptver = g_new_player.pos_y + ((g_xinteruptver - g_new_player.pos_x) * tan(g_new_player.ray_angle));
	g_xstepver = g_tile;
	g_xstepver *= g_new_player.ray_left ? -1 : 1;
	g_ystepver = g_tile * tan(g_new_player.ray_angle);
	g_ystepver *= (g_new_player.ray_up && g_ystepver > 0) ? -1 : 1;
	g_ystepver *= (g_new_player.ray_down && g_ystepver < 0) ? -1 : 1;
	g_nextvertouchx = g_xinteruptver;
	g_nextvertouchy = g_yinteruptver;
	if (g_new_player.ray_left)
		g_nextvertouchx--;
	help_inter_ver();
}
