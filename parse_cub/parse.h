/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:46:58 by hjung             #+#    #+#             */
/*   Updated: 2020/10/26 18:05:01 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "get_next_line.h"

typedef	struct	s_map_info
{
	
	int			*map;
	int			rows;
	int			cols;
}				t_map_info;

int	parse_map(t_map_info *map_info);

#endif