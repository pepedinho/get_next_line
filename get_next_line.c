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
	while (stash && stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
	retourne la chaine stash couper au premier '\n' 
	et replace le reste de stash au debut de cette derniere
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

/*
	fonction d'appel de formatage toujours selon le cas
	cas 1 = appeler format_stash et free la stash en cas d'echecs.
	cas 2 = appeler format_stash et free line si il s'agit d'une chaine vide
				ce qui signifie que la stash etait vide;
				(je ne free pas la stash car je la free dans la fonction precedente)
*/

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
		if (!line[0])
		{
			free(line);
			return (NULL);
		}
		return (line);
	}
}

/*
 fonction de monitoring verification de l'etat de la stash 
 cas 1 = BUFFER_SIZE caractere a ete lus et un \n dans la stash 
			|
			-->envoyer la stash a la fonction de formatage.

 cas 2 = nombre de caracter lus < BUFFER_SIZE donc fin du fichier
			|
			--> envoyer la stash a la fonction de formatage.
					|
					--> free la stash.
*/

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
	else if (nb_read < BUFFER_SIZE && !check_stash(*stash))
	{
		final_result = give_me_this_line(*stash, 2);
		free(*stash);
		*stash = NULL;
		return (final_result);
	}
	return (NULL);
}

/*
 fonction principal lecture du fichier allocation du buffer 
 et realocation de la stash (result) via strjoin modifier
*/

char	*get_next_line(int fd)
{
	static char		*result;
	char			*final_result;
	char			*buff;
	int				nb_read;

	nb_read = -1;
	while (nb_read != 0 && fd >= 0)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
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

	fd= open("read_error.txt", O_RDONLY);
	int i= 0;
	while(i < 5)
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
