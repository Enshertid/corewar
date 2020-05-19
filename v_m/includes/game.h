//
// Created by Daniil&Ekaterina Naumenko on 05/05/2020.
//

#ifndef GAME_H
#define GAME_H

#include "carriages.h"
#include "vm.h"
#include "op.h"

t_car			*check_caret(t_vm *vm, t_car *caret);
t_bool			check_live(t_vm *vm);

t_bool			end_dump(t_vm *vm, t_players *players);
t_bool			end_game(t_players *players);


#endif
