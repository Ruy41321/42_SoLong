/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:37:15 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/04 16:29:22 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	get_line_num(char *path)
{
	int		fd;
	int		line_count;
	char	*line;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

void	update_map(t_pointers *ptr, int i)
{
	ptr->map.matrix[i] = NULL;
	ptr->map.tex.size = 64;
	ptr->map.moves_count = 0;
}

void	set_map(t_pointers *ptr, char *map_path)
{
	int	i;
	int	fd;

	ptr->map.line_num = get_line_num(map_path);
	if (ptr->map.line_num <= 0)
		error_handling(ptr, "Errore nell'apertura del file");
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		error_handling(ptr, "Errore nell'apertura del file");
	ptr->map.matrix = malloc(sizeof(char *) * (ptr->map.line_num + 1));
	ptr->map.matrix[0] = get_next_line(fd);
	ptr->map.line_size = ft_strlen(ptr->map.matrix[0]);
	i = 0;
	while (++i < ptr->map.line_num)
	{
		ptr->map.matrix[i] = get_next_line(fd);
		if (ft_strlen((ptr->map.matrix[i])) != ptr->map.line_size)
		{
			ptr->map.line_num = i + 1;
			error_handling(ptr, "The map must be rectangular");
		}
	}
	update_map(ptr, i);
	close(fd);
}

int	has_correct_value(char cell, int *p, int *e, int *c)
{
	if (cell == 'P')
		(*p)++;
	else if (cell == 'E')
		(*e)++;
	else if (cell == 'C')
		(*c)++;
	else if (cell != '0' && cell != '1')
		return (FALSE);
	return (TRUE);
}

void	check_map_validation(t_pointers *ptr)
{
	int	i;
	int	j;
	int	player;
	int	my_exit;
	int	collectable;

	player = 0;
	my_exit = 0;
	collectable = 0;
	i = -1;
	while (++i < ptr->map.line_num)
	{
		j = -1;
		while (++j < ptr->map.line_size)
		{
			check_perimeter(ptr, i, j);
			if (!has_correct_value(ptr->map.matrix[i][j], \
			&player, &my_exit, &collectable))
				error_handling(ptr, \
				"The only characters allow are 1, 0, P, C, E");
		}
	}
	check_path(ptr, player, my_exit, collectable);
}
