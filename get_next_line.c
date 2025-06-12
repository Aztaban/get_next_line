/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/12 02:57:10 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*free_stash(char **stash)
{
	if (stash && *stash)
		free(*stash);
	if (stash)
		*stash = NULL;
	return (NULL);
}

static void	ft_strjoin_free_stash(char **stash, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash || !s2)
		return ;
	len1 = ft_strlen(*stash);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
	{
		free_stash(stash);
		return ;
	}
	ft_memcpy(result, *stash, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(*stash);
	*stash = result;
}

static char	*extract_and_trim(char **stash)
{
	size_t	len;
	char	*line;
	char	*new_stash;

	len = 0;
	if (!*stash || **stash == '\0')
		return (NULL);
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = ft_substr(*stash, 0, len);
	if (!(*stash)[len])
		return (free_stash(stash), line);
	new_stash = ft_strdup(*stash + len);
	if (!new_stash || *new_stash == '\0')
	{
		free(new_stash);
		return (free_stash(stash), line);
	}
	free(*stash);
	*stash = new_stash;
	return (line);
}

static void	fill_stash(int fd, char **stash, char *buffer)
{
	int		bytes_read;

	if (!*stash)
		*stash = ft_strdup("");
	if (!*stash)
		return ;
	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_strjoin_free_stash(stash, buffer);
		if (!*stash)
			return ;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_stash(&stash));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_stash(&stash));
	fill_stash(fd, &stash, buffer);
	free(buffer);
	if (!stash || *stash == '\0')
		return (free_stash(&stash));
	next_line = extract_and_trim(&stash);
	if (!next_line)
		return (free_stash(&stash));
	return (next_line);
}

/* 
#include <stdio.h>
int	main(void)
{
	char *test_stash = ft_strdup("Hello\n42\nWorld");
	//char *str = " of Warcraft";
	//printf("%s World", extract_line(test_stash));

	test_stash = trim_stash(test_stash);
	
	//test_stash = ft_strjoin_free_stash(test_stash, str);
	printf("%s", test_stash);
	free(test_stash);
}
*/
/* 
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	char *line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
    	printf("Line: %s", line);
    	free(line);	
	}
	
	close(fd);
	return (0);
} */
