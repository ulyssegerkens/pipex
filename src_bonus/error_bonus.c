/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:16 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/22 14:36:35 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(const char *context, char *description, int exit_status,
		t_data *d)
{
	ft_write_fd("pipex: ", 2);
	ft_write_fd(description, 2);
	ft_write_fd(": ", 2);
	ft_write_fd(context, 2);
	ft_write_fd("\n", 2);
	if (d)
		ft_lstclear(&d->allocated_pointers, free);
	exit(exit_status);
}

void	syscall_error(const char *context, int errnum, t_data *d)
{
	error(context, strerror(errnum), EXIT_FAILURE, d);
}

void	report_errno(char *context, t_data *d)
{
	s_write_fd("pipex: ", 2, d);
	perror(context);
}

ssize_t	s_write_fd(const void *buf, int fd, t_data *d)
{
	ssize_t	ret;

	ret = ft_write_fd(buf, fd);
	if (ret == -1)
		syscall_error("ft_write_fd", errno, d);
	return (ret);
}
