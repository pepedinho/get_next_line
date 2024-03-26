/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:25:49 by itahri            #+#    #+#             */
/*   Updated: 2024/03/26 15:33:34 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"




char	*get_next_line(int fd)
{
	char	*result;
	char	buff[1];
	int		nb_read;
	int		count;

	nb_read = -1;
	count = 0;
	
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, 1);
		if (buff[0] == '\n' || buff[0] == '\0')
		{
			result = malloc(sizeof(char) * count + 1);
			if (!result)
				return (NULL);
			nb_read = read(fd, result, count);
			return (result);
		}
		count++;
	}
	return (NULL);
}

#include <fcntl.h>
#include <stdio.h>
int main ()
{
	int i = 0;
	int	fd;

	fd = open("tests/test.txt", O_RDONLY);
	while (i < 3)
	{
		printf("%s \n", get_next_line(fd));
		i++;
	}
	close(fd);
}