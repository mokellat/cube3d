/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:51:40 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/06 14:51:41 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*bmp_header(t_bitmapheader *header)
{
	char	*ptr;

	ptr = ft_calloc(54, 1);
	header->bit_count = 24;
	header->width_in_bytes = ((g_width * header->bit_count + 31) / 32) * 4;
	header->image_size = header->width_in_bytes * g_height;
	header->size = 54 + header->image_size;
	header->off_bits = 54;
	header->info_size = 40;
	header->planes = 1;
	header->width = g_width;
	header->height = g_height;
	ft_memcpy(ptr, "BM", 2);
	ft_memcpy(ptr + 2, &(header->size), 4);
	ft_memcpy(ptr + 10, &(header->off_bits), 4);
	ft_memcpy(ptr + 14, &(header->info_size), 4);
	ft_memcpy(ptr + 18, &(header->width), 4);
	ft_memcpy(ptr + 22, &(header->height), 4);
	ft_memcpy(ptr + 26, &(header->planes), 2);
	ft_memcpy(ptr + 28, &(header->bit_count), 2);
	ft_memcpy(ptr + 34, &(header->image_size), 4);
	return (ptr);
}

int		*get_colors(int color)
{
	int *colors;

	colors = malloc(3 * sizeof(int));
	colors[0] = ((color >> 16) & 0xFF);
	colors[1] = ((color >> 8) & 0xFF);
	colors[2] = ((color) & 0xFF);
	return (colors);
}

char	*img_buff(t_bitmapheader *header)
{
	char	*ptr;
	int		i;
	int		j;
	int		*colors;

	ptr = malloc(header->image_size);
	i = header->height - 1;
	while (i > 0)
	{
		j = 0;
		while (j < header->width)
		{
			if(((g_height - i) * g_width) + j < g_width * g_height)
				colors = get_colors(g_mlx.img_data[((g_height - i) * g_width) + j]);
			ptr[i * header->width_in_bytes + j * 3 + 0] = colors[2];
			ptr[i * header->width_in_bytes + j * 3 + 1] = colors[1];
			ptr[i * header->width_in_bytes + j * 3 + 2] = colors[0];
			free(colors);
			j++;
		}
		i--;
	}
	return (ptr);
}

void	screenshot(void)
{
	t_bitmapheader	bitmap_header;
	char			*header_string;
	char			*img_buf;

	bitmap_header.fd = open("./screenshot.bmp", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	header_string = bmp_header(&bitmap_header);
	img_buf = img_buff(&bitmap_header);
	write(bitmap_header.fd, header_string, 54);
	write(bitmap_header.fd, img_buf, bitmap_header.image_size);
	free(header_string);
	free(img_buf);
	exit(EXIT_SUCCESS);
}
