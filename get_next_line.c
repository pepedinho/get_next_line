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
	while(i < len)
	{
		stash[j] = stash[i];
		i++;
		j++;
	}
	i = j;
	while(stash[i] != '\n' && stash[i])
	{
		stash[i] = '\0';
		i++;
	}
	if (stash[i])
		stash[i] = '\0';
	
	return (result);
}

char	*give_me_this_line(char *stash, char *buff, int cases)
{
	char 	*line;
	if (cases ==  1)
	{
		line = format_stash(stash);
		if (!line)
		{
			free(stash);
			return (NULL);
		}
		return (line);
	}
	else
	{
		line = format_stash(stash);
		if (!line)
			return (NULL);
		if (buff)
			free(buff);
		free(stash);
		return (line);
	}
}

char	*get_next_line(int fd)
{
	static char		*result;
	char			*final_result;
	char			*buff;
	int				nb_read;

	nb_read = -1;
	while (nb_read != 0)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read == 0 && !check_stash(result))
		{
			free(buff);
			break ;
		}
		result = ft_strjoin(result, buff);
		if (!result)
		{
			free(buff);
			free(result);
			return (NULL);
		}
		if (check_stash(result))
		{
			final_result = give_me_this_line(result, buff, 1);
			if (!final_result)
				return (NULL);
			return (final_result);
		}
		else if (nb_read < BUFFER_SIZE && check_stash(result))
		{
			final_result = give_me_this_line(result, buff, 1);
			if (final_result)
				return (NULL);
			return (final_result);
		}
		else if (nb_read < BUFFER_SIZE && !check_stash(result))
		{
			final_result = give_me_this_line(result, buff, 2);
			if (!final_result)
				return (NULL);
			return (final_result);
		}
	}
	return (NULL);
}

#include <fcntl.h>
int main ()
{
	int i = 0;
	int	fd;
	char *line;

	fd = open("tests/test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!line)
		{
			free(line);
			break ; 
		}
		else
		{
			printf("%s", line);
			free(line);
		}
		i++;
	}
	close(fd);
}
