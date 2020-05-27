/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_determinator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:57:45 by user              #+#    #+#             */
/*   Updated: 2020/05/27 16:16:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token_determinator.h"

static void	skip_unknown_token(const char **lineptr)
{
	const char *line = *lineptr;

	while (*line && *line != ' ' && *line != '\t')
		line += 1;
	*lineptr = line;
}

void		ft_mark_error_token(t_token *token, t_validation *val)
{
	token->type = UNKNOWN;
	token->value = NULL;
	val->error = 1;
	if (val->dbl_c == 0 && val->dbl_n == 0)
		warning_add(ERROR, 3, "syntax error in line №",
				ft_itoa_static(*val->line_index + 1, 10), ".");
}

t_token		token_determinator(const char **lineptr, t_validation *validation)
{
	t_token	token;
	bool	token_determined;

	token_determined = false;
	token_determined = is_separator(lineptr, &token);
	if (!token_determined)
		token_determined = is_empty(lineptr, &token);
	if (!token_determined)
		token_determined = is_label(lineptr, &token);
	if (!token_determined)
		token_determined = is_instruction(lineptr, &token, validation);
	if (!token_determined)
		token_determined = is_argument(lineptr, &token);
	if (!token_determined)
		token_determined = is_name(lineptr, &token, validation);
	if (!token_determined)
		token_determined = is_comment(lineptr, &token, validation);
	if (!token_determined)
	{
		ft_mark_error_token(&token, validation);
		skip_unknown_token(lineptr);
	}
	return (token);
}
