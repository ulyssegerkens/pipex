/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:28 by ugerkens          #+#    #+#             */
/*   Updated: 2023/11/04 20:54:39 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *d, int argc, char **argv, char **env)
{
	errno = 0;
	d->allocated_pointers = NULL;
	d->env = env;
	d->env_paths = init_env_paths(env, d);
	d->here_doc = false;
	d->limiter = NULL;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		d->here_doc = true;
		d->limiter = argv[2];
	}
	d->input_file = argv[1];
	d->output_file = argv[argc - 1];
	d->n_cmd = argc - 3 - d->here_doc;
	d->commands = parse_cmd_list(argv + 2 + d->here_doc, d->n_cmd, d);
	d->last_cmd_exit_status = EXIT_SUCCESS;
}

char	**init_env_paths(char **env, t_data *d)
{
	char	**paths;
	char	*path;
	int		i;

	paths = NULL;
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		path = s_alloc(ft_strdup("/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:\
			/usr/local/sbin:/opt/bin:/opt/sbin"), TRACK, d);
	else
		path = env[i] + 5;
	paths = ft_split(path, ':');
	if (!paths)
		error("ft_split", "fail to split env path", EXIT_FAILURE, d);
	track_alloc(d, paths);
	i = 0;
	while (paths[i])
		track_alloc(d, paths[i++]);
	return (paths);
}

char	***parse_cmd_list(char **argv, int n_cmd, t_data *d)
{
	char	***cmd_list;
	int		i;

	i = 0;
	cmd_list = s_alloc(ft_calloc((n_cmd + 1), sizeof(char **)), TRACK, d);
	while (i < n_cmd)
	{
		cmd_list[i] = parse_cmd(argv[i], d);
		if (cmd_list[i][0] == NULL)
			error("parse error", "empty argument", EXIT_FAILURE, d);
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
