# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 21:49:31 by irhesri           #+#    #+#              #
#    Updated: 2022/08/11 15:13:38 by irhesri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
NAME_B	= pipex_bonus

SRC		= mandatory/basic_functions.c mandatory/functions.c mandatory/new_split.c mandatory/pipex.c
SRC_B	= bonus/basic_functions_bonus.c bonus/functions_bonus.c bonus/get_next_line_bonus.c bonus/new_split_bonus.c bonus/pipex_bonus.c

CC		= gcc #-g -fsanitize=address
#CFLAGS	= -Wall -Wextra -Werror

OBJ		= $(SRC:%.c=%.o)
OBJ_B	= $(SRC_B:%.c=%.o)

$(NAME) : $(OBJ)
	@$(CC) $^ -o $@

bonus : $(NAME_B)

$(NAME_B) : $(OBJ_B)
	@$(CC) $^ -o $@

%.o : %.c 
	@gcc $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf mandatory/*.o
	@rm -rf bonus/*.o

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)

re: fclean $(NAME)

.PHONY: all clean fclean re