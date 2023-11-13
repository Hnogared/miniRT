# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 19:48:41 by hnogared          #+#    #+#              #
#    Updated: 2023/11/13 21:20:41 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# * SETUP VARIABLES ********************************************************** #

## Project structure ##
# Executable name #
NAME			:=	miniRT

# Source code directories #
SRCS_DIR		:=	srcs
LIBS_SRCS_DIR	:=	$(addprefix $(SRCS_DIR)/, libraries)
MLX_SRCS_DIR	:=	$(addprefix $(LIBS_SRCS_DIR)/, minilibx-linux)
LFT_SRCS_DIR	:=	$(addprefix $(LIBS_SRCS_DIR)/, extended_libft)

# Object, archive and header files directories respectively #
OBJS_DIR		:=	objs
ARCHIVES_DIR	:=	archives
INCLUDES_DIR	:=	includes

# Complementary paths to all source code files #
VPATH			:=	$(SRCS_DIR):					\
					$(SRCS_DIR)/object_management:	\
					$(SRCS_DIR)/display:			\
					$(SRCS_DIR)/parsing

# Source files names #
SRCS			:=	main.c					\
					check_file.c			\
					get_file.c				\
					check_scene.c			\
					check_numbers.c			\
					check_range_numbers.c	\
					conv_hexa.c				\
					object_creation.c		\
					object_modification.c	\
					print_object_data.c		\
					print_object_data_2.c	\
					window_management.c		\
					image_management.c		\
					utils.c


## Libraries files ##
# Minilibx and libft header files #
MLX_INCLUDES	:=	mlx.h mlx_int.h


# Minilibx and libft archive files #
MLX_ARCHIVES	:=	libmlx.a libmlx_Linux.a
LFT_ARCHIVES	:=	libextended_ft.a


## Files management ##
# Compilation method and flags #
CC				:=	gcc
CFLAGS			:=	-g -Wall -Werror -Wextra
IFLAGS			:=
LFLAGS			:=	-lX11 -lXext -lm

# File deletion method #
RM				:=	rm -rf


# * AUTOMATIC VARIABLES ****************************************************** #

# Object files depending on the source files #
OBJS			:=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))


## Libraries header files ##
# Minilibx and libft header files source path #
MLX_INCL_SRCS	:=	$(addprefix $(MLX_SRCS_DIR)/, $(MLX_INCLUDES))

# Minilibx and libft header files separate dependencies #
MLX_INCL_DEPEND	:=	$(addprefix $(INCLUDES_DIR)/, $(MLX_INCLUDES))


# Minilibx and libft header files dependencies for compilation #
INCL_DEPEND		:=	$(MLX_INCL_DEPEND) $(LFT_INCL_DEPEND)


## Libraries archives files ##
# Minilibx and libft archive files source path #
MLX_ARCHS_SRCS	:=	$(addprefix $(MLX_SRCS_DIR)/, $(MLX_ARCHIVES))
LFT_ARCHS_SRCS	:=	$(addprefix $(LFT_SRCS_DIR)/, $(LFT_ARCHIVES))

# Minilibx and libft archive files separate dependencies #
MLX_ARCHS_DEPEND:=	$(addprefix $(ARCHIVES_DIR)/, $(MLX_ARCHIVES))
LFT_ARCHS_DEPEND:=	$(addprefix $(ARCHIVES_DIR)/, $(LFT_ARCHIVES))

# Minilibx and libft archive files dependencies for compilation #
ARCHS_DEPEND	:=	$(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND)


## Compilation flags ##
# Minilibx and libft flags to include their archive files #
MLX_LFLAGS		:=	$(patsubst lib%.a,-l%,$(MLX_ARCHIVES))
LFT_LFLAGS		:=	$(patsubst lib%.a,-l%,$(LFT_ARCHIVES))

# Flags to include the manually given libraries, the minilibx and the libft #
AUTO_LFLAGS		:=	-L $(ARCHIVES_DIR) $(MLX_LFLAGS) $(LFT_LFLAGS) $(LFLAGS)

