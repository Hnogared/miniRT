# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 07:19:57 by hnogared          #+#    #+#              #
#    Updated: 2023/12/19 00:12:50 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libextended_ft.a

SRCS_DIR	:=	srcs
PRINTF_DIR	:=	$(SRCS_DIR)/display/ft_printf
GNL_DIR		:=	$(SRCS_DIR)/get_next_line

OBJS_DIR	:=	objs

INCL_DIR	:=	includes

VPATH	:=	$(SRCS_DIR)/char_checks:		\
			$(SRCS_DIR)/display:			\
			$(SRCS_DIR)/linked_lists:		\
			$(SRCS_DIR)/memory_management:	\
			$(SRCS_DIR)/strings:			\
			$(SRCS_DIR)/numbers:			\
			$(PRINTF_DIR):					\
			$(GNL_DIR)

LIB_SRCS	:= 	ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isprint.c		\
				ft_isascii.c		\
				ft_iswhitespace.c	\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_strlen.c			\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strchrnul.c		\
				ft_strncmp.c		\
				ft_strnstr.c		\
				ft_atoi.c			\
				ft_atof.c			\
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
				ft_strndup.c		\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_split_set.c		\
				ft_itoa.c			\
				ft_itoab.c			\
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
				ft_lstmap.c			\
				ft_min.c			\
				ft_max.c			\
				ft_fmin.c			\
				ft_fmax.c

PRINTF_SRCS	:=	ft_printf.c		\
				ft_fprintf.c	\
				ft_output.c		\
				ft_output2.c	\
				ft_strings.c

GNL_SRCS	:=	get_next_line_bonus.c

OBJS		:=	$(addprefix $(OBJS_DIR)/,\
					$(LIB_SRCS:.c=.o)\
					$(PRINTF_SRCS:.c=.o)\
					$(GNL_SRCS:.c=.o))

CC		:=	gcc
IFLAGS	:=	-I $(INCL_DIR)
CFLAGS	:=	-g -Werror -Wall -Wextra

AR		:=	ar rcs

RM		:=	rm -rf


all:		$(NAME)

$(NAME):	$(OBJS) | $(OBJS_DIR)
	@$(AR) $@ $(OBJS)
	@echo "Created $(NAME) library !"

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@echo "Created missing $(OBJS_DIR)/ directory"

$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)
	@echo "Compiled $@ object file !"

clean:
	@if ls $(OBJS_DIR)/*.o > /dev/null 2>&1; then	\
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
	@if [ -d $(OBJS_DIR) ]; then							\
		$(RM) $(OBJS_DIR);									\
		echo "Removed $(OBJS_DIR)/ objects directory";		\
	else													\
		echo "Nothing to be done for : $(RM) $(OBJS_DIR)/";	\
	fi

re:			fclean all

.PHONY:		all clean fclean dclean re
