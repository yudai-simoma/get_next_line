/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:51:45 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/08 20:09:13 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

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
 * 各文字列を条件に分けて新たな文字列へ格納した値を返す
 * x = 0 の時は、line_new(lineに新規に追加する)
 * x = 1 の時は、save_new(saveに新規に追加する)
 * x = 2 の時は、line_add(lineに元の文字列と新しい文字列を結合する)
 */
char	*ft_add_str(const char *s1, const char *s2, int x)
{
	char	*return_str;
	size_t	i;

	if (x == 1)
		s1 = ft_strchr(s1, '\n');
	if (x == 1 || x == 0)
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
 * ファイルを読み一行ずつ戻り値に格納する
 */
char	*get_next_line(int fd)
{
	static t_file	file;
	int				bytes;

	if(file.line != NULL)
	{
		free(file.line);
		file.line = NULL;
	}
	//saveに入っていたら、lineに入れる
	if (file.save != NULL)
	{
		//saveの中に改行があれば、lineに入れて出力
		if (ft_strchr(file.save, '\n') != NULL)
		{
			file.line = ft_add_str(file.save, NULL, 0);
			if (file.line == NULL)
				return (NULL);
			file.backup = file.save;
			free(file.save);
			file.save = NULL;
			file.save = ft_add_str(file.backup, NULL, 1);
			if (file.save == NULL)
				return (NULL);
			return (file.line);
		}
		//saveの中に改行がなければ、lineに格納
		else
		{
			file.line = ft_add_str(file.save, NULL, 0);
			if (file.line == NULL)
				return (NULL);
		}
	}
	while (1)
	{
		bytes = read(fd, &file.buf, BUFFER_SIZE);
		if (bytes == 0)
		{
			free(file.save);
			file.save = NULL;
			free(file.backup);
			file.backup = NULL;
			return (file.line);
		}
		file.buf[bytes] = '\0';
		// bufに改行があるかどうか
		if (ft_strchr(file.buf, '\n') != NULL)
		{
			//改行があれば、save(new)に改行後を入れ、lineに改行前を入れ、returnでlineを返す
			free(file.save);
			file.save = NULL;
			file.save = ft_add_str(file.buf, NULL, 1);
			if (file.save == NULL)
				return (NULL);
			if (file.line == NULL)
			{
				file.line = ft_add_str(file.buf, NULL, 0);
				if (file.line == NULL)
					return (NULL);
			}
			else
			{
				file.line = ft_add_str(file.line, file.buf, 2);
				if (file.line == NULL)
					return (NULL);
			}
			return (file.line);
		}
		else
		{
			//改行がなければ、lineにbufを入れる(新規や追加)
			if (file.line == NULL)
			{
				file.line = ft_add_str(file.buf, NULL, 0);
				if (file.line == NULL)
					return (NULL);
			}
			else
			{
				file.line = ft_add_str(file.line, file.buf, 2);
				if (file.line == NULL)
					return (NULL);
			}
		}
	}
}

int	main(void)
{
	int		fd;
	char	*map_file_str;

	// fd = open("test.txt", O_RDONLY);
	// while (1)
	// {
	// 	map_file_str = get_next_line(fd);
	// 	if (map_file_str == NULL)
	// 		break ;
	// 	printf("%s", map_file_str);
	// }

	fd = open("test.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));

	printf("\n----------------------------------------");
	printf("\n1%s",get_next_line(fd));
	printf("\n2%s",get_next_line(fd));
	printf("\n3%s",get_next_line(fd));
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	char		*map_file_str;

// 	map_file_str = get_next_line(open("test.txt", O_RDONLY));
// 	// map_file_str = ft_file_put_in_str("ft_make.txt");
// 	printf("%s", map_file_str);
// 	return (0);
// }
