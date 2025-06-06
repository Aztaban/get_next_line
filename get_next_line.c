/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/06 17:20:18 by mjusta           ###   ########.fr       */
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

static char	*extract_line(char *stash)
{
		size_t	len;

		len = 0;
		while (stash[len] && stash[len] != '\n')
			len++;
		return (ft_substr(stash, 0, len + 1));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes_read;
	char 		*next_line;

	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
	// allocate memory and create buffer.
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	// if the string in stash doesnt contain new line load buffer again and add buffer to stash.
	// repeat until the stash contains atleast one new line.
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		// read the fd and store value into buffer.
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_free_stash(stash, buffer); //free the previous stash before returning new one
	}
	// after that free the buffer.
	free(buffer); 
	// if the buffer return empty return NULL and return the last value.(without new line)
	// extract line from the stash and return it.
	next_line = extract_line(stash);
	// before returning the last line free the stash from memory.
	return (next_line);
}

/*
#include <stdio.h>
int	main(void)
{
	char *test_stash = ft_strdup("Hello\n42\nWorld");
	char *str = " of Warcraft";
	//printf("%s World", extract_line(test_stash));

	test_stash = ft_strjoin_free_stash(test_stash, str);
	printf("%s", test_stash);
	free(test_stash);
}
*/