/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_farm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:10:03 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/08 20:04:00 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_read_ants_count(t_farm *farm, char **data)
{
	size_t	i;

	while (get_next_line(0, data) == 1)
	{
		ft_lst_add(&farm->output, *data);
		if (ft_is_comment(*data))
		{
			ft_memdel((void**)data);
			continue ;
		}
		break ;
	}
	if (*data == NULL)
		ft_error_output(farm, "No input data");
	i = 0;
	while ((*data)[i])
	{
		if (!(ft_isdigit((*data)[i++])))
			ft_error_output(farm, "Wrong format for ants count");
	}
	farm->ants_count = (size_t)ft_atoi(*data);
	if (farm->ants_count > INT_MAX)
		ft_error_output(farm, "Integer owerflow");
	ft_ants_generator(farm);
	free(*data);
}

int				ft_is_comment(char *input_data)
{
	if (input_data)
	{
		if (input_data[0] == '#')
			return (1);
	}
	return (0);
}

t_farm			*ft_init_farm(void)
{
	t_farm	*farm;
	char	*input_data;

	input_data = NULL;
	farm = ft_create_farm();
	ft_read_ants_count(farm, &input_data);
	ft_read_rooms(farm, &input_data);
	ft_rooms_reverse(&farm->rooms);
	return (farm);
}
