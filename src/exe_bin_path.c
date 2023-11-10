/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:44 by ugerkens          #+#    #+#             */
/*   Updated: 2023/11/04 20:04:58 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_bin_path(char *bin, char **env_path, t_data *d)
{
	if (ft_strchr(bin, '/'))
		return (check_bin_with_path(bin, d));
	return (find_path(bin, env_path, d));
}

char	*check_bin_with_path(char *bin, t_data *d)
{
	if (check_access(bin, d))
		return (bin);
	if (errno == EACCES)
		error("permission denied", bin, 126, d);
	else if (errno != ENOENT)
		error("command not found", bin, 127, d);
	return (NULL);
}

char	*find_path(char *bin, char **env_path, t_data *d)
{
	int		i;
	bool	permission_denied;
	char	*full_path;

	i = 0;
	permission_denied = false;
	if (!env_path)
		error("command not found", bin, 127, d);
	while (env_path[i])
	{
		full_path = join_path(env_path[i], bin, d);
		if (check_access(full_path, d))
			return (full_path);
		if (errno == EACCES)
			permission_denied = true;
		free(full_path);
		i++;
	}
	if (permission_denied)
		error("permission denied", bin, 126, d);
	else
		error("command not found", bin, 127, d);
	return (NULL);
}

char	*join_path(char *dir, char *file, t_data *d)
{
	char	*slash_path;
	char	*full_path;

	slash_path = ft_strjoin(dir, "/");
	if (!slash_path)
		error("ft_strjoin", "fail to join file path", EXIT_FAILURE, d);
	full_path = ft_strjoin(slash_path, file);
	if (!full_path)
		error("ft_strjoin", "fail to join file path", EXIT_FAILURE, d);
	free(slash_path);
	return (full_path);
}

bool	check_access(char *bin, t_data *d)
{
	if (access(bin, X_OK) == EXIT_SUCCESS)
		return (true);
	if (errno != 0 && errno != EACCES && errno != ENOENT)
		syscall_error(bin, errno, d);
	return (false);
}
