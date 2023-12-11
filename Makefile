# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 19:48:41 by hnogared          #+#    #+#              #
#    Updated: 2023/12/11 08:45:43 by motoko           ###   ########.fr        #
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
VPATH			:=	$(SRCS_DIR):				\
					$(SRCS_DIR)/object:			\
					$(SRCS_DIR)/display:		\
					$(SRCS_DIR)/parsing:		\
					$(SRCS_DIR)/user_interface:	\
					$(SRCS_DIR)/vector:			\
					$(SRCS_DIR)/raytracing:		\
					$(SRCS_DIR)/utils

# Source files names #
SRCS			:=	main.c					\
					check_file.c			\
					get_file.c				\
					check_scene.c			\
					check_numbers.c			\
					check_range_numbers.c	\
					conv_hexa.c				\
					init_objs_1.c			\
					init_objs_2.c			\
					get_object_color.c		\
					object_creation.c		\
					object_interaction.c	\
					object_modification.c	\
					print_object_data.c		\
					print_object_data_2.c	\
					check_args.c			\
					image_handling.c		\
					window_handling.c		\
					window_modification.c	\
					main_window.c			\
					rgb_color.c				\
					keyboard.c				\
					free_and_exit.c			\
					check_range_numbers1.c	\
					handle_errors.c			\
					vect.c					\
					vect_utils.c			\
					vect_utils_2.c			\
					vect_utils_3.c			\
					vect_utils_4.c			\
					vect_utils_5.c			\
					vect_calc.c				\
					vect_try.c				\
					vect_try_2.c			\
					set_view_rays.c			\
					raytrace.c


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


## Loading variables ##
# The total load of a make task #
LOAD		:=	0

ifndef CALL_MAKE
COMPIL_LOAD := $(shell $(MAKE) $(MAKECMDGOALS) -n SERIOUS=TRUE CALL_MAKE=0\
	| grep '^gcc' | wc -l)
endif

# Track the progress of a make task #
PROGRESS	:=	0


# * PARAMETER VARIABLES ****************************************************** #

# Force the program's opened window to the specified width #
ifdef WIN_WIDTH
CFLAGS	+=	-D WIN_WIDTH=$(WIN_WIDTH)
endif

# Force the program's opened window to the specified height #
ifdef WIN_HEIGHT
CFLAGS	+=	-D WIN_HEIGHT=$(WIN_HEIGHT)
endif

# Force the program's default pixel ratio #
# Ex: A ratio of 2 would make each calculated pixel to be 2 screen pixels wide #
ifdef PIXEL_RATIO
CFLAGS	+=	-D DEFAULT_PIXEL_RATIO=$(PIXEL_RATIO)
endif

# **************************************************************************** #

# **************************************************************************** #
# * STANDARD RULES *********************************************************** #

all:	$(NAME)

## Compilation rules ##
# Compile the executable depending on the libraries archives and header files, #
#  as well as all the object files #
$(NAME):	$(ARCHS_DEPEND) $(INCL_DEPEND) $(OBJS) | print_flags
	$(call custom_loading_command,										\
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(AUTO_IFLAGS) $(AUTO_LFLAGS),	\
		"$(THEME_COLOR)Creating executable \ \ : $(NAME)$(ANSI_NC)")

# Compile an object file depending on its source file and the object directory #
$(OBJS_DIR)/%.o:	%.c | get_obj_load $(OBJS_DIR) print_flags
	$(call custom_loading_command,									\
		$(CC) $(CFLAGS) -c $< -o $@ $(AUTO_IFLAGS) $(AUTO_LFLAGS),	\
		"$(THEME_COLOR)Compiling object file : $@$(ANSI_NC)")
	$(eval PROGRESS := $(shell echo $$(( $(PROGRESS) + 1 ))))
	$(call put_loading, $(PROGRESS), $(LOAD), $(MAX_PROG_LENGTH))

