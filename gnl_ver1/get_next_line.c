/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:51:45 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/14 12:07:23 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


/*
 * 各文字列を条件に分けて新たな文字列へ格納した値を返す
 * x = 0 の時は、line_new(lineにbufの改行までを新規に追加する)
 * x = 1 の時は、save_new(saveにbufの改行後を新規に追加する)
 * x = 2 の時は、line_add(lineに元の文字列とbufの改行までを結合する)
 * x = 3 の時は、line_new(lineに全てのbufを新規に追加する)
 */
char	*ft_add_str(const char *s1, const char *s2, int x)
{
	char	*return_str;
	size_t	i;

	if (x == 1)
		s1 = ft_strchr(s1, '\n');
	if (x == 1 || x == 0 || x == 3 || s1 + 1 != '\0')
	{
		return_str = ft_strdup(s1 + x);
		if (return_str == NULL)
			return (NULL);
	}
	if (x == 0)
	{
		i = 0;
		while (return_str[i] != '\n' && return_str[i] != '\0')
			i++;
		return_str[i + 1] = '\0';
	}
	if (x == 2)
	{
		return_str = ft_strjoin(s1, ft_add_str(s2, NULL, 0));
		if (return_str == NULL)
			return (NULL);
	}
	return (return_str);
}

/*
** 文字列の先頭から「文字」を検索して見つかった場所をポインタで返します。
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

/*
** 与えられた文字列の桁数を返す
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
** 文字列srcを複製し、新しい文字列へのポインターを返す
*/
char	*ft_strdup(const char *src)
{
	char	*src_mal;
	int		i;

	src_mal = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (src_mal == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		src_mal[i] = src[i];
		i++;
	}
	src_mal[i] = '\0';
	return (src_mal);
}

/*
 * s1とs2の文字列を結合し、戻り値として返す
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*return_src;
	size_t	malloc_size;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return ((char *)s2);
	if (s1 != NULL && s2 == NULL)
		return ((char *)s1);
	malloc_size = ft_strlen(s1) + ft_strlen(s2);
	return_src = (char *)malloc(sizeof(char) * (malloc_size + 1));
	if (return_src == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
		return_src[i++] = *s1++;
	while (*s2 != '\0')
		return_src[i++] = *s2++;
	return_src[i] = '\0';
	return (return_src);
}

/*
 * save に値が入っていたら呼ばれる
 * saveの中に改行があれば、lineに入れて出力
 * saveの中に改行がなければ、lineに格納
 */
int	ft_save_add_line(t_file *file)
{
	if (ft_strchr(file->save, '\n') != NULL)
	{
		file->backup = file->save;
		file->line = ft_add_str(file->save, NULL, 0);
		if (file->line == NULL)
			return (1);
		file->save = ft_add_str(file->backup, NULL, 1);
		if (file->save == NULL)
			return (1);
		return (1);
	}
	else
	{
		file->line = ft_add_str(file->save, NULL, 3);
		if (file->line == NULL)
			return (1);
	}
	return (0);
}

/*
 * 無限ループの中でbufに改行があれば呼ばれる
 * saveに改行後を入れ、lineに改行までを入れ、returnでlineを返す
 */
int	ft_buf_add_save_line(t_file *file)
{
	if (file->save != NULL)
	{
		file->save = NULL;
	}
	file->save = ft_add_str(file->buf, NULL, 1);
	if (file->save == NULL)
		return (1);
	if (file->line == NULL)
	{
		file->line = ft_add_str(file->buf, NULL, 0);
		if (file->line == NULL)
			return (1);
	}
	else
	{
		file->line = ft_add_str(file->line, file->buf, 2);
		if (file->line == NULL)
			return (1);
	}
	return (1);
}

/*
 * 無限ループの中でbufに改行がなければ呼ばれる
 * lineに全てのbufを入れる
 */
int	ft_buf_add_line(t_file *file)
{
	if (file->line == NULL)
	{
		file->line = ft_add_str(file->buf, NULL, 3);
		if (file->line == NULL)
			return (1);
	}
	else
	{
		file->line = ft_add_str(file->line, file->buf, 2);
		if (file->line == NULL)
			return (1);
	}
	return (0);
}

/*
 * 無限ループの中で呼ばれる
 */
int	ft_while_loop(int fd, int bytes, t_file *file)
{
	bytes = read(fd, &file->buf, BUFFER_SIZE);
	if (bytes == 0)
	{
		if (file->save != NULL)
		{
			file->save = NULL;
		}
		// if (file->line[0] == '\0')
			// file->line = NULL;
		return (1);
	}
	if (bytes < 0)
	{
		if (file->save != NULL)
		{
			file->save = NULL;
		}
		return (1);
	}
	file->buf[bytes] = '\0';
	if ((ft_strchr(file->buf, '\n') != NULL && ft_buf_add_save_line(file))
		|| (ft_strchr(file->buf, '\n') == NULL && ft_buf_add_line(file)))
		return (1);
	return (0);
}

/*
 * ファイルを読み一行ずつ戻り値に格納する
 */
char	*get_next_line(int fd)
{
	static t_file	file;
	int				bytes;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (file.line != NULL)
	{
		free(file.line);
		file.line = NULL;
	}
	if (file.save != NULL)
		if (ft_save_add_line(&file))
			return (file.line);
	bytes = 0;
	while (1)
	{
		if (ft_while_loop(fd, bytes, &file))
			return (file.line);
	}
}

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int	main(void)
{
	int		fd;
	char	*map_file_str;

	fd = open("unit-test1/files/nl", O_RDONLY);
	// fd = open("unit-test1/files/empty", O_RDONLY);
	// fd = open("test2.txt", O_RDONLY);
	// fd = 0;
	while (1)
	{
		map_file_str = get_next_line(fd);
		if (map_file_str == NULL)
			break ;
		// printf("len: %lu", strlen(map_file_str));
		printf("> %s", map_file_str);
	}
	return (0);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*map_file_str;

// 	fd = open(argv[1], O_RDONLY);
// 	while (1)
// 	{
// 		map_file_str = get_next_line(fd);
// 		if (map_file_str == NULL)
// 			break ;
// 		printf("%s", map_file_str);
// 	}
// 	return (0);
// }