# Flags to include the manually given includes directories and $(INCLUDES_DIR) #
AUTO_IFLAGS		:=	$(IFLAGS) -I $(INCLUDES_DIR)


# * PARAMETER VARIABLES ****************************************************** #

# Force the program's opened window to the specified width #
ifdef WIN_WIDTH
CFLAGS	+=	-D WIN_WIDTH=$(WIN_WIDTH)
endif

# Force the program's opened window to the specified height #
ifdef WIN_HEIGHT
CFLAGS	+=	-D WIN_HEIGHT=$(WIN_HEIGHT)
endif

# **************************************************************************** #

# **************************************************************************** #
# * STANDARD RULES *********************************************************** #

all:	$(NAME)


## Compilation rules ##
# Compile the executable depending on the libraries archives and header files, #
#  as well as all the object files #
$(NAME):	$(ARCHS_DEPEND) $(INCL_DEPEND) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(AUTO_IFLAGS) $(AUTO_LFLAGS)

# Compile an object file depending on its source file and the object directory #
$(OBJS_DIR)/%.o:	%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(AUTO_IFLAGS) $(AUTO_LFLAGS)


## Directories rules ##
# Create the object directory if missing #
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

# Create the archive directory if missing #
$(ARCHIVES_DIR):
	mkdir $(ARCHIVES_DIR)


## Cleanup rules ##
# Remove all object files #
clean:
	$(RM) $(OBJS)

# Remove all object files and the executable #
fclean:	clean
	$(RM) $(NAME)

# Remove all minilibx and libft archives from the archive dir #
lclean:
	$(RM) $(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND)

# Remove all object files and the object directory #
dclean:	clean
	$(RM) $(OBJS_DIR)

# Remove all object files and the executable, then recompile everything #
re:	fclean all


# ??? #
test:
	clear
	@echo -n "\e[0;0H\e[s"
	$(call put_frame, 60, 11, $(FRAME_CHARS), $(ANSI_BG_BLA)$(ANSI_FG_BBLA))
	@echo -n "\e[u\e[B\e[9C"
	@echo -n $(ANSI_FG_WHI)$(ANSI_BG_BLA)$(ASCII_MINI)$(ANSI_NC)
	@echo -n "\e[3A\e[4D"
	@echo $(ANSI_FG_RED)$(ANSI_BG_BLA)$(ASCII_RT)$(ANSI_NC)
	@echo


# * LIBRARIES RULES ********************************************************** #

## Minilibx making rules ##
# Call the minilibx makefile to make #
minilibx:
	make -C $(MLX_SRCS_DIR)

# Call the minilibx makefile to make the rule after '-' (ex: minilibx-clean) #
minilibx-%:
	make $* -C $(MLX_SRCS_DIR)

# Call the minilibx makefile to make if the minilibx source archive is missing #
$(MLX_SRCS_DIR)/%.a:
	make -C $(MLX_SRCS_DIR)

# Copy the minilibx archive into the archive directory #
# Depends on the minilibx source archive and the archive directory #
$(MLX_ARCHS_DEPEND):	$(MLX_ARCHS_SRCS) | $(ARCHIVES_DIR)
	cp $^ $(ARCHIVES_DIR)


## Libft making rules ##
# Call the libft makefile to make #
libft:
	make -C $(LFT_SRCS_DIR)

# Call the libft makefile to make the rule after '-' (ex: libft-clean) #
libft-%:
	make $* -C $(LFT_SRCS_DIR)

# Call the libft makefile to make if the libft source archive is missing #
$(LFT_SRCS_DIR)/%.a:
	make -C $(LFT_SRCS_DIR)

# Copy the libft archive into the archive directory #
# Depends on the libft source archive and the archive directory #
$(LFT_ARCHS_DEPEND):	$(LFT_ARCHS_SRCS) | $(ARCHIVES_DIR)
	cp $^ $(ARCHIVES_DIR)


# * MISCELANEOUS RULES ******************************************************* #

# Display a short list of all available rules #
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

# Ignore files for check rule completeness
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
