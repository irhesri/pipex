# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 21:49:31 by irhesri           #+#    #+#              #
#    Updated: 2022/05/28 17:20:29 by irhesri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
NAME_B	= pipex_bonus

SRC		= mandatory/basic_functions.c mandatory/functions.c mandatory/new_split.c mandatory/pipex.c
SRC_B	= bonus/basic_functions_bonus.c bonus/functions_bonus.c bonus/get_next_line_bonus.c bonus/new_split_bonus.c bonus/pipex_bonus.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

OBJ		= $(SRC:%.c=%.o)
OBJ_B	= $(SRC_B:%.c=%.o)

$(NAME) : $(OBJ)
	@gcc $^ -o $@

bonus : $(NAME_B)

$(NAME_B) : $(OBJ_B)
	@gcc $^ -o $@

%.o : %.c 
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf mandatory/*.o
	@rm -rf bonus/*.o

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)

re: fclean all

.PHONY: all clean fclean re