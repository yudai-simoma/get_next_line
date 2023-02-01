/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:51:45 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/01 19:38:57 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{

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
