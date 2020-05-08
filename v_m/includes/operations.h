/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enshertid <enshertid@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:10:42 by ediego            #+#    #+#             */
/*   Updated: 2020/05/05 11:39:11 by enshertid        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# define REG 1
# define DIR 4
# define IND 2
# define ARG_CHECK 1
# define OP_BYTE 1

#include "libft.h"
#include "carriages.h"

typedef struct		s_vm t_vm;

typedef struct		s_operations
{
	void			(*func[16])(t_vm *vm, t_car *caret);
	int				op_cycles[16];
}					t_op;

void				op_live(t_vm *vm, t_car *car);
void				op_ld(t_vm *vm, t_car *car);
void				op_st(t_vm *vm, t_car *car);
void				op_add(t_vm *vm, t_car *car);
void				op_sub(t_vm *vm, t_car *car);
void				op_and(t_vm *vm, t_car *car);
void				op_or(t_vm *vm, t_car *car);
void				op_xor(t_vm *vm, t_car *car);
void				op_zjmp(t_vm *vm, t_car *car);
void				op_ldi(t_vm *vm, t_car *car);
void				op_sti(t_vm *vm, t_car *car);
void				op_fork(t_vm *vm, t_car *car);
void				op_lld(t_vm *vm, t_car *car);
void				op_lldi(t_vm *vm, t_car *car);
void				op_lfork(t_vm *vm, t_car *car);
void				op_aff(t_vm *vm, t_car *car);

int					determine_arg(unsigned char byte, unsigned int index);
void				set_array_of_operations(t_vm *vm);
void				set_array_of_cycles_to_op(t_vm *vm);

unsigned char		read_reg(t_vm *vm, int position);
int16_t				read_ind(t_vm *vm, int position);
int32_t				read_dir(t_vm *vm, int position);
int32_t				get_new_pos(int32_t position, int32_t step);

t_bool				get_arg(t_vm *vm, t_car *car, int8_t sw_arg, int32_t *arg);
void				use_args(t_vm *vm, t_car *car, int32_t result, int8_t third);
void				write_reg_to_arena(t_vm *vm, int value, int position);


#endif
