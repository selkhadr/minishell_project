/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution_sequel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:20:31 by selkhadr          #+#    #+#             */
/*   Updated: 2023/07/25 11:42:34 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(void)
{
	t_env	*tmp;
	char	pwd[1000];
	char	*var;

	var = NULL;
	tmp = g_glo.env;
	getcwd(pwd, PATH_MAX);
	while (tmp->env)
	{
		var = adrs_substr(tmp->env, 0, ft_strchr(tmp->env, '='));
		if (compare(var, "PWD") == 0)
		{
			free (tmp->env);
			tmp->env = NULL;
			free (var);
			tmp->env = ft_strjoin("PWD=", pwd);
			break ;
		}
		free (var);
		var = NULL;
		tmp = tmp->next;
	}
}

void	chdir_fnct(t_all *all, int flag)
{
	char	*tmp;

	tmp = expanded_value("HOME");
	if (all->cmds[1] == NULL || !compare(all->cmds[1], "~"))
	{
		if (!tmp && flag == 1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_glo.exitstatus = 1;
			exit (1);
		}
		chdir (tmp);
		change_pwd();
	}
	else
	{
		chdir(all->cmds[1]);
		change_pwd();
	}
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
	int	fg;

	i = 1;
	fg = 0;
	while (only_n_alpha(all->cmds[i]) == 0)
	{
		i++;
		fg = 1;
	}
	while (all->cmds[i])
	{
		ft_putstr_fd(all->cmds[i], 1);
		if (all->cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (fg == 0)
		write (1, "\n", 1);
	if (flag == 1)
		exit (0);
}
