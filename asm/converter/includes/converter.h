/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:25:34 by user              #+#    #+#             */
/*   Updated: 2020/05/10 14:53:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_H
# define CONVERTER_H

#include "token.h"
#include "libft.h"

t_vector_char	*convert_to_bytecode(const t_vector_token *tokens);

#endif
