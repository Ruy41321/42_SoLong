/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:08:35 by lpennisi          #+#    #+#             */
/*   Updated: 2024/04/04 13:29:12 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		last_check(char *next_line);
char	*add_buffer(char *next_line, char *buf, char *backup, int buf_size);
char	*add_char(char *s, char ch);
void	restore(char **next_line, char *backup);

char	*get_next_line(int fd)
{
	static char	backup[BUFFER_SIZE + 1];
	char		*buffer;
	char		*next_line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	next_line = (char *)malloc(sizeof(char));
	*next_line = 0;
	restore(&next_line, backup);
	while (get_last(next_line) != '\n')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
			next_line = add_buffer(next_line, buffer, backup, bytes_read);
		if (bytes_read != BUFFER_SIZE)
			break ;
	}
	free(buffer);
	if (last_check(next_line))
		return (NULL);
	return (next_line);
}

void	restore(char **next_line, char *backup)
{
	char	*buffer;

	if (ft_strlen(backup))
	{
		buffer = ft_strdup(backup);
		backup[0] = 0;
		*next_line = add_buffer(*next_line, buffer, backup, ft_strlen(buffer));
		free(buffer);
	}
	else
		backup[0] = 0;
}

char	*add_buffer(char *next_line, char *buf, char *backup, int buf_size)
{
	int	n;
	int	f;
	int	buf_len;

	f = 1;
	n = 0;
	while (n < buf_size)
	{
		if (f)
		{
			next_line = add_char(next_line, buf[n]);
			if (buf[n] == '\n')
				f = 0;
		}
		else
		{
			buf_len = ft_strlen(backup);
			backup[buf_len] = buf[n];
			backup[buf_len + 1] = 0;
		}
		n++;
	}
	return (next_line);
}

char	*add_char(char *s, char ch)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	ft_strcpy(ret, s);
	ret[ft_strlen(s)] = ch;
	ret[ft_strlen(s) + 1] = '\0';
	free(s);
	return (ret);
}

/**
 * The instruction in the if delete \n if its last char
 * for the correct behavior of SO_LONG
*/
int	last_check(char *next_line)
{
	int	len;

	len = ft_strlen(next_line);
	if (len)
	{
		if (next_line[len - 1] == '\n')
			next_line[len - 1] = '\0';
		return (0);
	}
	free(next_line);
	return (1);
}
