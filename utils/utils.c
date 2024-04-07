/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:03:39 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/04 15:44:41 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	error_handling(t_pointers *ptr, char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	on_destroy(ptr);
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

	tex = &(ptr->map.tex);
	x1 = x * ptr->map.tex.size;
	y1 = y * ptr->map.tex.size;
	if (ptr->map.matrix[y][x] == '1')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->wall, x1, y1);
	else if (ptr->map.matrix[y][x] == '0')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->floor, x1, y1);
	else if (ptr->map.matrix[y][x] == 'P')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->player, x1, y1);
	else if (ptr->map.matrix[y][x] == 'X')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->exit_pl, x1, y1);
	else if (ptr->map.matrix[y][x] == 'E')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->exit, x1, y1);
	else if (ptr->map.matrix[y][x] == 'C')
		mlx_put_image_to_window(ptr->mlx, ptr->win, tex->collect, x1, y1);
}
