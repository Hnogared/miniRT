# **************************************************************************** #
#    Makefile                                                                  #
# **************************************************************************** #

# * SETUP VARIABLES ********************************************************** #

#######################
## Project structure ##
#######################
# Executable name
NAME			:=	miniRT

# Source code directories
SRCS_DIR		:=	srcs
LIBS_SRCS_DIR	:=	$(addprefix $(SRCS_DIR)/, libraries)
MLX_SRCS_DIR	:=	$(addprefix $(LIBS_SRCS_DIR)/, minilibx-linux)
LFT_SRCS_DIR	:=	$(addprefix $(LIBS_SRCS_DIR)/, extended_libft)

# Object, archive and header files directories respectively
OBJS_DIR		:=	objs
ARCHIVES_DIR	:=	archives
INCLUDES_DIR	:=	includes

# Complementary paths to all source code files 
VPATH			:=	$(SRCS_DIR):					\
					$(SRCS_DIR)/object_management:	\
					$(SRCS_DIR)/display:

# Source files names
SRCS			:=	main.c					\
					check_file.c			\
					get_file.c				\
					check_scene.c			\
					conv_hexa.c				\
					object_creation.c		\
					object_modification.c	\
					print_object_data.c		\
					print_object_data_2.c	\
					window_management.c		\
					image_management.c


#####################
## Libraries files ##
#####################
# Minilibx and libft header files
MLX_INCLUDES	:=	mlx.h mlx_int.h


# Minilibx and libft archive files
MLX_ARCHIVES	:=	libmlx.a libmlx_Linux.a
LFT_ARCHIVES	:=	libextended_ft.a


######################
## Files management ##
######################
# Compilation method and flags
CC				:=	gcc
CFLAGS			:=	-g -Wall -Werror -Wextra
IFLAGS			:=
LFLAGS			:=	-lX11 -lXext -lm

# File deletion method
RM				:=	rm -rf


# * AUTOMATIC VARIABLES ****************************************************** #

###############################
## Automatic files variables ##
###############################
# Object files depending on the source files
OBJS			:=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

# Minilibx header files source path
MLX_INCL_SRCS	:=	$(addprefix $(MLX_SRCS_DIR)/, $(MLX_INCLUDES))
# Minilibx header files dependencies for compilation
MLX_INCL_DEPEND	:=	$(addprefix $(INCLUDES_DIR)/, $(MLX_INCLUDES))


# Minilibx and libft header files dependencies for compilation
INCL_DEPEND		:=	$(MLX_INCL_DEPEND) $(LFT_INCL_DEPEND)

# Minilibx archive files source path
MLX_ARCHS_SRCS	:=	$(addprefix $(MLX_SRCS_DIR)/, $(MLX_ARCHIVES))
# Minilibx archive files dependencies for compilation
MLX_ARCHS_DEPEND:=	$(addprefix $(ARCHIVES_DIR)/, $(MLX_ARCHIVES))

# Libft archive files source path
LFT_ARCHS_SRCS	:=	$(addprefix $(LFT_SRCS_DIR)/, $(LFT_ARCHIVES))
# Libft archive files dependencies for compilation
LFT_ARCHS_DEPEND:=	$(addprefix $(ARCHIVES_DIR)/, $(LFT_ARCHIVES))

ARCHS_DEPEND	:=	$(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND)

MLX_LFLAGS		:=	$(patsubst lib%.a,-l%,$(MLX_ARCHIVES))
LFT_LFLAGS		:=	$(patsubst lib%.a,-l%,$(LFT_ARCHIVES))

AUTO_LFLAGS		:=	-L $(ARCHIVES_DIR) $(MLX_LFLAGS) $(LFT_LFLAGS) $(LFLAGS) 
AUTO_IFLAGS		:=	$(IFLAGS) -I $(INCLUDES_DIR)


# * PARAMETER VARIABLES ****************************************************** #

