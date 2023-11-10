/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:31 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/22 14:32:04 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	d;

	check_args(argc, argv);
	init_data(&d, argc, argv, env);
	execute_pipeline(&d);
	ft_lstclear(&d.allocated_pointers, free);
	return (d.last_cmd_exit_status);
}

void	check_args(int argc, char **argv)
{
	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
		error("parse error", "not enough arguments", EXIT_FAILURE, NULL);
}
