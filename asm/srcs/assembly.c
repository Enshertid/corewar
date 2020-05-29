/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 15:02:43 by user              #+#    #+#             */
/*   Updated: 2020/05/29 16:03:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include "converter.h"

 #include <stdio.h>
static void	read_file(t_file *file)
{
	char	*line;
	bool	newline_exist;
	bool	final_newline_exist;

	final_newline_exist = false;
	file->lines = vec_create(80, sizeof(t_vector_char));
	// int i = 0;
	while ((gnl(file->fd, &line, &newline_exist)) == GNL_OK)
	{
		vec_pushback(&file->lines, &line);
		if (!useless_line(line))
			final_newline_exist = newline_exist;
		// printf("%d ok\n", i++);
	}
	if (vec_size(&file->lines) == 0)
		file->status = FILE_EMPTY;
	else if (final_newline_exist == false)
		file->status = FILE_NO_FINAL_NEWLINE;
}

static void	error_handle(const t_file *file, t_validation *val)
{
	if (file->status == FILE_NO_FINAL_NEWLINE)
	{
		warning_add(ERROR, 3, "File \"", file->name,
					"\" haven\'t final newline");
		val->no_newline_empty = 1;
	}
	else if (file->status == FILE_EMPTY)
	{
		warning_add(ERROR, 3, "File \"", file->name, "\" is empty");
		val->no_newline_empty = 1;
	}
}

void		assembly(t_file *file, t_validation *validation)
{
	file->bytecode = NULL;
	file->copy = NULL;
	file->lines = NULL;
	file->tokens = NULL;
	file->status = FILE_OK;
	read_file(file);
	file->copy = vec_copy(&file->lines, false);
	if (file->status != FILE_OK)
		error_handle(file, validation);
	else
	{
		file->tokens = tokenizer(file->lines, validation);
		ft_check_labels(file->tokens, validation);
		ft_check_sizes(file->tokens, validation);
		ft_check_instructions(file->tokens, validation);
		if (!ft_any_error(validation))
		{
			file->bytecode = convert_to_bytecode(file->tokens);
			write_to_file(file, file->bytecode);
		}
	}
	free_file(file);
}
