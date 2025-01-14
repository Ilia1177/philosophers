# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 11:22:57 by npolack           #+#    #+#              #
#    Updated: 2025/01/14 17:35:35 by npolack          ###   ########.fr        #
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

SRCS		=	philo.c\
				common.c\
				customers.c\
				manager.c\
			 	establishment.c\
			 	routine.c\
				job.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all				: $(NAME) 

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

san         : C_FLAGS += -fsanitize=thread
san         : $(NAME)

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
