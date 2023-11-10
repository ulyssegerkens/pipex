/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:07 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/19 23:35:31 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	s_open(const char *pathname, int flags, mode_t mode, t_data *d)
{
	int	ret;

	ret = open(pathname, flags, mode);
	if (ret == -1)
		syscall_error(pathname, errno, d);
	return (ret);
}

int	s_close(int fd, t_data *d)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		syscall_error("close", errno, d);
	return (ret);
}

int	s_dup2(int oldfd, int newfd, t_data *d)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret == -1)
		syscall_error("dup2", errno, d);
	return (ret);
}

int	s_unlink(const char *pathname, t_data *d)
{
	int	ret;

	ret = unlink(pathname);
	if (ret == -1)
		syscall_error("unlink", errno, d);
	return (ret);
}
