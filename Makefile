# **************************************************************************** #
#    Makefile                                                                  #
# **************************************************************************** #

NAME			:=	miniRT
 
VPATH			:=	srcs:

SRCS_DIR		:=	srcs
MLX_SRCS_DIR	:=	$(addprefix $(SRCS_DIR)/, minilibx-linux)
LFT_SRCS_DIR	:=	$(addprefix $(SRCS_DIR)/, extended_libft)
SRCS			:=	main.c \
				check_file.c \
 
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


ANSI_NC			:=	"\e[0m"
ANSI_FG_BLA		:=	"\e[30m"
ANSI_FG_RED		:=	"\e[31m"
ANSI_FG_GRE		:=	"\e[32m"
ANSI_FG_YEL		:=	"\e[33m"
ANSI_FG_BLU		:=	"\e[34m"
ANSI_FG_MAG		:=	"\e[35m"
ANSI_FG_CYA		:=	"\e[36m"
ANSI_FG_WHI		:=	"\e[37m"
ANSI_FG_BBLA	:=	"\e[90m"
ANSI_FG_BRED	:=	"\e[91m"
ANSI_FG_BGRE	:=	"\e[92m"
ANSI_FG_BYEL	:=	"\e[93m"
ANSI_FG_BBLU	:=	"\e[94m"
ANSI_FG_BMAG	:=	"\e[95m"
ANSI_FG_BCYA	:=	"\e[96m"
ANSI_FG_BWHI	:=	"\e[97m"

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

help:
	@echo "All available rules ("$(ANSI_FG_RED)"*"$(ANSI_NC)" = any name):";			\
	echo $(ANSI_FG_BYEL)" making      "$(ANSI_NC)"> all  re  help";						\
	echo -n $(ANSI_FG_GRE)" files       "$(ANSI_NC)"> $(NAME)  ";						\
	echo -n "$(OBJS_DIR)/"$(ANSI_FG_RED)"*"$(ANSI_NC)".o  ";							\
	echo "$(ARCHIVES_DIR)/"$(ANSI_FG_RED)"*"$(ANSI_NC)".a";								\
	echo $(ANSI_FG_BBLU)" directories "$(ANSI_NC)"> $(OBJS_DIR)  $(ARCHIVES_DIR)";		\
	echo $(ANSI_FG_RED)" cleanup     "$(ANSI_NC)"> clean  fclean  lclean  dclean\n";	\
	echo -n $(ANSI_FG_BYEL)" mlx making  "$(ANSI_NC)"> minilibx  ";						\
	echo "minilibx-"$(ANSI_FG_RED)"*"$(ANSI_NC);										\
	echo -n $(ANSI_FG_GRE)" mlx files   "$(ANSI_NC)"> ";								\
	echo "$(MLX_SRCS_DIR)/"$(ANSI_FG_RED)"*"$(ANSI_NC)".a\n";							\
	echo -n $(ANSI_FG_BYEL)" lft making  "$(ANSI_NC)"> libft  ";						\
	echo "libft-"$(ANSI_FG_RED)"*"$(ANSI_NC);											\
	echo -n $(ANSI_FG_GRE)" lft files   "$(ANSI_NC)"> ";								\
	echo "$(LFT_SRCS_DIR)/"$(ANSI_FG_RED)"*"$(ANSI_NC)".a"

# **************************************************************************** #

.PHONY:	all clean fclean lclean dclean libft libft-% minilibx minilibx-% re help
