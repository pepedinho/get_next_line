/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-06 11:23:34 by itahri            #+#    #+#             */
/*   Updated: 2024-05-06 11:23:34 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	return (result);
}

/*Ajoute s2 a la suite de s1 et assigne la chaine concaténer a s1*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	t_index	index;

	result = malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2) +1)));
	if (!result)
	{
		free((char *)s2);
		return (NULL);
	}
	index.i = 0;
	index.j = 0;
	if (s1)
	{
		while (s1[index.i])
		{
			result[index.i] = s1[index.i];
			index.i++;
		}
	}
	while (index.j < BUFFER_SIZE && s2[index.j])
		result[index.i++] = s2[index.j++];
	result[index.i] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (result);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(size * nmeb);
	if (ptr == NULL)
		return (NULL);
	if (nmeb == 0 || size == 0)
		return (NULL);
	i = 0;
	while (i < nmeb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}

void	free_this(char *result, char *buff)
{
	if (result)
	{
		free(result);
		result = NULL;
	}
	else
	{
		free(buff);
		buff = NULL;
	}
}
