/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:10 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/19 23:07:45 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	s_execve(const char *pathname, char *const argv[], char *const envp[],
		t_data *d)
{
	int	ret;

	ret = execve(pathname, argv, envp);
	if (ret == -1)
		syscall_error("execve", errno, d);
	return (ret);
}

pid_t	s_fork(t_data *d)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
		syscall_error("fork", errno, d);
	return (ret);
}

int	s_pipe(int pipefd[2], t_data *d)
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == -1)
		syscall_error("pipe", errno, d);
	return (ret);
}

pid_t	s_wait(int *wstatus, t_data *d)
{
	pid_t	ret;

	ret = wait(wstatus);
	if (ret == -1)
		syscall_error("wait", errno, d);
	return (ret);
}
