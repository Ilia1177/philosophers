# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 11:22:57 by npolack           #+#    #+#              #
#    Updated: 2025/01/02 18:49:19 by ilia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/philo

OS := $(shell uname)

ifeq ($(OS), Linux)
    LIBS	:= -lrt
	CC		= cc
else
    LIBS	:=
	CC		= clang
endif

SRCS_DIR	= srcs
OBJS_DIR	= objs
C_FLAGS		= -Wall -Wextra -Werror -g -O2 #-fsanitize=thread 

SRCS		= philo.c\
			  common.c\
			  customers.c\
			  manager.c\
			  establishment.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS: $(SRCS_DIR)/%.c=$(OBJS_DIR/%.o))

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

all				: $(NAME) 

$(NAME)			: $(OBJS)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $^ -o $@ $(LIBS)


clean			:
	rm -fr $(OBJS_DIR)

fclean			: clean
	rm $(NAME)

re				: fclean all

.PHONY			: all clean fclean re bonus
