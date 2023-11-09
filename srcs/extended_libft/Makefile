# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 07:19:57 by hnogared          #+#    #+#              #
#    Updated: 2023/11/09 18:01:46 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libextended_ft.a

LIB_D		=	Srcs
LIB_SRCS	= 	ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isprint.c		\
				ft_isascii.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_strlen.c			\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strncmp.c		\
				ft_strnstr.c		\
				ft_atoi.c			\
				ft_strlcpy.c		\
				ft_strlcat.c		\
				ft_bzero.c			\
				ft_memset.c			\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_calloc.c			\
				ft_strdup.c			\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_split_set.c		\
				ft_itoa.c			\
				ft_strmapi.c		\
				ft_striteri.c		\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_lstnew.c			\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_front.c	\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c

PRINTF_D	=	Srcs/display/ft_printf
PRINTF_SRCS	=	ft_printf.c		\
				ft_output.c		\
				ft_output2.c	\
				ft_strings.c

OBJS_D	= Objs
OBJS	= $(addprefix $(OBJS_D)/, $(LIB_SRCS:.c=.o) $(PRINTF_SRCS:.c=.o))

CC		= gcc
CFLAGS	= -Werror -Wall -Wextra

AR		= ar rcs

RM		= rm -rf


all:		$(NAME)

$(NAME):	$(OBJS_D) $(OBJS)
	@$(AR) $@ $(OBJS)
	@echo "Created $(NAME) library !"

$(OBJS_D):
	@if [ ! -d $(OBJS_D) ]; then						\
		mkdir $(OBJS_D);								\
		echo "Created missing $(OBJS_D)/ directory";	\
	fi

$(OBJS_D)/%.o:	$(LIB_D)/char_checks/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJS_D)/%.o:	$(LIB_D)/display/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJS_D)/%.o:	$(LIB_D)/linked_lists/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJS_D)/%.o:	$(LIB_D)/memory_management/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJS_D)/%.o:	$(LIB_D)/strings/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJS_D)/%.o:	$(PRINTF_D)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@if ls $(OBJS_D)/*.o > /dev/null 2>&1; then		\
		$(RM) $(OBJS);								\
		echo "Removed object files";				\
	else											\
		echo "Nothing to be done for : $(RM) *.o";	\
	fi

fclean:	clean
	@if [ -f $(NAME) ]; then							\
		$(RM) $(NAME);									\
		echo "Removed $(NAME)";							\
	else												\
		echo "Nothing to bo done for : $(RM) $(NAME)";	\
	fi

dclean:	clean
	@if [ -d $(OBJS_D) ]; then								\
		$(RM) $(OBJS_D);									\
		echo "Removed $(OBJS_D)/ objects directory";		\
	else													\
		echo "Nothing to be done for : $(RM) $(OBJS_D)/";	\
	fi

re:			fclean all

.PHONY:		all clean fclean dclean re
