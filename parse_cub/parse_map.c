/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:13:50 by hjung             #+#    #+#             */
/*   Updated: 2020/10/26 18:32:44 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>

int	parse_map(t_map_info *map_info)
{
	int		ret;
	int		fd;
	char	*line;

	//*line이 선언된 상태로 get_next_line 함수로 넘어감

	fd = open("map/map.cub", O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((ret = (get_next_line(fd, &line)) > 0))
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	
	close(fd);
	return (0);
}