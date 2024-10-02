/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:03:39 by lpennisi          #+#    #+#             */
/*   Updated: 2024/10/02 23:23:40 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	error_handling(t_pointers *ptr, char *msg)
{
	ptr->map_index = 0;
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	on_destroy(ptr, 1);
}

void	free_matrix(void **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(matrix[i++]);
	free(matrix);
}

void	load_img(t_pointers *ptr, int x, int y)
{
	int			x1;
	int			y1;
	t_texture	*tex;

	tex = &(ptr->map[ptr->map_index].tex);
	x1 = x * ptr->map[ptr->map_index].tex.size;
	y1 = y * ptr->map[ptr->map_index].tex.size;
	if (ptr->map[ptr->map_index].matrix[y][x] == '1')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->wall, x1, y1);
	else if (ptr->map[ptr->map_index].matrix[y][x] == '0')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->floor, x1, y1);
	else if (ptr->map[ptr->map_index].matrix[y][x] == 'P')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->player, x1, y1);
	else if (ptr->map[ptr->map_index].matrix[y][x] == 'X')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->exit_pl, x1, y1);
	else if (ptr->map[ptr->map_index].matrix[y][x] == 'E')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->exit, x1, y1);
	else if (ptr->map[ptr->map_index].matrix[y][x] == 'C')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->collect, x1, y1);
}
