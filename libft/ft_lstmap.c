/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:03:48 by vvandenb          #+#    #+#             */
/*   Updated: 2021/10/30 12:26:39 by vvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_mapped;
	t_list	*lst_elem;

	if (!lst && !f && !del)
		return (NULL);
	lst_mapped = NULL;
	while (lst)
	{
		lst_elem = ft_lstnew(f(lst->content));
		if (lst_elem == NULL)
		{
			ft_lstclear(&lst_mapped, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_mapped, lst_elem);
		lst = lst->next;
	}
	return (lst_mapped);
}
