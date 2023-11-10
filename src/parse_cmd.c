/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:39:04 by ugerkens          #+#    #+#             */
/*   Updated: 2023/10/19 23:47:37 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_cmd(char *str, t_data *d)
{
	t_parser	parser;
	char		**cmd_exe;

	init_parser(&parser, str, d);
	while (str[parser.i])
	{
		if (parser.state == NORMAL)
			normal_state(str, &parser, d);
		else if (parser.state == IN_SINGLE_QUOTE)
			single_quote_state(str, &parser);
		else if (parser.state == IN_DOUBLE_QUOTE)
			double_quote_state(str, &parser);
		parser.i++;
	}
	if (parser.state != NORMAL)
		error("parse error", "unclosed quote", EXIT_FAILURE, d);
	add_token_to_list(&parser, d);
	cmd_exe = convert_list_to_array(&parser, d);
	free(parser.buf);
	return (cmd_exe);
}

void	normal_state(char *str, t_parser *parser, t_data *d)
{
	if (str[parser->i] == ' ')
		add_token_to_list(parser, d);
	else if (str[parser->i] == '\"')
		parser->state = IN_DOUBLE_QUOTE;
	else if (str[parser->i] == '\'')
		parser->state = IN_SINGLE_QUOTE;
	else if (str[parser->i] == '\\')
		parser->buf[parser->buf_i++] = str[++parser->i];
	else
		parser->buf[parser->buf_i++] = str[parser->i];
}

void	single_quote_state(char *str, t_parser *parser)
{
	if (str[parser->i] == '\'')
		parser->state = NORMAL;
	else
		parser->buf[parser->buf_i++] = str[parser->i];
}

void	double_quote_state(char *str, t_parser *parser)
{
	if (str[parser->i] == '\"')
		parser->state = NORMAL;
	else if (str[parser->i] == '\\')
	{
		parser->i++;
		if (str[parser->i] == 'n')
			parser->buf[parser->buf_i++] = '\n';
		else if (str[parser->i] == 't')
			parser->buf[parser->buf_i++] = '\t';
		else if (str[parser->i] == '\"' || str[parser->i] == '\\')
			parser->buf[parser->buf_i++] = str[parser->i];
	}
	else
		parser->buf[parser->buf_i++] = str[parser->i];
}
