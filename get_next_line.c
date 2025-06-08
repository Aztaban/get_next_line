/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/08 20:31:05 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin_free_stash(char *stash, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (stash == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(stash);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, stash, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(stash);
	return (result);
}

static char	*trim_stash(char *stash)
{
	size_t	len;
	char	*new_stash;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (!stash[len])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + len + 1);
	free(stash);
	return (new_stash);
}

static char	*extract_line(char *stash)
{
	size_t	len;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	return (ft_substr(stash, 0, len + 1));
}

static char	*fill_stash(int fd, char *stash)
{
	char	*buffer;
	char	*tmp_stash;
	int		bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp_stash = ft_strjoin_free_stash(stash, buffer);
		if (!tmp_stash)
		{
			free(buffer);
			return (NULL);
		}
		stash = tmp_stash;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*next_line;

	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = fill_stash(fd, stash);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	next_line = extract_line(stash);
	stash = trim_stash(stash);
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