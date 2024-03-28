/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:25:49 by itahri            #+#    #+#             */
/*   Updated: 2024/03/27 19:03:30 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>



/*Verifie si stash contien un '\n'*/
int	check_stash(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}


/*
	retourne la chaine stash couper au premier '\n' stock le reste de stash au debut de stash
*/
char	*format_stash(char *stash)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	i++;
	result = ft_strndup(stash, i);
	if (!result)
		return (NULL);
	
	len = ft_strlen(stash);
	// printf("len > %d | i > %d\n", len, i);
	while(i < len)
	{
		stash[j] = stash[i];
		// printf("debug  : [%c]\n", stash[i]);
		i++;
		j++;
	}
	i = j;
	while(stash[i] != '\n' && stash[i])
	{
		stash[i] = '\0';
		i++;
	}
	//i++;
	if (stash[i])
		stash[i] = '\0';
	
	return (result);
}

char	*get_next_line(int fd)
{
	static char			*result;
	char				*final_result;
	char			buff[BUFFER_SIZE];
	int				nb_read;

	// if (!result)
	// 	result = ft_strnew();
	// 	printf("open function result : %s \n", result);
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read == (0))
				break ;
		result = ft_strjoin(result, buff);
		if (!result)
		{
			free(result);
			printf("HOLALALAALLALAALALALALA\n");
			return (NULL);
		}
		// printf("strjoin : %s \n", result);
		//printf("nb_read = %d | buffer_size = %d \n", nb_read, BUFFER_SIZE);
		if (nb_read < BUFFER_SIZE)
		{
			final_result = format_stash(result);
			free(result);
			if(!final_result)
				return (NULL);
			return (final_result);
		}
		if (check_stash(result))
			return (format_stash(result));
	}
	if (nb_read != 0)
		free(result);
	return (NULL);
}

#include <fcntl.h>
int main ()
{
	int i = 0;
	int	fd;

	fd = open("tests/test.txt", O_RDONLY);
	while (i < 30)
	{
		char *line = get_next_line(fd);
		if (!line)
		{
			//printf("[line %d]\n", i + 1);
			free(line);
			break ; 
		}
		else if (line)
		{
			//printf("[line %d]\n", i + 1);
			printf("%s", line);
			free(line);
		}
		i++;
	}
	close(fd);
}
