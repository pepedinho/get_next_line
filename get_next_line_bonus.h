/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-06 11:23:25 by itahri            #+#    #+#             */
/*   Updated: 2024-05-06 11:23:25 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
//# define BUFFER_SIZE 10000000
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