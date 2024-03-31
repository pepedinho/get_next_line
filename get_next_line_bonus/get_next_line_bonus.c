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

/*Verifie si stash contien un '\n'*/
static int	check_stash(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	if (i > 1)
		return (1);
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

static char	*give_me_this_line(char *stash, char *buff, int cases)
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
		if (!line)
			return (NULL);
		if (buff)
			free(buff);
		free(stash);
		return (line);
	}
}

static char	*monitoring(t_file *stash, char *buff, int nb_read)
{
	char	*final_result;

	if (check_stash(stash->stash))
	{
		final_result = give_me_this_line(stash->stash, buff, 1);
		if (!final_result)
			return (NULL);
		return (final_result);
	}
	else if (nb_read < BUFFER_SIZE && check_stash(stash->stash))
	{
		final_result = give_me_this_line(stash->stash, buff, 1);
		if (final_result)
			return (NULL);
		return (final_result);
	}
	else if (nb_read < BUFFER_SIZE && !check_stash(stash->stash))
	{
		final_result = give_me_this_line(stash->stash, buff, 2);
		if (!final_result)
			return (NULL);
		return (final_result);
	}
	return (NULL);
}

t_file		*check_in_list(t_file **lst, int fd)
{
	t_file	*current;

	current = *lst;
	while(current)
	{
		if(current->fd == fd)
			return(current);
		current = current->next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static	t_file	*file_lst;
	int				nb_read;
	char			*buff;
	char			*final_result;

	if (check_in_list(&file_lst, fd))
		file_lst = check_in_list(&file_lst, fd);
	else
		file_lst = ft_lstnew(fd);
	nb_read = -1;
	while (nb_read != 0)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		nb_read = read(file_lst->fd, buff, BUFFER_SIZE);
		if (nb_read == 0 && !check_stash(file_lst->stash))
		{
			free(buff);
			ft_lstclear(&file_lst, free);
		}
		file_lst->stash = ft_strjoin(file_lst->stash, buff);
		if (!file_lst->stash)
			return (NULL);
		final_result = monitoring(file_lst, buff, nb_read);
		if (final_result != NULL)
			return (final_result);
	}
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>


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
		free(line);
		if ((line = get_next_line(fd2)) != NULL)
			printf("[FILE 2]%s \n", line);
		free(line);
		if ((line = get_next_line(fd3)) != NULL)
			printf("[FILE 3]%s \n", line);
		free(line);
		i++;
	}
}