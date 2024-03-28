/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-03-28 01:33:36 by itahri            #+#    #+#             */
/*   Updated: 2024-03-28 01:33:36 by itahri           ###   ########.fr       */
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
	return(result);
}

/*Ajoute s2 a la suite de s1 et assigne la chaine concaténer a s1*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = malloc(sizeof(char) * (ft_strlen(s1) + (BUFFER_SIZE +1)));
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
	while (j < BUFFER_SIZE && s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	
	free((char *)s1);
	//s1 = result;
	return (result);
}