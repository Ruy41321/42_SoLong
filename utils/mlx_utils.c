/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:57:19 by lpennisi          #+#    #+#             */
/*   Updated: 2024/02/29 15:31:52 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_textures(t_pointers *ptr);

void	set_hook_and_loop(t_pointers *ptr)
{
	mlx_hook(ptr->win, KeyRelease, KeyReleaseMask, &on_keypress, ptr);
	mlx_hook(ptr->win, DestroyNotify, StructureNotifyMask, &on_destroy, ptr);
	mlx_loop(ptr->mlx);
}

void	init_pointers(t_pointers *ptr)
{
	int	size;

	ptr->mlx = mlx_init();
	if (!ptr->mlx)
		error_handling(ptr, "MLX Initialization Error");
	size = ptr->map.tex.size;
	ptr->win = mlx_new_window(ptr->mlx, \
	size * ptr->map.line_size, size * ptr->map.line_num, "PVE_HERO");
	if (!ptr->win)
		error_handling(ptr, "WINDOWS Initializzaztion Error");
	init_textures(ptr);
}

void	init_textures(t_pointers *ptr)
{
	ptr->map.tex.wall = mlx_xpm_file_to_image(ptr->mlx, \
	WALL_PATH, &ptr->map.tex.size, &ptr->map.tex.size);
	ptr->map.tex.floor = mlx_xpm_file_to_image(ptr->mlx, \
	FLOOR_PATH, &ptr->map.tex.size, &ptr->map.tex.size);
	ptr->map.tex.exit = mlx_xpm_file_to_image(ptr->mlx, \
	EXIT_PATH, &ptr->map.tex.size, &ptr->map.tex.size);
	ptr->map.tex.player = mlx_xpm_file_to_image(ptr->mlx, \
	PLAYER_PATH, &ptr->map.tex.size, &ptr->map.tex.size);
	ptr->map.tex.exit_pl = mlx_xpm_file_to_image(ptr->mlx, \
	PLAYER_ON_EXIT_PATH, &ptr->map.tex.size, &ptr->map.tex.size);
	ptr->map.tex.collect = mlx_xpm_file_to_image(ptr->mlx, \
	COLLECTABLE_PATH, &ptr->map.tex.size, &ptr->map.tex.size);
}
