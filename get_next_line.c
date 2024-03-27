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

int	ft_strlen(const char *str)
{
	int	i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*Duplique la chaine source dans une nouvelle chaine jusqu'au caractère n*/
char	*ft_strndup(const char *source, int n)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * n + 1);
	if (!result)
		return (NULL);
	while (i < n && source[i])
	{
		result[i] = source[i];
		i++;
	}
	result[i] = '\0';
	return(result);
}

/*Ajoute s2 a la suite de s1 et assigne la chaine concaténer a s1*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	s1 = result;
	return (result);
}

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
	i++;
	stash[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char			*result;
	char			buff[BUFFER_SIZE];
	int				nb_read;
	// if (result)
	// 	printf("open function result : %s \n", result);

	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, BUFFER_SIZE);
		result = ft_strjoin(result, buff);
		// printf("strjoin : %s \n", result);
		if (!result)
			return (NULL);
		if (nb_read < BUFFER_SIZE)
			return (format_stash(result));
		if (check_stash(result))
			return (format_stash(result));
	}
	free(result);
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
		char *line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		i++;
	}
	close(fd);
}
