/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/22 14:07:14 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*free_stash(char **stash)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

static void	ft_strjoin_free_stash(char **stash, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return ;
	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash)
		return ;
	len1 = ft_strlen(*stash);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return ((void)free_stash(stash));
	ft_memcpy(result, *stash, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free_stash(stash);
	*stash = result;
}

static char	*extract_and_trim(char **stash)
{
	size_t	len;
	char	*line;
	char	*new_stash;

	if (!*stash || **stash == '\0')
		return (NULL);
	len = 0;
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = ft_substr(*stash, 0, len);
	if (!line)
		return (free_stash(stash));
	new_stash = ft_strdup(*stash + len);
	free_stash(stash);
	if (!new_stash || *new_stash == '\0')
	{
		free_stash(&new_stash);
		return (line);
	}
	*stash = new_stash;
	return (line);
}

static void	fill_stash(int fd, char **stash, char *buffer)
{
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && (!*stash || !ft_strchr(*stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_stash(stash);
			return ;
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_strjoin_free_stash(stash, buffer);
		if (!*stash)
			return ;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*buffer;
	char		*next_line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (free_stash(&stash[fd]));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_stash(&stash[fd]));
	fill_stash(fd, &stash[fd], buffer);
	free(buffer);
	if (!stash[fd] || *stash[fd] == '\0')
		return (free_stash(&stash[fd]));
	next_line = extract_and_trim(&stash[fd]);
	return (next_line);
}

/* #include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);
	
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (1);
	char *line1;
	char *line2;
	char *line3;
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		if (line1)
			printf("Line 1: %s", line1);
		if (line2)
			printf("Line 2: %s", line2);
		if (line3)
			printf("Line 3: %s", line3);
		if (!line1 && !line2 && !line3)
			break;
		free(line1);	
		free(line2);	
		free(line3);	
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */
