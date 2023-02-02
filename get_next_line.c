/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:51:45 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/02 20:44:13 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save_add(char *save, char *buf)
{

}

char	*ft_line_add(char *line, char *buf)
{

}

char	*ft_save_new(char *buf)
{

}

char	*ft_line_new(char *buf)
{

}

/*
 * ファイルを読み一行ずつ戻り値に格納する
 */
char	*get_next_line(int fd)
{
	static t_file	file;
	int				bytes;

	file.buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (file.buf == NULL)
		return (NULL);
	file.line = NULL;
	while (1)
	{
		bytes = read(fd, &file.buf, BUFFER_SIZE);
		file.buf[bytes] = '\0';
		if (file.line == NULL)
		{
			file.line = ft_line_new(file.buf);
			file.save = ft_save_new(file.buf);
		}
		else
		{
			file.line = ft_line_add(file.line, file.buf);
			file.save = ft_save_add(file.save, file.buf);
		}
		if (bytes <= 0)
			return (file.line);
	}
}

#include <fcntl.h>
int	main(int argc, char **argv)
{
	char		*map_file_str;

	map_file_str = get_next_line(open("test.txt", O_RDONLY));
	// map_file_str = ft_file_put_in_str("ft_make.txt");
	printf("%s", map_file_str);
	return (0);
}
