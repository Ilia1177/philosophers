# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 11:22:57 by npolack           #+#    #+#              #
#    Updated: 2025/01/15 14:51:02 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/philo

SRCS_DIR	= srcs
OBJS_DIR	= objs
CC			= cc
C_FLAGS		= -Wall -Wextra -Werror -g -pthread

SRCS		= fork.c\
			  philo.c\
			  common.c\
			  manager.c\
			  customers.c\
			  establishment.c\

SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all				: $(NAME) 

san         : C_FLAGS += -fsanitize=thread
san         : $(NAME)

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME)			: $(OBJS)
	@mkdir -p bin
	$(CC) $(C_FLAGS) $^ -o $@

clean			:
	rm -fr $(OBJS_DIR)

fclean			: clean
	rm -fr bin

re				: fclean all

.PHONY			: all clean fclean re bonus
