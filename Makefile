
CC = gcc -Wall -Wextra -Werror -I /usr/share/man/man3 -L  /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o cub3D
SFLAGS = -g -g3 -fsanitize=address
NAME = cub3D

SRC = drawings.c\
		info.c\
		intersections.c\
		keys_update.c\
		total_intersections.c\
		main.c\
		get_next_line/get_next_line_utils.c\
		get_next_line/get_next_line.c\

all : $(NAME)

$(NAME): $(SRC) cub3d.h
	$(CC) $(SRC)

clean :
	rm -rf $(OBJECT)

fclean : clean
	rm -rf $(NAME)
	rm -rf cub3D

re : fclean all
