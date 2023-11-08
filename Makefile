# **************************************************************************** #
#    Makefile                                                                  #
# **************************************************************************** #

NAME			:=	miniRT
 
VPATH			:=	srcs:

SRCS_DIR		:=	srcs
MLX_SRCS_DIR	:=	$(addprefix $(SRCS_DIR)/, minilibx-linux)
LFT_SRCS_DIR	:=	$(addprefix $(SRCS_DIR)/, extended_libft)
SRCS			:=	main.c
 
OBJS_DIR		:=	objs
OBJS			:=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
 
INCLUDES_DIR	:=	includes

ARCHIVES_DIR	:=	archives

MLX_ARCHIVES	:=	libmlx.a libmlx_Linux.a
MLX_ARCHS_SRCS	:=	$(addprefix $(MLX_SRCS_DIR)/, $(MLX_ARCHIVES))
MLX_ARCHS_DEPEND:=	$(addprefix $(ARCHIVES_DIR)/, $(MLX_ARCHIVES))

LFT_ARCHIVES	:=	libextended_ft.a
LFT_ARCHS_SRCS	:=	$(addprefix $(LFT_SRCS_DIR)/, $(LFT_ARCHIVES))
LFT_ARCHS_DEPEND:=	$(addprefix $(ARCHIVES_DIR)/, $(LFT_ARCHIVES))

ARCHS_DEPEND	:=	$(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND)

MLX_LFLAGS		:=	-lmlx -lmlx_Linux -lX11 -lXext
LFT_LFLAGS		:=	-lextended_ft

CC				:=	gcc
CFLAGS			:=	-g -Wall -Werror -Wextra
LFLAGS			:=	-L $(ARCHIVES_DIR) $(MLX_LFLAGS) $(LFT_LFLAGS) -lm
IFLAGS			:=	-I $(INCLUDES_DIR)

RM				:=	rm -rf

# **************************************************************************** #

all:	$(NAME)

$(NAME):	$(ARCHS_DEPEND) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(IFLAGS) $(LFLAGS)

$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS) $(LFLAGS)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(ARCHIVES_DIR):
	mkdir $(ARCHIVES_DIR)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

lclean:
	$(RM) $(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND)

dclean:	clean
	$(RM) $(OBJS_DIR)

re:	fclean all

# **************************************************************************** #

minilibx:
	make -C $(MLX_SRCS_DIR)

minilibx-%:
	make $* -C $(MLX_SRCS_DIR)

$(MLX_SRCS_DIR)/%.a:
	make -C $(MLX_SRCS_DIR)

$(MLX_ARCHS_DEPEND):	$(MLX_ARCHS_SRCS) | $(ARCHIVES_DIR)
	cp $^ $(ARCHIVES_DIR)

# **************************************************************************** #

libft:
	make -C $(LFT_SRCS_DIR)

libft-%:
	make $* -C $(LFT_SRCS_DIR)

$(LFT_SRCS_DIR)/%.a:
	make -C $(LFT_SRCS_DIR)

$(LFT_ARCHS_DEPEND):	$(LFT_ARCHS_SRCS) | $(ARCHIVES_DIR)
	cp $^ $(ARCHIVES_DIR)

# **************************************************************************** #

.PHONY:	all clean fclean dclean minilibx minilibx-% re
