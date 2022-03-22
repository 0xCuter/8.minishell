/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:42:27 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/30 11:57:06 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst)
	{
		if ((*lst)->next)
			ft_lstclear(&((*lst)->next), del);
		ft_lstdelone(*lst, del);
	}
	*lst = NULL;
}
