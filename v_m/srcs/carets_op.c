//
// Created by Daniil&Ekaterina Naumenko on 05/05/2020.
//

#include "carriages.h"

t_car		*create_caret(int position_on_arena, int id)
{
	t_car		*node;
	
	node = ft_calloc(1, sizeof(t_car));
	node->position = position_on_arena;
	node->id = id;
	node->registers[0] = -id;
	return (node);
}

t_car		*copy_caret(t_car *parent, int32_t position, int32_t id)
{
	t_car		*node;
	
	node = ft_calloc(1, sizeof(t_car));
	ft_memcpy(node, parent, sizeof(t_car));
	node->position = position;
	return(node);
}

void		add_caret(t_car **head, t_car *new_node)
{
	(*head)->prev = new_node;
	new_node->next = *head;
	*head = new_node;
	(*head)->id = (*head)->next->id + 1;
}