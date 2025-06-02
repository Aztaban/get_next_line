/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:15 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/02 23:30:30 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

// helpers
size_t	ft_strlen(const char *s);   // always helpful for allocating memory (i hope)
char	*ft_strchr(const char *s, int c); // find a new line in string
char	*ft_substr(const char *s, unsigned int start, size_t len); // to extract the return string from stash. 
char	*ft_strdup(const char *s); // copy the rest of the string as new stack and maybe free the old one???

#endif