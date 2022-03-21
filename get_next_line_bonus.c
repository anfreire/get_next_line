/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfreire <anfreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:22:21 by anfreire          #+#    #+#             */
/*   Updated: 2022/03/21 18:43:17 by anfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*str_prcs(char **str)
{
	char	*tmp;
	char	*out;
	size_t	i;

	i = 0;
	out = NULL;
	while ((*str)[i] != 10 && (*str)[i])
		i++;
	if ((*str)[i] == 10)
	{
		out = ft_substr(*str, 0, i + 1);
		tmp = ft_strdup(*str + i + 1);
		free(*str);
		*str = tmp;
		if (!**str)
		{
			free(*str);
			*str = NULL;
		}
		return (out);
	}
	out = ft_strdup(*str);
	free(*str);
	*str = NULL;
	return (out);
}

static char	*str_checker(char **str, ssize_t nbytes, int fd)
{
	if (nbytes < 0)
		return (NULL);
	if (!nbytes && (!str[fd] || !*str[fd]))
		return (NULL);
	return (str_prcs(&str[fd]));
}

char	*get_next_line(int fd)
{
	static char		*str[1024];
	char			*tmp;
	char			*dest;
	ssize_t			nbytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	nbytes = read(fd, tmp, BUFFER_SIZE);
	while (nbytes > 0)
	{
		tmp[nbytes] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup("");
		dest = ft_strjoin(str[fd], tmp);
		free(str[fd]);
		str[fd] = dest;
		if (ft_strchr(tmp, 10))
			break ;
		nbytes = read(fd, tmp, BUFFER_SIZE);
	}
	free(tmp);
	return (str_checker(str, nbytes, fd));
}

/*
int	main()
{
	int fd;
	fd = open("texto.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

	
	
	return (0);
}*/
