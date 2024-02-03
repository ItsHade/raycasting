SRC_DIR := src
OBJ_DIR := obj
SRC = 	ft_put.c \
	main.c

SRC        := $(SRC:%=$(SRC_DIR)/%)
OBJ        := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = raycast

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I/usr/include/SDL2

RM = rm -f


MAKEFLAGS   += --no-print-directory

DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lSDL2 -lm -o $(NAME)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
		$(RM) -r $(OBJ_DIR)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
.SILENT:
