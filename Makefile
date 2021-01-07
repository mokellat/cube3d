CC = gcc -Wall -Wextra -Werror -I /usr/share/man/man3 -L  /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o cub3D
SFLAGS = -g -g3 -fsanitize=address
NAME = cub3D

SRC = drawings.c\
		info.c\
		intersections.c\
		keys_update.c\
		total_intersections.c\
		sprite.c\
		texture_choose.c\
		rgb.c\
		map_parsing.c\
		utils.c\
		parsing.c\
		parsing_utils.c\
		main.c\
		colors.c\
		get_next_line/get_next_line.c\

all : $(NAME)

$(NAME): $(SRC) cub3d.h
	cd Libft; make;
	$(CC) -g $(SRC) ./Libft/libft.a

clean :
	rm -rf $(OBJECT)

fclean : clean
	rm -rf $(NAME)
	rm -rf cub3D

re : fclean all
