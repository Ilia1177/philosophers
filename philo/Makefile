# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 11:22:57 by npolack           #+#    #+#              #
#    Updated: 2024/12/20 16:18:44 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/philo

SRCS_DIR	= srcs
OBJS_DIR	= objs
CC			= gcc
C_FLAGS		= -Wall -Wextra -Werror -g

SRCS		= fork.c\
			  philo.c\
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
	$(CC) $(C_FLAGS) $^ -o $@


clean			:
	rm -fr $(OBJS_DIR)

fclean			: clean
	rm $(NAME)

re				: fclean all

.PHONY			: all clean fclean re bonus
