/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:54:22 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/16 19:58:39 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
** 指定バイト数分のメモリをコピーする関数です。
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*cp_dst;
	const unsigned char	*cp_src;
	size_t				i;

	if ((dst == src) || (n == 0))
		return (dst);
	cp_dst = (unsigned char *)dst;
	cp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cp_dst[i] = cp_src[i];
		i++;
	}
	return (dst);
}

/*
** 指定したバイト数のメモリをコピー(移動)する関数です。
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*cp_dst;
	const unsigned char	*cp_src;

	if (dst == src)
		return (NULL);
	cp_dst = (unsigned char *)dst;
	cp_src = (const unsigned char *)src;
	if (dst > src)
	{
		while (len)
		{
			cp_dst[len - 1] = cp_src[len - 1];
			len--;
		}
	}
	else
		return (ft_memcpy(cp_dst, cp_src, len));
	return (dst);
}
