/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego  <ediego@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:44:25 by ediego            #+#    #+#             */
/*   Updated: 2020/05/16 21:28:34 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//void 		op_lldi(t_vm *vm, t_car *car)
//{
//	int8_t args;
//	int32_t sum;
//	int32_t pos;
//	int32_t value;
//	int32_t reg3;
//
//	printf("LLDI(%d): Cycle = %ld  POS = %d ", car->id, vm->current_cycle, car->position);
//	car->step = 2;
//	args = vm->arena[(car->position + 1) % MEM_SIZE];
//	if (valid_args(vm, car, args))
//	{
//		sum = get_arg_n(vm, car, args) + get_arg_n(vm, car, args << 2);
//		pos = calc_pos(car, sum);
//		value = read_four_bytes(vm, pos % MEM_SIZE);
//		reg3 = vm->arena[(car->position + car->step) % MEM_SIZE];
//		printf(" SUM = %d POS = %d VALUE = %d ", sum, pos, value);
//		set_reg(car, reg3, value, 0);
//	}
//	car->position += get_arg_step(args, 3, DIR_SIZE / 2);
//	car->step = OP_BYTE;
//	printf(" END pos = %d\n", car->position);
//}

// 	int8_t args;
// 	int32_t arg1;
// 	int32_t arg2;
// 	int32_t value;
// 	int32_t reg3;

// 	printf("LLDI(%d): Cycle = %ld  POS = %d ", car->id, vm->current_cycle, car->position);
// 	car->step = 2;
// 	args = vm->arena[(car->position + 1) % MEM_SIZE];
// 	if (valid_args(vm, car, args))
// 	{
// 		arg1 = get_arg_n(vm, car, args);
// 		arg2 = get_arg_n(vm, car, args << 2);
// 		if (check_arg(args) == IND_CODE)
// 			value = read_four_bytes(vm, ((car->position + (arg1 + arg2) % IDX_MOD) % MEM_SIZE));
// 		else
// 			value = read_four_bytes(vm, ((car->position + (arg1 + arg2)) % MEM_SIZE));
// 		reg3 = vm->arena[(car->position + car->step) % MEM_SIZE];
// 		printf(" ARG1 = %d ARG2 = %d REG3 = %d ", arg1, arg2, reg3);
// 		set_reg(car, reg3, value, 1);
// 	}
// 	car->position += get_arg_step(args, 3, DIR_SIZE / 2);
// 	car->step = OP_BYTE;
// 	printf(" END pos = %d\n", car->position);
// }

static void	get_op(t_vm *vm, t_car *car, int32_t step, int8_t arg)
{
	if (arg != REG)
		return ;
	arg = read_byte(vm, get_new_pos(car->position, car->step)) - 1;
	if (arg < 0 || arg >= REG_NUMBER)
		return ;
	car->registers[arg] = read_four_bytes(vm,
										  get_new_pos(car->position, step));
}

static t_bool	get_second(t_vm *vm, t_car *car, int8_t sw_arg, int32_t *val)
{
	if (sw_arg != REG && sw_arg != DIR)
		return (FALSE);
	if (sw_arg == REG)
	{
		*val = read_byte(vm, get_new_pos(car->position, car->step)) - 1;
		if (*val < 0 || *val >= REG_NUMBER)
			return (FALSE);
		*val = car->registers[*val];
	}
	else
		*val = read_two_bytes(vm, get_new_pos(car->position, car->step));
	if (sw_arg == DIR)
		car->step += DIR / 2;
	else
		car->step += REG;
	return (TRUE);
}

void		op_ldi(t_vm *vm, t_car *car)
{
	int8_t first;
	int8_t sec;
	int8_t third;
	int32_t first_val;
	int32_t sec_val;
	
	first = determine_arg(vm->arena[get_new_pos(car->position, car->step)], 0);
	sec = determine_arg(vm->arena[get_new_pos(car->position, car->step)], 1);
	third = determine_arg(vm->arena[get_new_pos(car->position, car->step)], 2);
	car->step += ARG_CHECK;
	if (first && sec && third)
		if (get_arg_dir_two(vm, car, &first, &first_val))
			if (get_second(vm, car, sec, &sec_val))
				get_op(vm, car, (first_val + sec_val), third);
	change_position(vm, car, OP_BYTE + first + sec + third);
}