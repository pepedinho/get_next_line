/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:25:49 by itahri            #+#    #+#             */
/*   Updated: 2024/03/26 19:11:49 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include <stdio.h>

int	ft_strlen(const char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *source)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * ft_strlen(source) + 1);
	if (!result)
		return (NULL);
	while (source[i])
	{
		result[i] = source[i];
		i++;
	}
	free((char *)source);
	return(result);
}

char	*get_next_line(int fd)
{
	char	*result;
	char	buff[1];
	int		nb_read;
	static t_line count;
	static int	pass;

	pass = 1;
	count.now = COUNT;
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, 1);
		if ((buff[0] == '\n' || buff[0] == '\0') && pass == 1)
		{
			result = malloc(sizeof(char) * (count.now - count.prec) + 1);
			if (!result)
				return (NULL);
			// printf("count.now = (%d) | count.prec = (%d)\n", count.now, count.prec);
			nb_read = read(fd, result, (count.now - count.prec) - 2);
			// printf("[ taille de la ligne / alloué: %d ]\n\n", count.now - count.prec);
			count.prec = count.now;
			// printf("laste caracter result : %c\n",result[count.now - count.prec] + 1);
			pass = 0;
			return (ft_strdup(result));
		}
		pass = 1;
		count.now++;
	}
	return (NULL);
}

#include <fcntl.h>
int main ()
{
	int i = 0;
	int	fd;

	fd = open("tests/test.txt", O_RDONLY);
	while (i < 5)
	{
		printf("%s \n", get_next_line(fd));
		i++;
	}
	close(fd);
}
