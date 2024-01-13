# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 07:19:57 by hnogared          #+#    #+#              #
#    Updated: 2024/01/06 23:29:03 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_NAME	:=	extended_ft

STATIC_NAME		:=	$(addsuffix .a, $(addprefix lib, $(LIB_NAME)))
DYNAMIC_NAME	:=	$(addsuffix .so, $(addprefix lib, $(LIB_NAME)))

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

LIB_SRCS	:= 	ft_isalpha.c			\
				ft_isdigit.c			\
				ft_isalnum.c			\
				ft_isprint.c			\
				ft_isascii.c			\
				ft_iswhitespace.c		\
				ft_toupper.c			\
				ft_tolower.c			\
				ft_strlen.c				\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strchrnul.c			\
				ft_strncmp.c			\
				ft_strnstr.c			\
				ft_atoi.c				\
				ft_atof.c				\
				ft_strlcpy.c			\
				ft_strlcat.c			\
				ft_bzero.c				\
				free_double_pointer.c	\
				ft_memset.c				\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_memcpy.c				\
				ft_memmove.c			\
				ft_calloc.c				\
				ft_strdup.c				\
				ft_strndup.c			\
				ft_substr.c				\
				ft_strjoin.c			\
				ft_strtrim.c			\
				ft_split.c				\
				ft_split_set.c			\
				ft_itoa.c				\
				ft_itoab.c				\
				ft_strmapi.c			\
				ft_striteri.c			\
				ft_putchar_fd.c			\
				ft_putstr_fd.c			\
				ft_putendl_fd.c			\
				ft_putnbr_fd.c			\
				ft_lstnew.c				\
				ft_lstsize.c			\
				ft_lstlast.c			\
				ft_lstadd_front.c		\
				ft_lstadd_back.c		\
				ft_lstdelone.c			\
				ft_lstclear.c			\
				ft_lstiter.c			\
				ft_lstmap.c				\
				ft_min.c				\
				ft_max.c				\
				ft_fmin.c				\
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


all:		$(STATIC_NAME) $(DYNAMIC_NAME)

$(STATIC_NAME):	$(OBJS) | $(OBJS_DIR)
	@$(AR) $@ $(OBJS)
	@echo "Created $(STATIC_NAME) static library !"

$(DYNAMIC_NAME):	$(OBJS) | $(OBJS_DIR)
	@$(CC) -shared -o $(DYNAMIC_NAME) $(OBJS)
	@echo "Created $(DYNAMIC_NAME) dynamic library !"

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
	@if [ ! -f $(STATIC_NAME) ] && [ ! -f $(DYNAMIC_NAME) ]; then			\
		echo -n "Nothing to bo done for : $(RM) $(STATIC_NAME)";			\
		echo " || $(RM) $(DYNAMIC_NAME)";									\
		return;																\
	fi;																		\
	if [ -f $(STATIC_NAME) ]; then											\
		$(RM) $(STATIC_NAME);												\
		echo "Removed $(STATIC_NAME)";										\
	fi;																		\
	if [ -f $(DYNAMIC_NAME) ]; then	   										\
		$(RM) $(DYNAMIC_NAME);		   										\
		echo "Removed $(DYNAMIC_NAME)";										\
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
