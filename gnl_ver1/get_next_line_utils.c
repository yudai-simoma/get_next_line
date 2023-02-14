/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:24:41 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/13 21:11:55 by yshimoma         ###   ########.fr       */
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
