/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-03-31 18:03:50 by itahri            #+#    #+#             */
/*   Updated: 2024-03-31 18:03:50 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_file
{
	int		fd;
	char	*stash;
	struct s_file	*next;
}			t_file;

typedef struct s_index
{
	size_t	i;
	size_t	j;
}		t_index;

int		ft_strlen(const char *str);
char	*ft_strndup(const char *source, int n);
char	*ft_strjoin(char const *s1, char const *s2);
t_file	*ft_lstnew(int fd);
void	*ft_calloc(size_t nmeb, size_t size);
void	ft_lstclear(t_file **lst, void (*del)(void *));

#endif
