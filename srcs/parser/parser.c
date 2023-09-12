/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:21:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/11 14:20:06 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*parser_loop(t_token **tmp_token, t_parser **tmp,
		t_parser **parser_head)
{
	if ((*tmp_token)->type == PIPE)
	{
		if (parser_pipe(tmp, *parser_head) == NULL)
			return (NULL);
	}
	else if (is_redirect(*tmp_token) == true)
	{
		if (parser_redirect(tmp_token, tmp) == NULL)
			return (free_parser_null(*parser_head));
	}
	else
	{
		if (parser_cmd(tmp_token, tmp) == NULL)
			return (free_parser_null(*parser_head));
	}
	return (tmp);
}

t_parser	*parser(t_token *token_head)
{
	t_parser	*parser_head;
	t_parser	*tmp;
	t_token		*tmp_token;

	// ft_printf("------------ parser start -----------\n");
	evoluve_token(token_head);
	parser_head = parser_init();
	if (parser_head == NULL)
		return (NULL);
	tmp = parser_head;
	tmp_token = token_head->next;
	while (tmp_token != token_head)
	{
		if (parser_loop(&tmp_token, &tmp, &parser_head) == NULL)
			return (NULL);
		tmp_token = tmp_token->next;
	}
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	parser_head = tmp;
	// ft_printf("------------ parser result -----------\n");
	// print_parser(parser_head);
	// ft_printf("---------- parser result end ---------\n");
	return (parser_head);
}
