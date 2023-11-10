/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:37 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/19 23:00:27 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_pipeline(t_data *d)
{
	int		p[2];
	int		prev_read_end;
	pid_t	last_pid;
	int		i;

	prev_read_end = -1;
	setup_input(d->input_file, d->limiter, d);
	setup_output(d->output_file, d);
	i = 0;
	while (i < d->n_cmd)
	{
		s_pipe(p, d);
		last_pid = execute_command(d, prev_read_end, p, i);
		setup_for_next_command(&prev_read_end, p, d);
		i++;
	}
	wait_for_children(d, last_pid);
}

pid_t	execute_command(t_data *d, int prev_read_end, int p[2], int i_cmd)
{
	pid_t	pid;
	char	**cmd_exe;

	pid = s_fork(d);
	if (pid != 0)
		return (pid);
	if (prev_read_end != -1)
	{
		s_dup2(prev_read_end, STDIN_FILENO, d);
		s_close(prev_read_end, d);
	}
	if (i_cmd < d->n_cmd - 1)
		s_dup2(p[WRITE_END], STDOUT_FILENO, d);
	s_close(p[READ_END], d);
	s_close(p[WRITE_END], d);
	cmd_exe = d->commands[i_cmd];
	s_execve(get_bin_path(cmd_exe[0], d->env_paths, d), cmd_exe, d->env, d);
	return (pid);
}

void	setup_for_next_command(int *prev_read_end, int p[2], t_data *d)
{
	if (*prev_read_end != -1)
		s_close(*prev_read_end, d);
	s_close(p[WRITE_END], d);
	*prev_read_end = p[READ_END];
}

void	wait_for_children(t_data *d, pid_t last_pid)
{
	int		i;
	pid_t	child_pid;
	int		status;

	i = 0;
	while (i < d->n_cmd)
	{
		child_pid = s_wait(&status, d);
		if (child_pid == last_pid && WIFEXITED(status))
			d->last_cmd_exit_status = WEXITSTATUS(status);
		i++;
	}
}
