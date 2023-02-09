/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:33:37 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/09 20:29:48 by yshimoma         ###   ########.fr       */
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

char	*get_next_line(int fd);
int		ft_whil_loop(int fd, int bytes, t_file *file);
int		ft_buf_add_line(t_file *file);
int		ft_buf_add_save_line(t_file *file);
int		ft_save_add_line(t_file *file);
char	*ft_add_str(const char *s1, const char *s2, int x);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);

#endif