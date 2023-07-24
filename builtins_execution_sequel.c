/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution_sequel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:20:31 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/23 22:10:06 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir_fnct(t_all *all, int flag)
{
	char	*tmp;

	tmp = expanded_value("HOME");
	if (!tmp && flag == 1)
	{
		fd_printf(2, "minishell: cd: HOME not set\n");
		g_glo.exitstatus = 1;
		exit (1);
	}
	if (all->cmds[1] == NULL)
		chdir(tmp);
	else if (ft_strncmp(all->cmds[1], "~", ft_strlen(all->cmds[1])) == 0)
		chdir(tmp);
	else
		chdir(all->cmds[1]);
	free (tmp);
	if (flag == 1)
		exit (0);
}

//extern

void	print_env(int flag)
{
	int			i;
	t_env		*tmp;

	i = 0;
	tmp = g_glo.env;
	while (tmp)
	{
		if (ft_strchr(tmp->env, '=') != NULL)
			printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	if (flag == 1)
		exit (0);
}

int	only_n_alpha(char *str)
{
	int	i;

	i = 1;
	if (str == NULL)
		return (1);
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_fnct(t_all *all, int flag)
{
	int	i;

	i = 1;
	while (only_n_alpha(all->cmds[i]) == 0)
	{
		i++;
		flag = 1;
	}
	while (all->cmds[i])
	{
		printf("%s", all->cmds[i]);
		if (all->cmds[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
}
