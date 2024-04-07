/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:55:54 by lpennisi          #+#    #+#             */
/*   Updated: 2024/02/29 15:20:47 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	on_destroy(t_pointers *ptr)
{
	if (ptr->map.matrix)
		free_matrix((void **)ptr->map.matrix, ptr->map.line_num);
	if (ptr->win)
		mlx_destroy_window(ptr->mlx, ptr->win);
	if (ptr->mlx)
	{
		if (ptr->map.tex.collect)
		{
			mlx_destroy_image(ptr->mlx, ptr->map.tex.collect);
			mlx_destroy_image(ptr->mlx, ptr->map.tex.exit);
			mlx_destroy_image(ptr->mlx, ptr->map.tex.floor);
			mlx_destroy_image(ptr->mlx, ptr->map.tex.player);
			mlx_destroy_image(ptr->mlx, ptr->map.tex.wall);
			mlx_destroy_image(ptr->mlx, ptr->map.tex.exit_pl);
		}
		mlx_destroy_display(ptr->mlx);
		free(ptr->mlx);
	}
	exit (0);
	return (0);
}

int	on_keypress(int keysym, t_pointers *ptr)
{
	(void)ptr;
	if (keysym == ESC)
		on_destroy(ptr);
	if (keysym == W || keysym == A || keysym == S || keysym == D)
	{
		if (move(ptr, keysym))
		{
			ft_printf("Congratulation you WON\n");
			on_destroy(ptr);
		}
	}
	return (0);
}
