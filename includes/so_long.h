/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:49:58 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/04 14:50:01 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_texture
{
	void	*wall;
	void	*floor;
	void	*exit;
	void	*player;
	void	*exit_pl;
	void	*collect;
	int		size;
}	t_texture;

typedef struct s_map
{
	t_texture	tex;
	char		**matrix;
	int			player_x;
	int			player_y;
	int			collect_count;
	int			line_size;
	int			line_num;
	int			moves_count;
}	t_map;

typedef struct s_pointers
{
	void		*mlx;
	void		*win;
	t_map		map;
}	t_pointers;

# define WALL_PATH "./textures/myAssets/64/wall.xpm"
# define FLOOR_PATH "./textures/myAssets/64/floor.xpm"
# define EXIT_PATH "./textures/myAssets/64/exit.xpm"
# define PLAYER_PATH "./textures/myAssets/64/player.xpm"
# define PLAYER_ON_EXIT_PATH "./textures/myAssets/64/exit_pl.xpm"
# define COLLECTABLE_PATH "./textures/myAssets/64/collect.xpm"

# define TRUE 1
# define FALSE 0
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

void	error_handling(t_pointers *ptr, char *msg);
void	set_hook_and_loop(t_pointers *ptr);
void	init_pointers(t_pointers *ptr);
int		on_destroy(t_pointers *ptr);
void	free_matrix(void **matrix, int size);
int		on_keypress(int keysym, t_pointers *ptr);
void	load_map(t_pointers *ptr);
void	load_img(t_pointers *ptr, int x, int y);
void	check_perimeter(t_pointers *ptr, int i, int j);
void	check_path(t_pointers *ptr, int p, int e, int c);
int		has_path_to_collectables(t_map *map, int i, int j, int **visited);
int		has_path_to_exit(t_map map, int i, int j, int **visited);
void	set_map(t_pointers *ptr, char *map_path);
void	check_map_validation(t_pointers *ptr);
int		get_object_position(t_map map, char object, int *i, int *j);
int		move(t_pointers *ptr, int direction);

#endif