/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:22:58 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/14 18:33:28 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
 * s文字列の中で、startから最大len分文字を抽出し、戻り値として返す。
 "abcdefghijklmn",3,20    defg
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*return_str;
	size_t	malloc_size;
	size_t	i;

	if (ft_strlen(s) <= len)
		malloc_size = ft_strlen(s) - (size_t)start;
	else
		malloc_size = len;
	return_str = (char *)malloc(sizeof(char) * (malloc_size + 1));
	if (return_str == NULL)
		return (NULL);
	i = 0;
	while (i < malloc_size)
	{
		return_str[i] = s[start + i];
		i++;
	}
	return_str[i] = '\0';
	return (return_str);
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

char	*get_next_line(int fd)
{
	int			bytes;
	static char	buf[BUFFER_SIZE + 1];
	// static char	buf[(size_t)BUFFER_SIZE + 1];

	//bufに値があった場合、以下を処理
	//bufに改行があれば、lineに改行までを入れて出力、bufの改行後を先頭に移動させる
	// return
	//bufに改行が無ければ、lineにbufの全てを入れ、readする
	//read
	



}

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int	main(void)
{
	int		fd;
	char	*map_file_str;

	// fd = open("unit-test1/files/nl", O_RDONLY);
	// fd = open("unit-test1/files/empty", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	// fd = 0;
	while (1)
	{
		map_file_str = get_next_line(fd);
		if (map_file_str == NULL)
			break ;
		// printf("len: %lu", strlen(map_file_str));
		printf("> %s", map_file_str);
		free(map_file_str);
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