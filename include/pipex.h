/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 00:06:15 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/22 14:32:35 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// standard libraries
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
// personal libraries
# include "get_next_line.h"
# include "libft.h"

// Main structure
typedef struct s_data
{
	char		**env;
	char		**env_paths;

	char		*input_file;
	bool		here_doc;
	char		*limiter;
	char		*output_file;

	int			n_cmd;
	char		***commands;
	int			last_cmd_exit_status;

	t_list		*allocated_pointers;
}				t_data;

typedef enum t_alloc
{
	CHECK,
	TRACK
}				t_alloc;

# define READ_END 0
# define WRITE_END 1

// Parser structure
typedef enum t_prs_state
{
	NORMAL,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
}				t_prs_state;

typedef struct s_parser
{
	t_prs_state	state;
	int			i;
	char		*buf;
	int			buf_i;
	t_list		*tokens;
}				t_parser;

// Functions
// Main
int				main(int argc, char **argv, char **env);
void			check_args(int argc, char **argv);

// Initialization
void			init_data(t_data *d, int argc, char **argv, char **env);
char			**init_env_paths(char **env, t_data *d);
char			***parse_cmd_list(char **argv, int n_cmd, t_data *d);

// Commands parsing
char			**parse_cmd(char *str, t_data *d);
void			normal_state(char *str, t_parser *parser, t_data *d);
void			single_quote_state(char *str, t_parser *parser);
void			double_quote_state(char *str, t_parser *parser);
// Commands parsing Utils
void			init_parser(t_parser *parser, char *str, t_data *d);
void			add_token_to_list(t_parser *parser, t_data *d);
char			**convert_list_to_array(t_parser *parser, t_data *d);

// Pipeline execution
void			execute_pipeline(t_data *d);
pid_t			execute_command(t_data *d, int prev_read_end, int p[2], int i);
void			setup_for_next_command(int *prev_read_end, int p[2], t_data *d);
void			wait_for_children(t_data *d, pid_t last_pid);

// Infile and Outfile
void			setup_input(char *filename, char *limiter, t_data *d);
void			setup_output(char *filename, t_data *d);
int				heredoc_listener(char *limiter, t_data *d);

// Seach binary path for execution
char			*get_bin_path(char *bin, char **env_path, t_data *d);
char			*check_bin_with_path(char *bin, t_data *d);
char			*find_path(char *bin, char **env_path, t_data *d);
char			*join_path(char *dir, char *file, t_data *d);
bool			check_access(char *bin, t_data *d);

// Error
void			error(const char *context, char *description, int exit_status,
					t_data *d);
void			syscall_error(const char *context, int errnum, t_data *d);
void			report_errno(char *context, t_data *d);
ssize_t			s_write_fd(const void *buf, int fd, t_data *d);

// Allocation
void			*s_alloc(void *pointer, t_alloc mode, t_data *d);
void			track_alloc(t_data *d, void *pointer);
void			free_data(t_data *d);

// Facade for system call
// Syscall: File descriptor
int				s_open(const char *pathname, int flags, mode_t mode, t_data *d);
int				s_close(int fd, t_data *d);
int				s_dup2(int oldfd, int newfd, t_data *d);
int				s_unlink(const char *pathname, t_data *d);
// Syscall: Process
int				s_execve(const char *pathname, char *const argv[],
					char *const envp[], t_data *d);
pid_t			s_fork(t_data *d);
int				s_pipe(int pipefd[2], t_data *d);
pid_t			s_wait(int *wstatus, t_data *d);

#endif
