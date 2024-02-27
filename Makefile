# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 13:47:01 by kde-la-c          #+#    #+#              #
#    Updated: 2023/08/07 13:47:03 by kde-la-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_DBG	= dbg
SRC			= pipex.c\
			input.c\
			output.c\
			run_cmd.c\
			fill_cmd.c\
			handle_fds.c\
			init_core.c
OBJS		= $(SRC:%.c=%.o)
INCLUDE		= pipex.h
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm
RFLAGS		= -rf

LIBNAME		= libft.a
LIBPATH		= libft/

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDE) $(LIBNAME)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBNAME)
	$(RM) $(RFLAGS) $(OBJS)
	@echo "\033[0;31m--- RELINK ---\033[0m"
			@echo "\033[0;32m--- $(NAME) compiled successfully! ---\033[0m"

l:			$(OBJS) $(INCLUDE) $(LIBNAME)
			$(CC) $(CFLAGS) -fsanitize=leak -g3 $(OBJS) -o $(NAME) $(LIBNAME)
			$(RM) $(RFLAGS) $(OBJS)
			@echo "\033[0;32m--- $(NAME) compiled successfully! ---\033[0m"

m:			$(OBJS) $(INCLUDE) $(LIBNAME)
			$(CC) $(CFLAGS) -fsanitize=address -g3 $(OBJS) -o $(NAME) $(LIBNAME)
			$(RM) $(RFLAGS) $(OBJS)
			@echo "\033[0;32m--- $(NAME) compiled successfully! ---\033[0m"

debug:		$(NAME_DBG)

$(NAME_DBG): $(LIBNAME) $(SRC)
			$(CC) $(CFLAGS) -fdiagnostics-color=always -g3 $(SRC) $(LIBNAME) -o $@

$(LIBNAME):
			$(MAKE) -C $(LIBPATH)
			cp $(LIBPATH)$(LIBNAME) .
			$(MAKE) -C $(LIBPATH) fclean

clean:
			$(RM) $(RFLAGS) $(OBJS)
			@echo "\033[0;32m--- Objects cleaned successfully! ---\033[0m"

fclean:		clean
			$(RM) $(RFLAGS) $(NAME) $(LIBNAME)
			@echo "\033[0;32m--- Archive cleaned successfully! ---\033[0m"

re:			fclean all

.PHONY:		all clean fclean re debug m l
