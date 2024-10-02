/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:55:54 by lpennisi          #+#    #+#             */
/*   Updated: 2024/10/02 23:46:40 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	on_destroy(t_pointers *ptr, int esc_pressed)
{
	if (ptr->map[ptr->map_index].matrix)
		free_matrix((void **)ptr->map[ptr->map_index].matrix, ptr->map[ptr->map_index].line_num);
	if (ptr->win)
		mlx_destroy_window(ptr->mlx, ptr->win);
	if (ptr->mlx)
	{
		if (ptr->map[ptr->map_index].tex.collect)
		{
			mlx_destroy_image(ptr->mlx, ptr->map[ptr->map_index].tex.collect);
			mlx_destroy_image(ptr->mlx, ptr->map[ptr->map_index].tex.exit);
			mlx_destroy_image(ptr->mlx, ptr->map[ptr->map_index].tex.floor);
			mlx_destroy_image(ptr->mlx, ptr->map[ptr->map_index].tex.player);
			mlx_destroy_image(ptr->mlx, ptr->map[ptr->map_index].tex.wall);
			mlx_destroy_image(ptr->mlx, ptr->map[ptr->map_index].tex.exit_pl);
		}
		mlx_destroy_display(ptr->mlx);
		free(ptr->mlx);
	}
	ptr->map_index++;
	if (ptr->map_index <= ptr->map_num && !esc_pressed)
		start_map(ptr);
	else
	{
		if (ptr->map_index <= ptr->map_num)
		{
			init_pointers(ptr);
			on_destroy(ptr, 1);
		}
		free(ptr->map);
		exit (0);
	}
	return (0);
}

int	on_keypress(int keysym, t_pointers *ptr)
{
	(void)ptr;
	if (keysym == ESC)
		on_destroy(ptr, 1);
	if (keysym == W || keysym == A || keysym == S || keysym == D)
	{
		if (move(ptr, keysym))
		{
			ft_printf("Congratulation you WON\n");
			on_destroy(ptr, 0);
		}
	}
	return (0);
}
