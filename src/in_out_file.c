/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:51 by ugerkens          #+#    #+#             */
/*   Updated: 2023/11/07 12:47:25 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_input(char *filename, char *limiter, t_data *d)
{
	int	input_fd;

	if (limiter != NULL)
		input_fd = heredoc_listener(limiter, d);
	else
	{
		input_fd = open(filename, O_RDONLY);
		if (input_fd == -1)
		{
			report_errno(filename, d);
			input_fd = s_open("/dev/null", O_RDONLY, 0, d);
		}
	}
	s_dup2(input_fd, STDIN_FILENO, d);
	s_close(input_fd, d);
}

void	setup_output(char *filename, t_data *d)
{
	int	output_fd;

	output_fd = s_open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644, d);
	s_dup2(output_fd, STDOUT_FILENO, d);
	s_close(output_fd, d);
}

int	heredoc_listener(char *limiter, t_data *d)
{
	int		tmp_fd;
	char	*line;
	int		gnl_status;

	tmp_fd = s_open("/tmp/.pp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600, d);
	gnl_status = EXIT_SUCCESS;
	while (gnl_status == EXIT_SUCCESS)
	{
		gnl_status = get_next_line(0, &line);
		if (gnl_status == EXIT_FAILURE)
			error("get_next_line", "fail to read heredoc", EXIT_FAILURE, d);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		s_write_fd(line, tmp_fd, d);
		free(line);
	}
	s_close(tmp_fd, d);
	tmp_fd = s_open("/tmp/.pp_heredoc", O_RDONLY, 0600, d);
	s_unlink("/tmp/.pp_heredoc", d);
	return (tmp_fd);
}
