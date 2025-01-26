# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 11:22:57 by npolack           #+#    #+#              #
#    Updated: 2025/01/26 18:08:23 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/philo_bonus

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
C_FLAGS		= -Wall -Wextra -Werror -g 

SRCS		=	philo_bonus.c\
				common_bonus.c\
				customers_bonus.c\
				manager_bonus.c\
			 	establishment_bonus.c\
			 	routine_bonus.c\
				job_bonus.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all				: $(NAME) 

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

thread		: C_FLAGS += -g -pthread
thread		: re

san         : C_FLAGS += -g -fsanitize=thread
san         : re

$(NAME)			: $(OBJS)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $^ -o $@ $(LIBS)

unlink			:
	@mkdir -p bin
	cc srcs/close_sem.c -o bin/unlink_sem

clean			:
	rm -fr $(OBJS_DIR)

fclean			: clean
	rm -fr bin

re				: fclean all

.PHONY			: all clean fclean re bonus
