# **************************************************************************** #
# 1. BUILD VARIABLES                                                           #
# **************************************************************************** #

NAME			:=	cub3D
NAME_B			:=	cub3D_bonus
HEADER_DIR		:=	include/mandatory/
SOURCE_DIR		:=	src/mandatory/
HEADER_DIR_B	:=	include/bonus/
SOURCE_DIR_B	:=	src/bonus/

# **************************************************************************** #
# 2. SOURCE CODE                                                               #
# **************************************************************************** #

override SOURCE_HOOKS		:=	$(addprefix hooks/, collision destroy_hook focus_hook key_hook loop_hook move)
override SOURCE_RENDERING	:=	$(addprefix rendering/, dda_utils draw_frame render_map)
override HEADER_FILES		:=	colors cub3D raycasting parse_cub_file
override SOURCE_FILES		:=	$(addprefix raycasting/, $(SOURCE_HOOKS) $(SOURCE_RENDERING) quit) \
								$(addprefix errors/, puterr) \
								$(addprefix parsing/, init_data_map_utils init_data_map interpret_line is_valid_map_path parse_cub_file_utils parse_cub_file) \
								$(addprefix tools/, ft_sprintf ft_sprintf_utils) \
								main

# **************************************************************************** #
# 3. OTHER COMPILATION VARIABLES                                               #
# **************************************************************************** #

override BUILD_DIR	:=	.dist/
override SOURCE		:=	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SOURCE_FILES)))
override HEADER		:=	$(addprefix $(HEADER_DIR), $(addsuffix .h, $(HEADER_FILES)))
override OBJ		:=	$(patsubst $(SOURCE_DIR)%.c, $(BUILD_DIR)%.o, $(SOURCE))
override DEPS		:=	$(patsubst %.o, %.d, $(OBJ))
override DIRS		:=	$(sort $(dir $(OBJ) $(DEPS)))

override LIB	:=	lib/
override MLX	:=	mlx/

# **************************************************************************** #
# 4. SOURCE CODE FOR BONUS                                                     #
# **************************************************************************** #

override SOURCE_HOOKS_B		:=	$(addprefix hooks/, collision destroy_hook focus_hook key_hook loop_hook mouse_hook move)
override SOURCE_RENDERING_B	:=	$(addprefix rendering/, dda_utils draw_frame render_map)
override HEADER_FILES_B		:=	colors cub3D raycasting_bonus parse_cub_file
override SOURCE_FILES_B		:=	$(addprefix raycasting/, $(SOURCE_HOOKS_B) $(SOURCE_RENDERING_B) quit) \
								$(addprefix door/, door_interact) \
								$(addprefix errors/, puterr) \
								$(addprefix parsing/, init_data_map_utils init_data_map interpret_line is_valid_map_path parse_cub_file_utils parse_cub_file) \
								$(addprefix minimap/, draw_minimap init_minimap) \
								$(addprefix mouse_utils/, mouse_hide mouse_warp) \
								$(addprefix sprite/, draw_sprite load_sprite) \
								$(addprefix tools/, ft_sprintf ft_sprintf_utils) \
								main

# **************************************************************************** #
# 5. OTHER COMPILATION VARIABLES FOR BONUS                                     #
# **************************************************************************** #

override BUILD_DIR_B	:=	.dist_bonus/
override SOURCE_B		:=	$(addprefix $(SOURCE_DIR_B), $(addsuffix .c, $(SOURCE_FILES_B)))
override HEADER_B		:=	$(addprefix $(HEADER_DIR_B), $(addsuffix .h, $(HEADER_FILES_B)))
override OBJ_B			:=	$(patsubst $(SOURCE_DIR_B)%.c, $(BUILD_DIR_B)%.o, $(SOURCE_B))
override DEPS_B			:=	$(patsubst %.o, %.d, $(OBJ_B))
override DIRS_B			:=	$(sort $(dir $(OBJ_B) $(DEPS_B)))

# **************************************************************************** #
# 6. FLAGS AND VARIABLES                                                       #
# **************************************************************************** #

TURBO_FLAGS			:=	-O3 -flto -march=native -mtune=native -funroll-loops -ffast-math -falign-functions=32 -falign-loops=16
DEBUG_FLAGS			:=	-g3
CFLAGS				:=	-Wall -Wextra -Werror -MD $(DEBUG_FLAGS) #$(TURBO_FLAGS)
MAKEFLAGS			:=	--no-print-directory
RMFLAGS				:=	-rf
VG					:=	valgrind
VGFLAGS				:=	--leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes
override CC			:=	clang
override RM			:=	rm
override CLEAR		:=	clear
CALLGRIND_PRFL		:=	exec-profile.cub3D
CALLGRIND_PRFL_B	:=	exec-profile.cub3D_bonus
override VGCALL		:=	--tool=callgrind --callgrind-out-file=$(CALLGRIND_PRFL)
override VGCALL_B	:=	--tool=callgrind --callgrind-out-file=$(CALLGRIND_PRFL_B)
override KCACHE		:=	kcachegrind


# **************************************************************************** #
# 7. COMPILATION RULES                                                         #
# **************************************************************************** #

.PHONY: all
all: display $(NAME)

