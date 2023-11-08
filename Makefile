# **************************************************************************** #
#    Makefile                                                                  #
# **************************************************************************** #

NAME			:=	miniRT
                
VPATH			:=	srcs:
                
SRCS			:=	main.c
                
OBJS_DIR		:=	objs
OBJS			:=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
                
CC				:=	gcc
CFLAGS			:=	-g -Wall -Werror -Wextra

RM				:=	rm -rf

INCLUDES_DIR	:=	includes

ARCHIVES_DIR	:=	archives
MLX_ARCHIVES_DIR:=	$(ARCHIVES_DIR)/mlx
LFT_ARCHIVES_DIR:=	$(ARCHIVES_DIR)/extended_libft

MLX_SRCS_DIR	:=	srcs/minilibx-linux
MLX_ARCHIVES	:=	libmlx.a libmlx_Linux.a
MLX_ARCHS_DEPEND:=	$(addprefix $(MLX_ARCHIVES_DIR)/, $(MLX_ARCHIVES))
MLX_LIBFLAGS	:=	-lmlx -lmlx_Linux -lX11 -lXext

LFT_SRCS_DIR	:=	srcs/extended_libft
LFT_ARCHIVES	:=	libextended_ft.a
LFT_ARCHS_DEPEND:=	$(addprefix $(LFT_ARCHIVES_DIR)/, $(LFT_ARCHIVES))
LFT_LIBFLAGS	:=	-lextended_ft

ARCHIVES		:=	$(addprefix $(ARCHIVES_DIR)/, $(MLX_ARCHIVES))

LIBFLAGS_DIR	:=	-L $(MLX_ARCHIVES_DIR) -L $(LFT_ARCHIVES_DIR)
LIBFLAGS		:=	$(MLX_LIBFLAGS) $(LFT_LIBFLAGS)

# **************************************************************************** #

all:	$(NAME)

$(NAME):	$(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -I $(INCLUDES_DIR) $(LIBFLAGS_DIR) $(LIBFLAGS)

$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR) $(LIBFLAGS_DIR) $(LIBFLAGS)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(ARCHIVES_DIR):
	mkdir $(ARCHIVES_DIR)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

dclean:	clean
	$(RM) $(OBJS_DIR)

re:	fclean all

# **************************************************************************** #

minilibx:
	make -C $(MLX_SRCS_DIR)

minilibx-%:
	make $* -C $(MLX_SRCS_DIR)

$(MLX_ARCHIVES_DIR):
	mkdir $(MLX_ARCHIVES_DIR)

$(MLX_SRCS_DIR)/%.a:
	make -C $(MLX_SRCS_DIR)

$(MLX_ARCHIVES_DIR)/%.a:	$(MLX_SRCS_DIR)/%.a | $(MLX_ARCHIVES_DIR)
	cp $< $(MLX_ARCHIVES_DIR)

# **************************************************************************** #

libft:
	make -C $(LFT_SRCS_DIR)

libft-%:
	make $* -C $(LFT_SRCS_DIR)

$(LFT_ARCHIVES_DIR):
	mkdir $(LFT_ARCHIVES_DIR)

$(LFT_SRCS_DIR)/%.a:
	make -C $(LFT_SRCS_DIR)

$(LFT_ARCHIVES_DIR)/%.a:	$(LFT_SRCS_DIR)/%.a | $(LFT_ARCHIVES_DIR)
	cp $< $(LFT_ARCHIVES_DIR)

# **************************************************************************** #

.PHONY:	all clean fclean dclean minilibx minilibx-% re
