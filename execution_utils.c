/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:52:08 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 22:12:58 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strncmp_fnct(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (i < n)
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	return (0);
}

int	compare(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	is_num(char *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (0);
	if (ptr[i] == '-' || ptr[i] == '+')
		i++;
	if (ptr[i] == 0)
		return (0);
	else
	{
		while (ptr[i])
		{
			if (!(ptr[i] >= '0' && ptr[i] <= '9'))
				return (0);
			i++;
		}
	}
	return (1);
}

void	exit_norm(t_all *all)
{
	if (all->cmds[1] == NULL)
	{
		printf("exit\n");
		exit (0);
	}
	if (is_num(all->cmds[1]) && !all->cmds[2])
	{
		printf("exit\n");
		exit (ft_atoi(all->cmds[1]));
	}
}

void	exit_fnct(t_all *all)
{
	int	i;

	i = 0;
	exit_norm(all);
	if (all->cmds[2] != NULL)
	{
		print_error(NULL, "exit\nminishell: exit: too many arguments\n", 0);
		exit (1);
	}
	while (all->cmds[1][i])
	{
		if (!(all->cmds[1][i] >= '0' && all->cmds[1][i] <= '9'))
		{
			fd_printf(2, "exit\nminishell: exit: ");
			print_error(all->cmds[1], ": numeric argument required\n", 0);
			exit (1);
		}
		i++;
	}
}
