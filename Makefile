# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amontano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/25 03:44:24 by amontano          #+#    #+#              #
#    Updated: 2018/09/16 15:07:17 by amontano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = main.c		\
	  img.c			\
	  hooks.c		\
	  mapgen.c		\
	  util.c		\
	  raycast.c     \
	  render.c 		\
	  player.c 		\
	  draw.c        \
	  rgb_to_hsv.c	\
	  hsv_to_rgb.c	\
	  tex.c 		\
	  event.c		\
	  music.c		\
	  move.c		\
	  hud.c			\
	  sprite_init.c \
	  sprite.c      \
	  sprite_util.c \
	  mapcheck.c
	 
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_DIR = obj/

MLX_PATH = minilibx_macos/
MLX = $(addprefix $(MLX_PATH), mlx.a)
MLX_DIR = -I ./minilibx_macos/
MLX_LNK = -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

FT = libft/
LIBFT = $(addprefix $(FT), libft.a)
FT_DIR = -I ./libft/src/
FT_LNK = -L ./libft/ -lft

SRC_DIR = ./src/
INC_DIR = ./includes/
OBJ_DIR = ./obj/

all: obj $(LIBFT) $(MLX_DIR) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(MLX_INC) $(FT_DIR) -I $(INC_DIR) -o $@ -c $<

$(LIBFT):
	@make -C $(FT)

$(MLX_DIR):
	@make -C $(MLX_PATH)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK)  -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

o: clean all

re: fclean all

.PHONY: all clean fclean re o

