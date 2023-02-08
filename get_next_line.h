/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:33:37 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/07 19:21:52 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 42

typedef struct s_file
{
	char	buf[BUFFER_SIZE + 1];
	char	*save;
	char	*line;
	char	*backup;
}	t_file;

typedef struct s_count
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
}	t_count;

#endif