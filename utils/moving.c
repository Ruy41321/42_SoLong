/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:04:04 by lpennisi          #+#    #+#             */
/*   Updated: 2024/02/29 15:30:41 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		move_player(t_map *map, int new_x, int new_y);

int	move(t_pointers *ptr, int direction)
{
	int	new_x;
	int	new_y;

	new_x = ptr->map.player_x;
	new_y = ptr->map.player_y;
	if (direction == W)
		new_y -= 1;
	if (direction == A)
		new_x -= 1;
	if (direction == S)
		new_y += 1;
	if (direction == D)
		new_x += 1;
	if (ptr->map.matrix[new_y][new_x] == '1')
		return (0);
	system("clear");
	ft_printf("Moves count: %d\n", ptr->map.moves_count++);
	if (move_player(&ptr->map, new_x, new_y))
		return (1);
	load_map(ptr);
	return (0);
}

void	update_player_pos(t_map *map, int new_y, int new_x)
{
	map->player_y = new_y;
	map->player_x = new_x;
}

int	move_player(t_map *map, int new_x, int new_y)
{
	if (map->matrix[map->player_y][map->player_x] == 'X')
		map->matrix[map->player_y][map->player_x] = 'E';
	else
		map->matrix[map->player_y][map->player_x] = '0';
	update_player_pos(map, new_y, new_x);
	if (map->matrix[map->player_y][map->player_x] == 'E')
	{
		if (map->collect_count == 0)
			return (1);
		map->matrix[map->player_y][map->player_x] = 'X';
	}
	else
	{
		if (map->matrix[map->player_y][map->player_x] == 'C')
			map->collect_count--;
		map->matrix[map->player_y][map->player_x] = 'P';
	}
	return (0);
}
