/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego  <ediego@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:30:32 by ediego            #+#    #+#             */
/*   Updated: 2020/05/02 16:24:36 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 		op_sti(t_vm *vm, t_car *car)
{
	//done
	vm->dump_value = 1000; // delete this
	car->cycle_to_action = 25;
}

