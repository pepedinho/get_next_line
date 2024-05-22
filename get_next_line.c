/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:25:49 by itahri            #+#    #+#             */
/*   Updated: 2024/04/01 08:05:46 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*Verifie si stash contien un '\n'*/
int	check_stash(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] && stash)
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
	retourne la chaine stash couper au premier '\n' 
	et stock le reste de stash au debut de stash
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
	while (i < len)
		stash[j++] = stash[i++];
	i = j;
	while (stash[i] != '\n' && stash[i])
	{
		stash[i] = '\0';
		i++;
	}
	if (stash[i])
		stash[i] = '\0';
	return (result);
}

char	*give_me_this_line(char *stash, int cases)
{
	char	*line;

	if (cases == 1)
	{
		line = format_stash(stash);
		if (!line)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		return (line);
	}
	else
	{
		line = format_stash(stash);
		if (!line || !line[0])
		{
			free(line);
			return (NULL);
		}
		return (line);
	}
}

char	*monitoring(char **stash, int nb_read)
{
	char	*final_result;

	if (check_stash(*stash))
	{
		final_result = give_me_this_line(*stash, 1);
		if (!final_result)
			return ((void *)-1);
		return (final_result);
	}
	else if (nb_read < BUFFER_SIZE && check_stash(*stash))
	{
		final_result = give_me_this_line(*stash, 1);
		return (final_result);
	}
	else if (nb_read < BUFFER_SIZE && !check_stash(*stash))
	{
		final_result = give_me_this_line(*stash, 2);
		free(*stash);
		*stash = NULL;
		return (final_result);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*result;
	char			*final_result;
	char			*buff;
	int				nb_read;

	if (fd < 0)
		return (NULL);
	nb_read = -1;
	while (nb_read != 0)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
		{
			if (result)
			{
				free(result);
			}
			return (NULL);
		}
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read == -1 || (nb_read == 0 && !result))
			return (free(buff), free(result), NULL);
		result = ft_strjoin(result, buff);
		if (!result)
			return (NULL);
		final_result = monitoring(&result, nb_read);
		if (final_result == (void *)-1)
			return (NULL);
		else if (final_result != NULL)
			return (final_result);
	}
	return (NULL);
}

/*
#include <fcntl.h>
int main()
{
	int fd;
	char *line;

	fd= open("testmouss", O_RDONLY);
	int i= 0;
	while(i < 4)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}

}
*/
/*
#include <fcntl.h>
int    main(void)
{
    int fd;
    char *line;

    // Ouvrir le fichier en lecture
    fd = open("files/alternate_line_nl_with_nl", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Lire et afficher chaque ligne du fichier
    line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line); // Libérer la mémoire allouée par get_next_line
    line = get_next_line(fd);
	if (!line)	
		return 0;
    printf("[%s] \n", line);
    free(line); // Libérer la mémoire allouée par get_next_line
    line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line); // Libérer la mémoire allouée par get_next_line
    line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line); // Libérer la mémoire allouée par get_next_line
	line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line); // Libérer la mémoire allouée par get_next_line
	line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line); // Libérer la mémoire allouée par get_next_line
	line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line);
	line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line);
	line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line);
	line = get_next_line(fd);
	if (!line)
		return 0;
    printf("[%s] \n", line);
    free(line);
    close(fd);

    return (0);
}
*/
