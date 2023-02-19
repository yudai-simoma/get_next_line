/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:55:22 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/19 10:54:26 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
static char	*set_str_in_line(char *buf, char *return_str, size_t l_num)
{
	char	*cp_str;

	if (return_str != NULL)
	{
		cp_str = return_str;
		return_str = ft_strjoin(return_str, buf);
		if (return_str == NULL)
		{
			free(cp_str);
			return (NULL);
		}
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
static char	*buf_in_line(char *buf, char *return_str)
{
	size_t	i;
	size_t	buf_size;

	i = 0;
	buf_size = ft_strlen(buf);
	while (buf[i] != '\n')
		i++;
	i++;
	return_str = set_str_in_line(buf, return_str, i);
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
static int	set_str(char *buf, char **return_str)
{
	char	*cp_str;

	if (ft_strchr(buf, '\n') != NULL)
	{
		*return_str = buf_in_line(buf, *return_str);
		return (1);
	}
	else
	{
		if (*return_str != NULL)
		{
			cp_str = *return_str;
			*return_str = ft_strjoin(*return_str, buf);
			free(cp_str);
			if (*return_str == NULL)
				return (1);
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
	ssize_t		bytes;
	static char	buf[OPEN_MAX + 1][BUFFER_SIZE + 1];
	char		*return_str;

	if (fd >= OPEN_MAX + 1 || fd < 0
		|| BUFFER_SIZE < 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	return_str = NULL;
	while (1)
	{
		if ((buf[fd][0] != '\0') && set_str(buf[fd], &return_str))
			return (return_str);
		bytes = read(fd, buf[fd], BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (bytes < 0)
			{
				free (return_str);
				return_str = NULL;
			}
			buf[fd][0] = '\0';
			return (return_str);
		}
		buf[fd][bytes] = '\0';
	}
}

// #include <stdio.h>
// #include <fcntl.h>
// #include <string.h>
// int main(void)
// {
// 	int	fd;
// 	int fd1;

// 	fd = open("./test.txt",O_RDONLY);
// 	fd1 = open("./test2.txt",O_RDONLY);

// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd1));

// 	// printf("");
// 	puts("\n\n\n----------------------------\n\n\n");
// 	printf("%s",get_next_line(fd));
// 	printf("%s",get_next_line(fd1));
// }
