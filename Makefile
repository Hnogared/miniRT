# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 19:48:41 by hnogared          #+#    #+#              #
#    Updated: 2024/01/13 21:44:53 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Path to the Makefile's includes #
MK_INCLUDES_DIR	:=	Makefile_includes

# Makefile for compilation variables declaration #
include $(MK_INCLUDES_DIR)/Makefile.compilation_variables

# Makefile for graphical display variables declaration # 
include $(MK_INCLUDES_DIR)/Makefile.graphical_variables

# Makefile for functions definitions #
include $(MK_INCLUDES_DIR)/Makefile.functions

# * STANDARD RULES *********************************************************** #

all:	intro $(NAME)

## Compilation rules ##
# Compile the executable depending on the libraries archives and header files, #
#  as well as all the object files #
$(NAME):	$(ARCHS_DEPEND) $(INCL_DEPEND) $(OBJS) | add_bonus_flag print_flags
	$(call custom_loading_command,										\
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(AUTO_IFLAGS) $(AUTO_LFLAGS),	\
		"$(THEME_COLOR)Creating executable \ \ : $(NAME)$(ANSI_NC)")

# Compile the executable as the bonus build depending on the libraries #
#  archives and header files, as well as all the object files #
bonus:	$(NAME)

# Compile an object file depending on its source file and the object directory #
$(OBJS_DIR)/%.o:	%.c $(ARCHS_DEPEND) $(INCL_DEPEND) | get_obj_load	\
					$(OBJS_DIR) add_bonus_flag print_flags
	$(call custom_loading_command,									\
		$(CC) $(CFLAGS) -c $< -o $@ $(AUTO_IFLAGS) $(AUTO_LFLAGS),	\
		"$(THEME_COLOR)Compiling object file : $@$(ANSI_NC)")
	$(eval PROGRESS := $(shell echo $$(( $(PROGRESS) + 1 ))))
	$(call put_loading, $(PROGRESS), $(LOAD), $(MAX_PROG_LENGTH))

# Calculate the amount of object files to compile for the loading bar #
get_obj_load:
ifndef CALL_MAKE
	$(eval LOAD := $(shell $(MAKE) $(MAKECMDGOALS) -n SERIOUS=TRUE CALL_MAKE=0\
		| grep '^gcc' | grep -v 'miniRT' | wc -l))
	$(eval PROGRESS := 0)
endif

# Add the bonus compilation flag if 'bonus' is the called rule #
add_bonus_flag:
ifneq (,$(findstring bonus, $(MAKECMDGOALS)))
	$(eval CFLAGS += -D RT_BONUS=1)
endif

# Display the flags currently used for compilation #
print_flags:
ifneq ($(COMPIL_LOAD), 0)
	$(call custom_command, true, "compilation flags: $(CFLAGS)")
else ifneq (,$(findstring re, $(MAKECMDGOALS)))
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

# Remove all object files and the executable, then recompile #
re:	fclean $(NAME)

# Remove all object files and the executable, the recompile with bonus features #
re-bonus:	fclean bonus


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
	$(call custom_command, cp $^ $(ARCHIVES_DIR),\
		"$(THEME_COLOR)Retrieved the minilibx $(MLX_ARCHIVES) files.$(ANSI_NC)")

# Copy the minilibx header files into the includes directory #
# Depends on the minilibx source include files #
$(MLX_INCL_DEPEND):	$(MLX_INCL_SRCS)
	$(call custom_command, cp $^ $(INCLUDES_DIR),\
		"$(THEME_COLOR)Retrieved the minilibx $(MLX_INCLUDES) files.$(ANSI_NC)")


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
	$(call custom_command, cp $^ $(ARCHIVES_DIR),\
		"$(THEME_COLOR)Retrieved the libft $(LFT_ARCHIVES) files.$(ANSI_NC)")

# Copy the libft header files into the includes directory #
# Depends on the libft source include files #
$(LFT_INCL_DEPEND):	$(LFT_INCL_SRCS)
	$(call custom_command, cp $^ $(INCLUDES_DIR),\
		"$(THEME_COLOR)Retrieved the libft $(LFT_INCLUDES) files.$(ANSI_NC)")


# * MISCELANEOUS RULES ******************************************************* #

# Display a short list of all available rules #
help:
	@echo "\nMiniRT Makefile help - Available targets\n";				\
	echo "$(ANSI_BOLD)BASIC TARGETS$(ANSI_NC)";							\
	echo "\tall  re  bonus  re-bonus  help  test  norm";				\
	echo "$(ANSI_BOLD)FILES TARGETS$(ANSI_NC)";							\
	echo -n "\t$(NAME)";												\
	echo -n "$(OBJS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).o  ";		\
	echo "$(ARCHIVES_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a";		\
	echo "$(ANSI_BOLD)DIRECTORIES TARGETS$(ANSI_NC)";					\
	echo "\t$(OBJS_DIR)  $(ARCHIVES_DIR)";								\
	echo "$(ANSI_BOLD)CLEANUP TARGETS$(ANSI_NC)";						\
	echo "\tclean  fclean  lclean  dclean";								\
	echo "$(ANSI_BOLD)MINILIBX TARGETS$(ANSI_NC)";						\
	echo "\tminilibx  minilibx-$(ANSI_FG_RED)<target>$(ANSI_NC)";		\
	echo "$(ANSI_BOLD)MINILIBX FILES TARGETS$(ANSI_NC)";				\
	echo "\t$(MLX_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a";		\
	echo "$(ANSI_BOLD)LIBFT TARGETS$(ANSI_NC)";							\
	echo "\tlibft  libft-$(ANSI_FG_RED)<target>$(ANSI_NC)";				\
	echo "$(ANSI_BOLD)LIBFT FILES TARGETS$(ANSI_NC)";					\
	echo "\t$(LFT_SRCS_DIR)/$(ANSI_FG_RED)<file_name>$(ANSI_NC).a\n"

# Compile the executable if needed and run it with the tester script #
test:	$(NAME)
	@bash tester.sh

# Run the norm checking script #
norm:
	@bash normer.sh

# Run the intro script if compilations are taking place #
ifneq ($(COMPIL_LOAD), 0)
intro:
	@bash intro.sh
endif


# **************************************************************************** #

# Ignore the following files during rule completeness check
.PHONY:	all clean fclean lclean dclean libft libft-% minilibx minilibx-% re	\
		help norm intro bonus re-bonus add_bonus_flags

# **************************************************************************** #
