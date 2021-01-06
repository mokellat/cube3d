/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokellat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:27:12 by mokellat          #+#    #+#             */
/*   Updated: 2019/12/15 22:22:04 by mokellat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_the_second(char ***ptr, char **line, int j)
{
	char	*tempo;

	tempo = *line;
	*line = ft_strjoin(*line, **ptr);
	if (!line)
		return (-1);
	free(tempo);
	tempo = **ptr;
	**ptr = ft_strdup(**ptr + j + 1);
	if (!**ptr)
		return (-1);
	free(tempo);
	return (0);
}

int	get_the_first(char **line, char **ptr)
{
	int		j;

	j = 0;
	while (*(*ptr + j) != '\0')
	{
		if (*(*ptr + j) == '\n')
		{
			(*(*ptr + j)) = '\0';
			get_the_second(&ptr, line, j);
			return (1);
		}
		if (*(*ptr + j + 1) == '\0')
		{
			get_the_second(&ptr, line, j);
			free(*ptr);
			return (0);
		}
		j++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	ssize_t		i;
	char		*buff;
	static char *ptr;
	char		*tempo;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 0)
		return (-1);
	if (!(buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (!ptr)
		ptr = ft_strdup("");
	if (!(*line = ft_strdup("")) || !ptr)
		return (-1);
	while (((i = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		*(buff + i) = '\0';
		tempo = ptr;
		if (!(ptr = ft_strjoin(ptr, buff)))
			return (-1);
		free(tempo);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (get_the_first(line, &ptr));
}