ifdef WIN_WIDTH
CFLAGS	+=	-D WIN_WIDTH=$(WIN_WIDTH)
endif

ifdef WIN_HEIGHT
CFLAGS	+=	-D WIN_HEIGHT=$(WIN_HEIGHT)
endif

# **************************************************************************** #

all:	$(NAME)

$(NAME):	$(ARCHS_DEPEND) $(INCL_DEPEND) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(AUTO_IFLAGS) $(AUTO_LFLAGS)

$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(AUTO_IFLAGS) $(AUTO_LFLAGS)

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

test:
	clear
	@echo -n "\e[0;0H\e[s"
	$(call put_frame, 60, 11, $(FRAME_CHARS), $(ANSI_BG_BLA)$(ANSI_FG_BBLA))
	@echo -n "\e[u\e[B\e[9C"
	@echo -n $(ANSI_FG_WHI)$(ANSI_BG_BLA)$(ASCII_MINI)$(ANSI_NC)
	@echo -n "\e[3A\e[4D"
	@echo $(ANSI_FG_RED)$(ANSI_BG_BLA)$(ASCII_RT)$(ANSI_NC)
	@echo

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
	@echo "\nMiniRT Makefile help - Available targets\n";				\
	echo "$(ANSI_BOLD)BASIC TARGETS$(ANSI_NC)";							\
	echo "\tall  re  help\n";											\
	echo "$(ANSI_BOLD)FILES TARGETS$(ANSI_NC)";							\
	echo -n "\t$(NAME)";												\
	echo -n "$(OBJS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).o  ";		\
	echo "$(ARCHIVES_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n";		\
	echo "$(ANSI_BOLD)DIRECTORIES TARGETS$(ANSI_NC)";					\
	echo "\t$(OBJS_DIR)  $(ARCHIVES_DIR)\n";							\
	echo "$(ANSI_BOLD)CLEANUP TARGETS$(ANSI_NC)";						\
	echo "\tclean  fclean  lclean  dclean\n\n";							\
	echo "$(ANSI_BOLD)MINILIBX TARGETS$(ANSI_NC)";						\
	echo "\tminilibx  minilibx-$(ANSI_FG_RED)<target>$(ANSI_NC)\n";		\
	echo "$(ANSI_BOLD)MINILIBX FILES TARGETS$(ANSI_NC)";				\
	echo "\t$(MLX_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n\n";	\
	echo "$(ANSI_BOLD)LIBFT TARGETS$(ANSI_NC)";							\
	echo "\tlibft  libft-$(ANSI_FG_RED)<target>$(ANSI_NC)\n";			\
	echo "$(ANSI_BOLD)LIBFT FILES TARGETS$(ANSI_NC)";					\
	echo "\t$(LFT_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n"

# **************************************************************************** #

.PHONY:	all clean fclean lclean dclean libft libft-% minilibx minilibx-% re help

# **************************************************************************** #

ANSI_NC			:=	"\\e[0m"
ANSI_BOLD		:=	"\\e[1m"

ANSI_NFG		:=	"\\e[39m"
ANSI_FG_BLA		:=	"\\e[30m"
ANSI_FG_RED		:=	"\\e[31m"
ANSI_FG_GRE		:=	"\\e[32m"
ANSI_FG_YEL		:=	"\\e[33m"
ANSI_FG_BLU		:=	"\\e[34m"
ANSI_FG_MAG		:=	"\\e[35m"
ANSI_FG_CYA		:=	"\\e[36m"
ANSI_FG_WHI		:=	"\\e[37m"
ANSI_FG_BBLA	:=	"\\e[90m"
ANSI_FG_BRED	:=	"\\e[91m"
ANSI_FG_BGRE	:=	"\\e[92m"
ANSI_FG_BYEL	:=	"\\e[93m"
ANSI_FG_BBLU	:=	"\\e[94m"
ANSI_FG_BMAG	:=	"\\e[95m"
ANSI_FG_BCYA	:=	"\\e[96m"
ANSI_FG_BWHI	:=	"\\e[97m"

