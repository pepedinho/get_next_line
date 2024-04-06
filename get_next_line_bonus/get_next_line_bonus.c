/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-03-31 18:08:51 by itahri            #+#    #+#             */
/*   Updated: 2024-03-31 18:08:51 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_file	*give_me_element(t_file	*stash, int fd)
{
	t_file	*current;
	t_file	*first;

	current = stash;

	if (!current)
	{
		current = ft_lstnew(fd);
		if (!current)
			return (NULL);
		current->first = current;
		return (current);
	}
	else
	{
		first = current->first;
		while(first)
		{
			if (first->fd == fd)
				return first;// L'element existe
			first = first->next;
		}
		//L'element n'existe pas
			//creationd'un nouvel element asocier au fd recus en parametre 
		first = ft_lstnew(fd);
		first->first = current->first;
		if (!first)
			return(NULL);
		ft_lstadd_back(&current, first);
		return(ft_lstlast(current));
	}
	return(NULL);
}

int		check_stash(char *stash)
{
	int	i;
	
	if (!stash)
		return (0);
	i = 0;
	while(stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return 0;
}

char	*format_stash(char	*stash, int cas)
{
	int		i;
	int		j;
	char	*result;

	(void)cas;
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i])
		i++;
	result =ft_strndup(stash, i);
	if (!result)
		return (NULL);
	
	j = 0; //i + 1 = caractere juste apre le '\n'
	if (!stash[i] && i > 0)
		stash[j] = '\0';
	else
	{
		while (stash[i])
		{
			stash[j++] = stash[i]; //fait passer les caracteres restant au debut de la chaine de caracatere
			i++;
		}
		while (stash[j++])
			stash[j] = '\0';
	}
	return (result);
}

char	*give_me_the_line(t_file *file_infos)
{
	int		nb_read;
	char	*buff;
	char	*line;

	nb_read = -1;
	while (nb_read != 0)	
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		nb_read = read(file_infos->fd, buff, BUFFER_SIZE);
		if (nb_read == 0 && !check_stash(file_infos->stash))
			return (NULL);
		file_infos->stash = ft_strjoin(file_infos->stash, buff);
		if (nb_read < BUFFER_SIZE && check_stash(file_infos->stash))
		{
			line = format_stash(file_infos->stash, 1);
			if (!line)
				return (NULL);
			break ;
		}
		else if (nb_read < BUFFER_SIZE && !check_stash(file_infos->stash))
		{
			line = format_stash(file_infos->stash, 1);
			if (!line)
				return (NULL);
			break ;
		}
		else if (check_stash(file_infos->stash))
		{
			line = format_stash(file_infos->stash, 1);
			if (!line)
				return (NULL);
			break ;
		}
	}
	return (line);	
}

char	*get_next_line(int fd)
{
	static t_file	*file_infos;
	char			*line;
		
	file_infos = give_me_element(file_infos, fd);
	line = give_me_the_line(file_infos);
	if (!line)
		return (NULL);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd1;
	int fd2;
	int fd3;
	int i;
	char	*line;

	fd1 = open("tests/file1.txt", O_RDONLY);
	fd2 = open("tests/file2.txt", O_RDONLY);
	fd3 = open("tests/file3.txt", O_RDONLY);

	i = 0;
	while (i < 3)
	{
		if ((line = get_next_line(fd1)) != NULL)
			printf("[FILE 1]%s \n", line);
		if (line)
			free(line);
		if ((line = get_next_line(fd1)) != NULL)
			printf("[FILE 1]%s \n", line);
		if (line)
			free(line);
		if ((line = get_next_line(fd2)) != NULL)
			printf("[FILE 2]%s \n", line);
		if (line)
			free(line);
		if ((line = get_next_line(fd3)) != NULL)
			printf("[FILE 3]%s \n", line);
		if (line)
			free(line);
		i++;
	}
}