/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:41:24 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/02 23:19:00 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	// create stash
	// allocate memory and create buffer.
	// read the fd and store value into buffer. 
	// store the buffer value in static variable stash. (allocate memory for stash?)
	// if the string in stash doesnt contain new line load buffer again and add buffer to stash.
	// repeat until the stash contains atleast one new line. 
	// after that free the buffer. 
	// if the buffer return empty return NULL and return the last value.(without new line)
	// extract line from the stash and return it.
	// before returning the last line free the stash from memory.
}