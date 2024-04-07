/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_extention.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:57:07 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/04 13:38:49 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_extention(char *pathfile)
{
	char	**words;
	char	*ext;
	int		i;

	i = 0;
	ext = NULL;
	words = ft_split(pathfile, '.');
	while (words[i])
	{
		if (ext)
			free(ext);
		ext = ft_strdup(words[i]);
		free(words[i]);
		i++;
	}
	free(words);
	return (ext);
}
