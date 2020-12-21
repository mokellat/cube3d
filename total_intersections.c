#include "cub3d.h"

void	total_intesection_calcul()
{
	//rays_directions();
	data_gather();
	normalise_angle();
	horz_intersection_calcul();
	ver_intersection_calcul();
	g_horzdistance = (g_foundawallhorz) ? distance_between(g_new_player.pos_x, g_new_player.pos_y, g_horzwallhitx, g_horzwallhity) : INT_MAX;
	g_verdistance = (g_foundawallver) ? distance_between(g_new_player.pos_x, g_new_player.pos_y, g_verwallhitx, g_verwallhity) : INT_MAX;
	g_new_player.wallHitX = (g_horzdistance < g_verdistance) ? g_horzwallhitx : g_verwallhitx;
	g_new_player.wallHitY = (g_horzdistance < g_verdistance) ? g_horzwallhity : g_verwallhity;
	g_distance = (g_horzdistance < g_verdistance) ? g_horzdistance : g_verdistance;
	g_new_player.wasHitVertical = (g_verdistance < g_horzdistance);
	//line(g_new_player.pos_x, g_new_player.pos_y, g_new_player.ray_angle, g_distance,0xFF0000);
}


int textures_directions()
{
	if(g_new_player.ray_up && g_new_player.wasHitVertical)
		return (g_tex.redbrick_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
	else if(g_new_player.ray_down && g_new_player.wasHitVertical)
		return(g_tex.redbrick_data2[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
	else if(g_new_player.ray_left && g_new_player.wasHitVertical)
		return(g_tex.grey_stone_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
	else
		return(g_tex.eagle_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
}


void	walls_draw(int y, int index)
{
	y = g_walltoppixel;
	while (y < g_wallbottompixel)
	{
		g_distancefromtop = y + (g_wallstripg_height / 2) - (g_height / 2);
		g_textureoffsety = g_distancefromtop * ((double)(g_textureheight / g_wallstripg_height));
		g_textureoffsety = g_textureoffsety < 0 ? 0 : g_textureoffsety;
		if(g_new_player.ray_up && !g_new_player.wasHitVertical)
			g_colorshading = (g_tex.redbrick_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
		else if(g_new_player.ray_down && !g_new_player.wasHitVertical)
			g_colorshading = (g_tex.redbrick_data2[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
		else if(g_new_player.ray_left && g_new_player.wasHitVertical)
			g_colorshading = (g_tex.grey_stone_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
		else if(g_new_player.ray_right && g_new_player.wasHitVertical)
			g_colorshading = (g_tex.eagle_data[(int)((g_texturewidth * g_textureoffsety) + g_textureoffsetx)]);
		int tst = (int)((g_width * y++) + index);
		if(tst > 0 && tst < g_height * g_width)
			g_mlx.img_data[tst] = g_colorshading;
	}
}

void	total_intersection_3D(int index)
{
	int y;

	total_intesection_calcul();
	g_correctdistance = g_distance * cos(g_new_player.ray_angle - g_new_player.rotation_angle);
	g_distanceprojplane = (g_width / 2) / tan(g_new_player.FOV_angle / 2);
	g_wallstripg_height = ((g_tile / g_correctdistance) * g_distanceprojplane);
	g_walltoppixel =  (g_height / 2) - (g_wallstripg_height / 2);
	g_walltoppixel =  g_walltoppixel < 0 ? 0 : g_walltoppixel;
	g_wallbottompixel =  (g_height / 2) + (g_wallstripg_height / 2);
	g_wallbottompixel = (g_wallbottompixel > g_height) ? g_height : g_wallbottompixel;
	g_textureoffsetx = (g_new_player.wasHitVertical) ? (int) g_new_player.wallHitY % g_tile : (int) g_new_player.wallHitX % g_tile ;
	y = 0;
	while(y < g_walltoppixel)
	{
		g_mlx.img_data[g_width * y + index] = create_trgb(g_file.color_r_c, g_file.color_g_c, g_file.color_b_c);
		y++;
	}
	y = g_walltoppixel;
	walls_draw(y , index);
	y = g_wallbottompixel;
	while (y < g_height)
	{
		g_mlx.img_data[g_width * y + index] = create_trgb(g_file.color_r_f, g_file.color_g_f, g_file.color_b_f);
		y++;
	}
	render_sprite();
}


/*void	castAllRays()
{
	int index;

	index = 0;
	g_new_player.ray_angle = g_new_player.rotation_angle - g_new_player.FOV_angle / 2;
	while (index < g_new_player.Num_rays)
	{
		total_intesection_calcul();
		g_new_player.ray_angle += g_new_player.FOV_angle / g_new_player.Num_rays;
		index++;
	}
}*/
