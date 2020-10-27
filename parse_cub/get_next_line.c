/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 14:24:48 by hjung             #+#    #+#             */
/*   Updated: 2020/10/27 11:09:59 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	free(s1);
	s1 = NULL;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

int		chk_nl_exist(char *bckup)
{
	int			i;

	i = 0;
	while (bckup[i] != '\0')
	{
		if (bckup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ret_line(char **bckup, char **line, int i)
{
	char		*tmp_ptr;

	*line = ft_substr(*bckup, 0, i);
	tmp_ptr = ft_strdup(&(*bckup)[i + 1]);
	free(*bckup);
	*bckup = tmp_ptr;
	return (1);
}

int		ret_rest(char **bckup, char **line)
{
	int			i;

	if (*bckup == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (*bckup && (i = chk_nl_exist(*bckup)) >= 0)
		return (ret_line(bckup, line, i));
	else if (*bckup[0] != '\0')
	{
		*line = ft_strdup(*bckup);
		free(*bckup);
		*bckup = 0;
		return (0);
	}
	*line = ft_strdup("");
	free(*bckup);
	*bckup = 0;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	ssize_t		rd_size;
	char		buff[BUFFER_SIZE + 1];
	static char	*bckup[OPEN_MAX];

	if ((fd < 0) || !line || (BUFFER_SIZE <= 0))
		return (-1);
	while ((rd_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd_size] = '\0';
		bckup[fd] = gnl_strjoin(bckup[fd], buff);
		i = chk_nl_exist(bckup[fd]);
		if (i >= 0)
			return (ret_line(&bckup[fd], line, i));
	}
	if (rd_size < 0)
		return (-1);
	return (ret_rest(&bckup[fd], line));
}
