/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:17 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/20 00:08:16 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*s_alloc(void *pointer, t_alloc mode, t_data *d)
{
	if (!pointer)
		error("Memory allocation", strerror(errno), EXIT_FAILURE, d);
	if (mode == TRACK)
		track_alloc(d, pointer);
	return (pointer);
}

void	track_alloc(t_data *d, void *pointer)
{
	t_list	*new_node;

	new_node = ft_lstnew(pointer);
	if (!new_node)
	{
		free(pointer);
		error("Memory allocation", strerror(errno), EXIT_FAILURE, d);
	}
	ft_lstadd_front(&d->allocated_pointers, new_node);
}
