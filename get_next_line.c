/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhajja <melhajja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:34:14 by melhajja          #+#    #+#             */
/*   Updated: 2023/01/17 21:14:42 by melhajja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char *str){
	free(str);
	str = NULL;
}
char	*two_free(char *str1, char *str2){
	free(str1);
	str1 = NULL;
	free(str2);
	str2 = NULL;
	return (NULL);
}
char	*read_lines(int fd, char *storage, char *buffer)
{
	ssize_t		read_bytes;

	read_bytes = 1;
	while (read_bytes > 0){
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((read_bytes == 0 && storage == NULL) || read_bytes == -1){
			if(read_bytes == -1 && storage)
				ft_free(storage);
			ft_free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		if (!storage)
			storage = ft_strdup(buffer);
		else{
			storage = ft_strjoin(storage, buffer);
			if (!storage)
				two_free(storage, buffer);
		}
		if (position(storage) != -7)
			break ;
	}
	ft_free(buffer);
	return (storage);
}
char	*get_line(char *storage){
	int	newline_position;
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	newline_position = position(storage);
	if(newline_position == -7 && ft_strlen(storage) > 0){
		line = ft_strdup(storage);
		ft_free(storage);
	}
	if(newline_position != -7 && ft_strlen(storage) > 0)
	{	
		if(storage[0] == '\n')
			line = ft_strdup("\n");
		else
			line = ft_substr(storage, 0, newline_position + 1);
		tmp = ft_substr(storage, newline_position + 1, ft_strlen(storage));
		ft_free(storage);
		storage = ft_strdup(tmp);
		ft_free(tmp);
	}
	return (line);
}

char	*get_next_line(int fd){
	static char	*storage;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	// printf("before-->storage-%s--buffer-->%s--\n", storage, buffer);
	storage = read_lines(fd, storage, buffer);
	printf("content : --%s--\n", storage);
	// printf("after-->storage-%s--buffer-->%s--\n", storage, buffer);
	return (get_line(storage));
	// return ("salat");
}

int main(){
	int fd = open("file2.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}