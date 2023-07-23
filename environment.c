/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:23:21 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/21 15:24:19 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	take_env(t_env **all, char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		ft_lstadd_back(all, ft_lstnew(arr[i]));
// 		i++;
// 	}
// }

// void	ft_lstadd_back(t_env **lst, t_env *new)
// {
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	while ((*lst)->next != NULL)
// 		lst = &(*lst)->next;
// 	(*lst)->next = new;
// }

// t_env	*ft_lstnew(char *content)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->env = ft_strdup(content);
// 	node->next = NULL;
// 	return (node);
// }