# Calculate the amount of object files to compile for the loading bar #
get_obj_load:
ifndef CALL_MAKE
	$(eval LOAD := $(shell $(MAKE) -n SERIOUS=TRUE CALL_MAKE=0 | grep '^gcc'\
		 | grep -v 'miniRT' | wc -l))
	$(eval PROGRESS := 0)
endif

# Display the flags currently used for compilation #
print_flags:
ifneq ($(COMPIL_LOAD),0)
	$(call custom_command, true, "compilation flags: $(CFLAGS)")
else ifeq ("$(MAKECMDGOALS)","re")
	$(call custom_command, true, "compilation flags: $(CFLAGS)")
endif


## Directories rules ##
# Create the object directory if missing #
$(OBJS_DIR):
	$(call custom_command,										\
		mkdir $(OBJS_DIR),										\
		"$(THEME_COLOR)Created the $(OBJS_DIR)/ directory.")

# Create the archive directory if missing #
$(ARCHIVES_DIR):
	$(call custom_command,														\
		mkdir $(ARCHIVES_DIR),													\
		"$(THEME_COLOR)A wild $(ARCHIVES_DIR)/ directory appeared !$(ANSI_NC)")


## Cleanup rules ##
# Remove all object files #
clean:
	$(call custom_command,										\
		$(RM) $(OBJS),											\
		"$(THEME_COLOR)Yeet and delete $(OBJS) !$(ANSI_NC)")

# Remove all object files and the executable #
fclean:	clean
	$(call custom_command,							\
		$(RM) $(NAME),								\
		"$(THEME_COLOR)Removed $(NAME).$(ANSI_NC)")

# Remove all minilibx and libft archives from the archive dir #
lclean:
	$(call custom_command,												\
		$(RM) $(MLX_ARCHS_DEPEND) $(LFT_ARCHS_DEPEND),					\
		"$(THEME_COLOR)Deleted $(ARCHS_DEPEND), it's gone.$(ANSI_NC)")

# Remove all object files and the object directory #
dclean:	clean
	$(call custom_command,												\
		$(RM) $(OBJS_DIR),												\
		"$(THEME_COLOR)Deleted the $(OBJS_DIR)/ directory.$(ANSI_NC)")

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
	@echo "\nMiniRT Makefile help - Available targets\n";				\
	echo "$(ANSI_BOLD)BASIC TARGETS$(ANSI_NC)";							\
	echo "\tall  re  help  test";										\
	echo "$(ANSI_BOLD)FILES TARGETS$(ANSI_NC)";							\
	echo -n "\t$(NAME)";												\
	echo -n "$(OBJS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).o  ";		\
	echo "$(ARCHIVES_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a";		\
	echo "$(ANSI_BOLD)DIRECTORIES TARGETS$(ANSI_NC)";					\
	echo "\t$(OBJS_DIR)  $(ARCHIVES_DIR)";							\
	echo "$(ANSI_BOLD)CLEANUP TARGETS$(ANSI_NC)";						\
	echo "\tclean  fclean  lclean  dclean";							\
	echo "$(ANSI_BOLD)MINILIBX TARGETS$(ANSI_NC)";						\
	echo "\tminilibx  minilibx-$(ANSI_FG_RED)<target>$(ANSI_NC)";		\
	echo "$(ANSI_BOLD)MINILIBX FILES TARGETS$(ANSI_NC)";				\
	echo "\t$(MLX_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a";	\
	echo "$(ANSI_BOLD)LIBFT TARGETS$(ANSI_NC)";							\
	echo "\tlibft  libft-$(ANSI_FG_RED)<target>$(ANSI_NC)";			\
	echo "$(ANSI_BOLD)LIBFT FILES TARGETS$(ANSI_NC)";					\
	echo "\t$(LFT_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n"

test:
	@bash tester.sh

# **************************************************************************** #

# Ignore the following files during rule completeness check
.PHONY:	all clean fclean lclean dclean libft libft-% minilibx minilibx-% re	\
		help intro

# **************************************************************************** #
