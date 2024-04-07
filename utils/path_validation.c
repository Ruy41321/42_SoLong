/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:11:06 by lpennisi          #+#    #+#             */
/*   Updated: 2024/02/29 15:28:20 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	has_path_to_exit_recur(t_map map, int i, int j, int **visited)
{
	if (i < 0 || i >= map.line_num || j < 0 \
	|| j >= map.line_size || visited[i][j] || map.matrix[i][j] == '1')
		return (FALSE);
	visited[i][j] = 1;
	if (map.matrix[i][j] == 'E')
		return (TRUE);
	if (has_path_to_exit_recur(map, i - 1, j, visited) || \
		has_path_to_exit_recur(map, i + 1, j, visited) || \
		has_path_to_exit_recur(map, i, j - 1, visited) || \
		has_path_to_exit_recur(map, i, j + 1, visited))
		return (TRUE);
	return (FALSE);
}

int	has_path_to_exit(t_map map, int i, int j, int **visited)
{
	int	ret;

	ret = has_path_to_exit_recur(map, i, j, visited);
	free_matrix((void **)visited, map.line_num);
	return (ret);
}

void	check_path_collectable_recur(t_map *map, int i, int j, int **visited)
{
	int	*c;

	c = &map->collect_count;
	if (i < 0 || i >= map->line_num || j < 0 \
	|| j >= map->line_size || visited[i][j] || map->matrix[i][j] == '1')
		return ;
	visited[i][j] = 1;
	if (map->matrix[i][j] == 'C')
		*c -= 1;
	if (*c != 0)
	{
		check_path_collectable_recur(map, i - 1, j, visited);
		if (*c != 0)
		{
			check_path_collectable_recur(map, i + 1, j, visited);
			if (*c != 0)
			{
				check_path_collectable_recur(map, i, j - 1, visited);
				if (*c != 0)
					check_path_collectable_recur(map, i, j + 1, visited);
			}
		}
	}
}

int	has_path_to_collectables(t_map *map, int i, int j, int **visited)
{
	check_path_collectable_recur(map, i, j, visited);
	free_matrix((void **)visited, map->line_num);
	if (map->collect_count == 0)
		return (TRUE);
	return (FALSE);
}
