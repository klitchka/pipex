# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaparici <aaparici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/08 10:32:22 by aaparici          #+#    #+#              #
#    Updated: 2021/08/09 17:00:15 by aaparici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

SRCS		= pipex.c pipex_util.c

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)
$(NAME):	
			$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
clean:		
			$(RM) -r *.o
fclean:		clean
			$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re
