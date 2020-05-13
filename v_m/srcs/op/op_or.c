/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego  <ediego@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:54:37 by ediego            #+#    #+#             */
/*   Updated: 2020/05/02 17:54:56 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "vm.h"

void 		op_or(t_vm *vm, t_car *car)
{
	int8_t	first;
	int8_t	sec;
	int8_t	third;
	int32_t	first_arg;
	int32_t	second_arg;
	
	first = determine_arg(vm->arena[get_new_pos(car->position, car->step)], 0);
	sec = determine_arg(vm->arena[get_new_pos(car->position, car->step)], 1);
	third = determine_arg(vm->arena[get_new_pos(car->position, car->step)], 2);
	car->step = OP_BYTE + ARG_CHECK;
	if (first != 0 && sec != 0 && third != 0)
		if (get_arg_dir_four(vm, car, first, &first_arg))
			if (get_arg_dir_four(vm, car, sec, &second_arg))
				use_args(vm, car, ((unsigned)first_arg | (unsigned)second_arg),
						 third);
	car->position = get_new_pos(car->position, car->step + REG);
	car->code = read_byte(vm, car->position) - 1;
	if (car->code >= 0 && car->code < OP_NUM)
		car->cycle_to_action = vm->operations.op_cycles[car->code];
	car->step = OP_BYTE;
}