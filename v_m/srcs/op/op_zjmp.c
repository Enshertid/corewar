/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego  <ediego@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:39:34 by ediego            #+#    #+#             */
/*   Updated: 2020/05/02 18:40:02 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 		op_zjmp(t_vm *vm, t_car *car)
{
	//done
	vm->dump_value = 1000; // delete this
	if (!car->registers[1])
		car->cycle_to_action = 20;
}
