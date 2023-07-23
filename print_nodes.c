/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moun <mel-moun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:07:07 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/14 12:00:47 by mel-moun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nodes(t_all *head)
{
	t_all	*current;
	int		p;
	int		i;

	current = head;
	p = 1;
	i = 0;
	while (current != NULL)
	{
		printf("----------Node %d-----------\n", p++);
		printf("File Types AND Files : ");
		if (current->file_names == NULL)
			printf("(null)");
		else
		{
			i = 0;
			while (current->file_names[i] != NULL)
			{
				printf("\n[%d] %s", current->file_types[i], current->file_names[i]);
				i++;
			}
		}
		printf("\n");
		printf("Commands: ");
		if (current->cmds == NULL)
			printf("(null)");
		else
		{
			i = 0;
			while (current->cmds[i] != NULL)
			{
				printf("[%s] ", current->cmds[i]);
				i++;
			}
		}
		printf("\n\n");
		current = current->next;
	}
}
