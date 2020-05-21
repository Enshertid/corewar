/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego  <ediego@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 19:21:59 by enshertid         #+#    #+#             */
/*   Updated: 2020/05/20 00:02:56 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

static bool			valid_aff(t_pars *pars, t_players *players)
{
	pars->i++;
	if (!players->aff)
		players->aff = true;
	else
		ft_error("second aff flag", "valid aff", 2);
	return (true);
}

static void			finish_players(t_players *players, int8_t new_size)
{
	t_player	**new_array;
	
	players->iter = 0;
	players->size = new_size;
	new_array = ft_calloc(new_size, sizeof(t_player*));
	while(players->iter != new_size)
	{
		new_array[players->iter] = players->arr[players->iter];
		players->iter++;
	}
	free(players->arr);
	players->arr = new_array;
}

static void			init_pars(t_pars *pars, int ac, char **av)
{
	ft_memset(pars, 0, sizeof(t_pars));
	pars->ac = ac;
	pars->av = av;
	pars->i = 1;
}

void				parsing(t_players *players, int ac, char **av)
{
	t_pars		pars;
	
	init_pars(&pars, ac, av);
	if (pars.ac < 2)
		ft_error("Have no champions", NULL, 1);
	else if (pars.ac > (MAX_PLAYERS * 3) + DUMP)
		ft_error("To many arguments", NULL, 1);
	while (pars.i < pars.ac)
	{
		if (ft_strequ(pars.av[pars.i], "-dump") && valid_dump(&pars, players))
			continue ;
		if (ft_strequ(pars.av[pars.i], "-a") && valid_aff(&pars, players))
			continue ;
		else if (ft_strequ(pars.av[pars.i], "-n"))
			valid_flag(&pars, players);
		else
			valid_name(&pars, players);
		pars_champ(&pars, players);
	}
	if (players->iter == 0)
		ft_error("Have no champions", NULL, 2);
	validate_id(players);
	if (players->iter != players->size)
		finish_players(players, players->iter);
}
