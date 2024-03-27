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

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 20
#include <stdlib.h>
#include <unistd.h>

# define COUNT count.prec ? count.prec : count.now


typedef struct s_line
{
	int	prec;
	int	now;
}		t_line;


#endif