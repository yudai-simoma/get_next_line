/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:31:54 by yshimoma          #+#    #+#             */
/*   Updated: 2023/03/09 18:32:13 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int	main(void)
{
	int		fd;
	char	*map_file_str;

	// fd = open("unit-test1/files/nl", O_RDONLY);
	// fd = open("unit-test1/files/41_no_nl", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	// fd = 0;
	while (1)
	{
		map_file_str = get_next_line(fd);
		printf("> %s", map_file_str);
		if (map_file_str == NULL)
			break ;
		// printf("len: %lu", strlen(map_file_str));
		free(map_file_str);
	}
	// system("leaks a.out");
	return (0);
}