$(NAME): $(LIB) $(LIB)libft.a $(MLX) $(MLX)libmlx.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB)libft.a $(MLX)libmlx.a -L$(MLX) -L/opt/X11/lib -lXext -lXfixes -lX11 -lm -o $(NAME)
	@printf "\n\e[48;2;0;0;180m==============================================\e[0m\n\n"

$(BUILD_DIR)%.o: $(SOURCE_DIR)%.c $(HEADER) Makefile | $(DIRS)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB)include -I$(MLX) -c $< -o $@

# **************************************************************************** #
# 7. COMPILATION RULES FOR BONUS                                               #
# **************************************************************************** #

.PHONY: bonus
bonus: display_b $(NAME_B)

$(NAME_B): $(LIB) $(LIB)libft.a $(MLX) $(MLX)libmlx.a $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIB)libft.a $(MLX)libmlx.a -L$(MLX) -lXext -lXfixes -lX11 -lm -o $(NAME_B)
	@printf "\n\e[48;2;0;180;180m==============================================\e[0m\n\n"

$(BUILD_DIR_B)%.o: $(SOURCE_DIR_B)%.c $(HEADER_B) Makefile | $(DIRS_B)
	$(CC) $(CFLAGS) -I$(HEADER_DIR_B) -I$(LIB)include -I$(MLX) -c $< -o $@

# **************************************************************************** #
# 7. GENERAL RULES                                                             #
# **************************************************************************** #

$(LIB)libft.a: lib

$(MLX)libmlx.a: mlx

.PHONY: mlx
mlx: force
	@printf "\n\e[48;2;180;0;0m========== [ MINILIBX COMPILATION ] ==========\e[0m\n\n"
	@$(MAKE) $(MAKEFLAGS) -C $(MLX) all
	@printf "\n\e[48;2;180;0;0m==============================================\e[0m\n\n"

.PHONY: lib
lib: force
	@printf "\n\e[48;2;0;180;0m=========== [ LIBFT COMPILATION ] ============\e[0m\n\n"
	@$(MAKE) $(MAKEFLAGS) -C $(LIB) all
	@printf "\n\e[48;2;0;180;0m==============================================\e[0m\n\n"

.PHONY: display
display:
	@printf "\n\e[48;2;0;0;180m=========== [ CUB3D COMPILATION ] ============\e[0m\n\n"

.PHONY: display_b
display_b:
	@printf "\n\e[48;2;0;180;180m======== [ CUB3D BONUS COMPILATION ] =========\e[0m\n\n"

.PHONY: force
force:
	@true

.PHONY: clean
clean:
	$(MAKE) -C $(LIB) clean
	$(MAKE) -C $(MLX) clean
	$(RM) $(RMFLAGS) $(BUILD_DIR)
	$(RM) $(RMFLAGS) $(BUILD_DIR_B)
	$(RM) $(RMFLAGS) $(CALLGRIND_PRFL)
	$(RM) $(RMFLAGS) $(CALLGRIND_PRFL_B)

.PHONY: fclean
fclean: clean
	$(MAKE) -C $(LIB) fclean
	$(RM) $(RMFLAGS) $(NAME)
	$(RM) $(RMFLAGS) $(NAME_B)

.PHONY: re
re: fclean
	$(MAKE)

.PHONY: norm
norm:
	@norminette ./src ./include $(LIBFT_DIR) | grep "Error"

.PHONY: run
run:
	$(CLEAR)
	$(MAKE)
	$(CLEAR)
	./$(NAME) assets/maps/valid_maps/map_subject.cub

.PHONY: vg
vg:
	$(CLEAR)
	$(MAKE)
	$(CLEAR)
	$(VG) $(VGFLAGS) ./$(NAME) assets/maps/valid_maps/map_subject.cub

.PHONY: cg
cg:
	$(CLEAR)
	$(MAKE)
	$(RM) $(RMFLAGS) $(CALLGRIND_PRFL)
	$(CLEAR)
	$(VG) $(VGCALL) ./$(NAME) assets/maps/valid_maps/map_subject.cub
	$(KCACHE) $(CALLGRIND_PRFL)

test:
	$(CLEAR)
	$(MAKE)
	./scripts/parsing_tester.sh

$(DIRS):
	@mkdir -p $@

$(DIRS_B):
	@mkdir -p $@

# **************************************************************************** #
# 8. BONUS RULES                                                               #
# **************************************************************************** #

.PHONY: bre
bre: fclean
	$(MAKE) bonus

.PHONY: brun
brun:
	$(CLEAR)
	$(MAKE) bonus
	$(CLEAR)
	./$(NAME_B) assets/maps/subject\ bonus.cub

.PHONY: bvg
bvg:
	$(CLEAR)
	$(MAKE) bonus
	$(CLEAR)
	$(VG) $(VGFLAGS) ./$(NAME_B) assets/maps/subject\ bonus.cub

.PHONY: bcg
bcg:
	$(CLEAR)
	$(MAKE) bonus
	$(RM) $(RMFLAGS) $(CALLGRIND_PRFL_B)
	$(CLEAR)
	$(VG) $(VGCALL_B) ./$(NAME_B) assets/maps/subject\ bonus.cub
	$(KCACHE) $(CALLGRIND_PRFL_B)

-include $(DEPS)
-include $(DEPS_B)
