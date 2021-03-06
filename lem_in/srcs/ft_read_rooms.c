/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:25:43 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/12 12:02:53 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*ft_find_room(t_room *rooms, char *name)
{
	while (rooms)
	{
		if (ft_strcmp(rooms->name, name) == 0)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

int			ft_read_room(t_farm *farm, char *data)
{
	int		split_count;
	char	**tab;

	ft_lst_add(&(farm->output), data);
	if (!(tab = ft_strsplit(data, ' ')))
		exit(OUT_OF_MEMORY);
	split_count = 0;
	while (tab[split_count])
		split_count++;
	if (split_count == 3)
	{
		ft_add_room(farm, tab);
		farm->rooms_count++;
	}
	else
		ft_free_tab(&tab);
	return (split_count);
}

static int	ft_is_already_links(t_room *r1, t_room *r2)
{
	size_t	i;

	i = 0;
	while (r1->links[i])
	{
		if (r1->links[i] == r2)
			return (1);
		i++;
	}
	return (0);
}

void		ft_link_rooms(t_farm *farm, char *data)
{
	t_room	*r1;
	t_room	*r2;
	char	*defis;

	if (farm->output && ft_strcmp(farm->output->str, data))
		ft_lst_add(&(farm->output), data);
	if (!(defis = ft_strchr(data, '-')) || ft_strchr(data, ' '))
		ft_error_output(farm, "Wrong link room format");
	*defis = '\0';
	r1 = ft_find_room(farm->rooms, data);
	r2 = ft_find_room(farm->rooms, defis + 1);
	if (r1 == NULL || r2 == NULL)
		ft_error_output(farm, "Room`s name doesn`t exist");
	if (r1->links == NULL)
		r1->links = (t_room**)ft_memalloc(sizeof(t_room*) * farm->rooms_count);
	if (r2->links == NULL)
		r2->links = (t_room**)ft_memalloc(sizeof(t_room*) * farm->rooms_count);
	if (!ft_is_already_links(r1, r2))
	{
		r1->links[(r1->degree)++] = r2;
		r1->links[(r1->degree)] = NULL;
		r2->links[(r2->degree)++] = r1;
		r2->links[(r2->degree)] = NULL;
	}
}

int			ft_read_rooms(t_farm *farm, char **data)
{
	int			limit;

	limit = 3;
	while (get_next_line(0, data))
	{
		if (ft_is_comment(*data))
		{
			ft_is_modifer(*data, farm);
			free(*data);
			continue ;
		}
		if (limit == 3)
			limit = ft_read_room(farm, *data);
		if (limit != 3 && limit != 1)
			ft_error_output(farm, "Format line error");
		if (limit == 1)
			ft_link_rooms(farm, *data);
		free(*data);
	}
	if (farm->start == NULL || farm->end == NULL)
		ft_error_output(farm, "No \"start\" or \"end\" room(s)");
	return (1);
}
