/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <mokellat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 14:51:44 by mokellat          #+#    #+#             */
/*   Updated: 2021/02/07 17:24:59 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H
# include "cub3d.h"

typedef struct		s_bitmapheader{
	uint32_t	file_size;
	uint32_t	off_bits;
	uint32_t	size;
	uint32_t	info_size;
	int32_t		width;
	int32_t		height;
	uint16_t	planes;
	uint16_t	bit_count;
	uint32_t	image_size;
	int			width_in_bytes;
	int			fd;
}					t_bitmapheader;
void				screenshot(void);
char				*img_buff(t_bitmapheader *header);
int					*get_colors(int color);
char				*bmp_header(t_bitmapheader *header);
#endif
