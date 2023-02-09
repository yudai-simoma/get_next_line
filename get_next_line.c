/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoma <yshimoma@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:51:45 by yshimoma          #+#    #+#             */
/*   Updated: 2023/02/09 20:46:09 by yshimoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * save に値が入っていたら呼ばれる
 * saveの中に改行があれば、lineに入れて出力
 * saveの中に改行がなければ、lineに格納
 */
int	ft_save_add_line(t_file *file)
{
	if (ft_strchr(file->save, '\n') != NULL)
	{
		file->line = ft_add_str(file->save, NULL, 0);
		if (file->line == NULL)
			return (1);
		file->backup = file->save;
		free(file->save);
		file->save = NULL;
		file->save = ft_add_str(file->backup, NULL, 1);
		if (file->save == NULL)
			return (1);
		return (1);
	}
	else
	{
		file->line = ft_add_str(file->save, NULL, 0);
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
	free(file->save);
	file->save = NULL;
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
	return (0);
}

/*
 * 無限ループの中で呼ばれる
 */
int	ft_whil_loop(int fd, int bytes, t_file *file)
{
	bytes = read(fd, &file->buf, BUFFER_SIZE);
	if (bytes == 0)
	{
		free(file->save);
		file->save = NULL;
		return (1);
	}
	file->buf[bytes] = '\0';
	if (ft_strchr(file->buf, '\n') != NULL)
	{
		if (ft_buf_add_save_line(file))
			return (1);
	}
	else
	{
		if (ft_buf_add_line(file))
			return (1);
	}	
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
		free(file.line);
		file.line = NULL;
	if (file.save != NULL)
		if (ft_save_add_line(&file))
			return (file.line);
	bytes = 0;
	while (1)
	{
		if (ft_whil_loop(fd, bytes, &file))
			return (file.line);
	}
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*map_file_str;

	fd = open("test.txt", O_RDONLY);
	fd = 0;
	while (1)
	{
		map_file_str = get_next_line(fd);
		if (map_file_str == NULL)
			break ;
		printf("> %s", map_file_str);
	}
	return (0);
}

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
