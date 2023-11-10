/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:38:58 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/22 14:31:37 by ugerkens         ###   ########.fr       */
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
	(void)argv;
	if (argc != 5)
		error("parse error", "wrong number of arguments", EXIT_FAILURE, NULL);
}
