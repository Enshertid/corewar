/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_determinator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:57:45 by user              #+#    #+#             */
/*   Updated: 2020/05/12 22:31:43 by user             ###   ########.fr       */
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

t_token		token_determinator(const char **lineptr, t_validation *validation)
{
	t_token	token;
	bool	token_determined;

	token_determined = false;
	token_determined = is_separator(lineptr, &token);
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
		token.type = UNKNOWN;
		token.value = NULL;
		validation->error = 1;
		if (validation->dbl_c == 0 && validation->dbl_n == 0)
			warning_add(ERROR, 2, "token_determinator Syntax error. Line: ", validation->line_index);
		skip_unknown_token(lineptr);
	}
	return (token);
}
