#include "../includes/tokenizer.h"
#include "../includes/token_determinator.h"

t_vector_token		line_to_tokens(const char *line, t_validation	*validation)
//t_vector_token		line_to_tokens(t_vector_char *lines, int *line_index, t_validation	*validation)
{
	t_vector_token	tokens;
	t_token			token;
//	const char 		*line;

//	line = lines[*line_index];
	tokens = vec_create(8, sizeof(t_token));
	while (*line)
	{
		while (*line && (*line == ' ' || *line == '\t'))
			++line;
		if (*line == COMMENT_CHAR)
			break ;
		token = token_determinator(&line, validation);
		vec_pushback(&tokens, &token);
	}
	return (tokens);
}

t_vector_token		*tokenizer(t_vector_char *lines, t_validation	*validation)
{
	const size_t	lines_count = vec_size(&lines);
	int				line_index;
	t_vector_token	*tokens;
	t_vector_token	tokens_line;

	validation->lines = lines;
	tokens = vec_create(lines_count, sizeof(t_vector_token));
	line_index = 0;
	validation->line_index = &line_index;
	while (line_index < (int)lines_count)
	{
		tokens_line = line_to_tokens(lines[line_index], validation);
		vec_pushback(&tokens, &tokens_line);
		line_index += 1;
	}
	return (tokens);
}