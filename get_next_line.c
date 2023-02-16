/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:22:58 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/16 19:51:58 by yshimoma         ###   ########.fr       */
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
 * return_strにbufの改行までを入れて返す
 * return_strに値があれば、joinで結合し、改行後を'\0'埋めする
 * return_strに値が無ければ、dupでbufと同じ文字列を作成し改行後を'\0'埋めする
 */
static char	*ft_add_str(char *buf, char *return_str, size_t l_num)
{
	char	*cp_str;

	if (return_str != NULL)
	{
		cp_str = return_str;
		return_str = ft_strjoin(return_str, buf);
		if (return_str == NULL)
			return (NULL);
		return_str[ft_strlen(cp_str) + l_num] = '\0';
		free(cp_str);
	}
	else
	{
		return_str = ft_strdup(buf);
		if (return_str == NULL)
			return (NULL);
		return_str[l_num] = '\0';
	}
	return (return_str);
}

/*
 * bufに改行があれば呼ばれる
 * return_strにbufの改行までを入れて、返す(ft_add_strで処理をする)
 * bufの改行後を先頭に移動させる
 */
static char	*ft_buf_in_line(char *buf, char *return_str)
{
	size_t	i;
	size_t	buf_size;

	i = 0;
	buf_size = ft_strlen(buf);
	while (buf[i] != '\n')
		i++;
	i++;
	return_str = ft_add_str(buf, return_str, i);
	if (return_str == NULL)
		return (NULL);
	if (buf[i] != '\0')
	{
		ft_memmove(buf, &buf[i], buf_size - i);
		buf[buf_size - i] = '\0';
	}
	else
		buf[0] = '\0';
	return (return_str);
}

/*
 * while(1)の中かつbufに値があれば呼ばれる
 * bufに改行があった場合は、ft_buf_in_line()を呼ぶ
 * bufに改行がなく、return_strに値があった場合はreturn_strとbufを結合
 * bufに改行がなく、return_strに値が無い場合は、bufの文字列をreturn_strに格納
 */
static int	ft_while_loop(char *buf, char **return_str)
{
	char	*cp_str;

	if (ft_strchr(buf, '\n') != NULL)
	{
		*return_str = ft_buf_in_line(buf, *return_str);
		return (1);
	}
	else
	{
		if (*return_str != NULL)
		{
			cp_str = *return_str;
			*return_str = ft_strjoin(*return_str, buf);
			if (*return_str == NULL)
				return (1);
			free(cp_str);
		}
		else
		{
			*return_str = ft_strdup(buf);
			if (*return_str == NULL)
				return (1);
		}
	}
	return (0);
}

/*
 * fdを1行ずつ出力する関数
 * fdをBUFFER_SIZE分読み、改行もしくはreadが0バイトになったらそれまで読んだ文字を出力
 * 改行があった場合は、改行後をstatic変数で保存しておき次の改行もしくは0バイト時に一緒に出力
 */
char	*get_next_line(int fd)
{
	int			bytes;
	static char	buf[BUFFER_SIZE + 1];
	char		*return_str;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	return_str = NULL;
	while (1)
	{
		if (buf[0] != '\0')
			if (ft_while_loop(buf, &return_str))
				return (return_str);
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
		{
			buf[0] = '\0';
			return (return_str);
		}
		buf[bytes] = '\0';
	}
}

// #include <stdio.h>
// #include <fcntl.h>
// #include <string.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*map_file_str;

// 	// fd = open("unit-test1/files/nl", O_RDONLY);
// 	// fd = open("unit-test1/files/41_no_nl", O_RDONLY);
// 	fd = open("test.txt", O_RDONLY);
// 	// fd = 0;
// 	while (1)
// 	{
// 		map_file_str = get_next_line(fd);
// 		if (map_file_str == NULL)
// 			break ;
// 		// printf("len: %lu", strlen(map_file_str));
// 		printf("> %s", map_file_str);
// 		free(map_file_str);
// 	}
// 	// system("leaks a.out");
// 	return (0);
// }

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
