# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 16:05:56 by ugerkens          #+#    #+#              #
#    Updated: 2023/10/19 00:11:44 by ugerkens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME			=	get_next_line.a
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -Isrc -Iinclude
RM				=	rm -rf

# Paths and Files
VPATH			=	src
SRCS			=	get_next_line.c get_next_line_utils.c
OBJS			=	$(addprefix obj/,$(SRCS:.c=.o))

# Rules
$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

all:			$(NAME)

obj:
				mkdir -p obj

obj/%.o:		%.c | obj
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) obj

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.SILENT:

.PHONY:			all clean fclean re
