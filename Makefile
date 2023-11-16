# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 19:48:41 by hnogared          #+#    #+#              #
#    Updated: 2023/11/14 00:50:39 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pathe to the Makefile's includes #
MK_INCLUDES_DIR	:=	Makefile_includes

# Include the Makefile defining the shell functions #
include $(MK_INCLUDES_DIR)/Makefile.functions

# Include the Makefile containing the variables used for graphical displays # 
include $(MK_INCLUDES_DIR)/Makefile.graphical_variables

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
intro:
	$(call play_intro)


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
	@echo -e "\nMiniRT Makefile help - Available targets\n";				\
	echo -e "$(ANSI_BOLD)BASIC TARGETS$(ANSI_NC)";							\
	echo -e "\tall  re  help\n";											\
	echo -e "$(ANSI_BOLD)FILES TARGETS$(ANSI_NC)";							\
	echo -e -n "\t$(NAME)";												\
	echo -e -n "$(OBJS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).o  ";		\
	echo -e "$(ARCHIVES_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n";		\
	echo -e "$(ANSI_BOLD)DIRECTORIES TARGETS$(ANSI_NC)";					\
	echo -e "\t$(OBJS_DIR)  $(ARCHIVES_DIR)\n";							\
	echo -e "$(ANSI_BOLD)CLEANUP TARGETS$(ANSI_NC)";						\
	echo -e "\tclean  fclean  lclean  dclean\n\n";							\
	echo -e "$(ANSI_BOLD)MINILIBX TARGETS$(ANSI_NC)";						\
	echo -e "\tminilibx  minilibx-$(ANSI_FG_RED)<target>$(ANSI_NC)\n";		\
	echo -e "$(ANSI_BOLD)MINILIBX FILES TARGETS$(ANSI_NC)";				\
	echo -e "\t$(MLX_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n\n";	\
	echo -e "$(ANSI_BOLD)LIBFT TARGETS$(ANSI_NC)";							\
	echo -e "\tlibft  libft-$(ANSI_FG_RED)<target>$(ANSI_NC)\n";			\
	echo -e "$(ANSI_BOLD)LIBFT FILES TARGETS$(ANSI_NC)";					\
	echo -e "\t$(LFT_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n"

# **************************************************************************** #

# Ignore the following files during rule completeness check
.PHONY:	all clean fclean lclean dclean libft libft-% minilibx minilibx-% re help

# **************************************************************************** #