ANSI_BG_BLA		:=	"\\e[40m"

ASCII_MINI	:=	"@   @@@@   @@@@@    @@@@@   @@@@ @"	\
				"\\e[B\\e[35D@@ @@@@@   @@@@@    @@@@@   @@@@ @"	\
				"\\e[B\\e[35D@@@@@@@@   @@@@@    @@@@@@  @@@@ @"	\
				"\\e[B\\e[35D@@@@@@@@   @@@@@    @@@@@@  @@@@ @"	\
				"\\e[B\\e[35D@@@@@@@@   @@@@@    @@@@@@@ @@@@ @"	\
				"\\e[B\\e[35D@ @ @@@@   @@@@@    @@@@@@@@@@@@ @"	\
				"\\e[B\\e[35D@   @@@@   @@@@@    @@@@@@@@@@@@ @"	\
				"\\e[B\\e[35D@   @@@@   @@@@@    @@@@@  @@@@@ @"	\
				"\\e[B\\e[35D@   @@@@   @@@@@    @@@@@   @@@@ @"

ASCII_RT	:=	"%%%%%  %%%%%%"	\
				"\\e[B\\e[14D%%  %%   %%"	\
				"\\e[B\\e[12D%%%%%    %%"	\
				"\\e[B\\e[12D%%  %%   %%"

FRAME_CHARS	:=	"═" "║" "╔" "╗" "╚" "╝"

# **************************************************************************** #

define put_square
	$(eval width = $(1))
	$(eval height = $(2))
	$(eval color = $(3))
	@line=" ";										\
	x=1;											\
	while [ $$x -lt $(width) ]; do					\
		line="$$line ";								\
		x=$$(( $$x + 1 ));							\
	done;											\
	square="$$line\e[B\e[$(width)D";				\
	y=1;											\
	while [ $$y -lt $(height) ]; do					\
		square="$$square$$line\e[B\e[$(width)D";	\
		y=$$(( $$y + 1 ));							\
	done;											\
	echo -n "$(color)$$square$(ANSI_NC)"
endef

define put_frame
	$(eval width = $(1))
	$(eval height = $(2))
	$(eval horizontal = $(word 1, $(3)))
	$(eval vertical = $(word 2, $(3)))
	$(eval tl_corner = $(word 3, $(3)))
	$(eval tr_corner = $(word 4, $(3)))
	$(eval bl_corner = $(word 5, $(3)))
	$(eval br_corner = $(word 6, $(3)))
	$(eval color = $(4))
	@frame_top="$(tl_corner)";							\
	frame_middle="$(vertical)";							\
	frame_bottom="$(bl_corner)";						\
	x=1;												\
	while [ $$x -lt $$(( $(width) - 1 )) ];	do			\
		frame_top="$$frame_top$(horizontal)";			\
		frame_middle="$$frame_middle ";					\
		frame_bottom="$$frame_bottom$(horizontal)";		\
		x=$$(( $$x + 1 ));								\
	done;												\
	frame_middle="$$frame_middle$(vertical)";			\
	frame="$$frame_top$(tr_corner)\e[B\e[$(width)D";	\
	y=1;												\
	while [ $$y -lt $$(( $(height) - 1 )) ]; do			\
		frame="$$frame$$frame_middle\e[B\e[$(width)D";	\
		y=$$(( $$y + 1 ));								\
	done;												\
	frame="$$frame$$frame_bottom$(br_corner)";			\
	echo -n "$(color)$$frame$(ANSI_NC)"
endef

#LFT_INCLUDES	:=	libft.h
#LFT_INCL_SRCS	:=	$(addprefix $(LFT_SRCS_DIR)/, $(LFT_INCLUDES))
#LFT_INCL_DEPEND	:=	$(addprefix $(INCLUDES_DIR)/, $(LFT_INCLUDES))
