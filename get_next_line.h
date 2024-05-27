/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:29:14 by itahri            #+#    #+#             */
/*   Updated: 2024/03/27 18:22:13 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct s_index
{
	size_t	i;
	size_t	j;
}		t_index;

int		ft_strlen(const char *str);
char	*ft_strndup(const char *source, int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmeb, size_t size);
void	free_this(char *result, char *buff);
char	*get_next_line(int fd);

#endif
