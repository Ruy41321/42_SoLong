/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:39:15 by lpennisi          #+#    #+#             */
/*   Updated: 2024/02/28 14:07:28 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_perimeter(t_pointers *ptr, int i, int j)
{
	if (ptr->map.matrix[i][j] != '1' \
	&& ((i == 0 || i + 1 == ptr->map.line_num) \
	|| j == 0 || j + 1 == ptr->map.line_size))
		error_handling(ptr, "Missing correct perimiter");
}

int	check_elementes(int p, int e, int c)
{
	if (p != 1)
		return (FALSE);
	if (e != 1)
		return (FALSE);
	if (c == 0)
		return (FALSE);
	return (TRUE);
}

int	get_object_position(t_map map, char object, int *i, int *j)
{
	*i = -1;
	while (++(*i) < map.line_num)
	{
		*j = -1;
		while (++*(j) < map.line_size)
		{
			if (map.matrix[*i][*j] == object)
				return (1);
		}
	}
	return (0);
}

int	**get_visited(t_map map)
{
	int	**visited;
	int	i;

	visited = malloc(map.line_num * sizeof(int *));
	i = -1;
	while (++i < map.line_num)
	{
		visited[i] = ft_calloc(map.line_size, sizeof(int));
	}
	return (visited);
}

void	check_path(t_pointers *ptr, int p, int e, int c)
{
	int	i;
	int	j;

	if (!check_elementes(p, e, c))
		error_handling(ptr, "Must have: 1 exit and position, 1+ collect");
	ptr->map.collect_count = c;
	get_object_position(ptr->map, 'P', &i, &j);
	if (!has_path_to_exit(ptr->map, i, j, get_visited(ptr->map)) || \
	!has_path_to_collectables(&(ptr->map), i, j, get_visited(ptr->map)))
		error_handling(ptr, "There is no available path to win");
	ptr->map.collect_count = c;
	ptr->map.player_x = j;
	ptr->map.player_y = i;
}
