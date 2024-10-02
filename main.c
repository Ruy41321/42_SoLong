/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:58:00 by lpennisi          #+#    #+#             */
/*   Updated: 2024/10/02 23:49:15 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	init_pointer(t_pointers *ptr);

void	start_map(t_pointers *ptr)
{
	init_pointers(ptr);
	load_map(ptr);
	set_hook_and_loop(ptr);
}

int	main(int argc, char **argv)
{
	t_pointers	ptr;
	char		*ext;
	int			i;

	if (argc < 2)
		error_handling(&ptr, "Invalid Number of Arguments");
	ptr.map = malloc(sizeof(t_map) * argc - 1);
	ptr.map_index = 0;
	init_pointer(&ptr);
	i = 0;
	ptr.map_index = -1;
	ptr.map_num = 0;
	while (++i < argc)
	{
		ptr.map_index++;
		ext = ft_get_extention(argv[i]);
		if (ft_strncmp(ext, "ber", 3))
		{
			free(ext);
			error_handling(&ptr, "Wrong extention");
		}
		free(ext);
	}
	i = 0;
	ptr.map_index = -1;
	ptr.map_num = -1;
	while (++i < argc)
	{
		ptr.map_index++;
		ptr.map_num++;
		set_map(&ptr, argv[i]);
		check_map_validation(&ptr);
	}
	ptr.map_index = 0;
	start_map(&ptr);
	return (0);
}

void	init_pointer(t_pointers *ptr)
{
	ptr->mlx = NULL;
	ptr->win = NULL;
	ptr->map[ptr->map_index].matrix = NULL;
	ptr->map[ptr->map_index].tex.collect = NULL;
}

void	load_map(t_pointers *ptr)
{
	int	x;
	int	y;

	y = -1;
	while (++y < ptr->map[ptr->map_index].line_num)
	{
		x = -1;
		while (++x < ptr->map[ptr->map_index].line_size)
			load_img(ptr, x, y);
	}
}
