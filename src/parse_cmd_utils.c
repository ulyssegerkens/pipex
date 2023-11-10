/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:01 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/19 23:07:14 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_parser(t_parser *parser, char *str, t_data *d)
{
	parser->i = 0;
	parser->buf = s_alloc(ft_calloc(ft_strlen(str) + 1, sizeof(char)), CHECK,
			d);
	parser->buf_i = 0;
	parser->state = NORMAL;
	parser->tokens = NULL;
}

void	add_token_to_list(t_parser *parser, t_data *d)
{
	t_list	*new_token;
	char	*content;

	if (parser->buf_i != 0)
	{
		parser->buf[parser->buf_i] = '\0';
		content = s_alloc(ft_strdup(parser->buf), TRACK, d);
		new_token = s_alloc(ft_lstnew(content), CHECK, d);
		ft_lstadd_back(&(parser->tokens), new_token);
		parser->buf_i = 0;
	}
}

char	**convert_list_to_array(t_parser *parser, t_data *d)
{
	t_list	*current;
	char	**cmd_exe;
	int		i;

	cmd_exe = (char **)s_alloc(ft_calloc(ft_lstsize(parser->tokens) + 1,
				sizeof(char *)), TRACK, d);
	i = 0;
	current = parser->tokens;
	while (current)
	{
		cmd_exe[i++] = (char *)current->content;
		current = current->next;
	}
	ft_lstclear(&parser->tokens, NULL);
	return (cmd_exe);
}
