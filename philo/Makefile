# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <npolack@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 11:22:57 by npolack           #+#    #+#              #
#    Updated: 2024/12/19 23:16:26 by ilia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/philo

SRCS_DIR	= srcs
OBJS_DIR	= objs
CC			= gcc
C_FLAGS		= -Wall -Wextra -Werror -g

SRCS		= philo.c common.c ft_atoi.c fork.c
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
