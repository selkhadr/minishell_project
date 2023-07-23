/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:15:33 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/23 14:41:51 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "fd_printf/fd_printf.h"

# define WRIT 1
# define READ 0

enum e_tokens
{
	FILEE,
	CMD,
	ARG,
	S_ARG,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	APPEND_ERROR,
	HEREDOC_ERROR,
};

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_struct
{
	int			exitstatus;
	int			i;
	int			j;
	int			doubleq;
	int			k;
	int			len;
	char		*line;
	char		*expanded;	
	char		*before;
	char		*to_expand;
	char		*str;
	char		*tmp;
	char		*node;
	t_env		*env;
	t_token		*test;
	t_token		*curr;
}	t_struct;

typedef struct s_final
{
	int				*file_types;
	char			**cmds;
	char			**file_names;
	int				fd;
	char			*path;
	int				pip[2];
	pid_t			pid;
	int				prev_pip;
	struct s_final	*next;
}	t_all;

typedef struct	s_export_var
{
	char		*variable;
	char		*var;
	int			i;
	int			j;
	int			k;
}	t_export_var;

extern t_struct	g_glo;

///////////parsing

//storing the environment into linked list
// void	take_env(t_env **all, char **arr);

// void	ft_lstadd_back(t_env **lst, t_env *new);

// t_env	*ft_lstnew(char *content);

//prompt function
void	prompt(t_token **all, t_all **glo, char **envp);

//function to convert the line read from new readline into a new one
//the change is expanding what it should be expanded
//echo hello $USER => echo hello mel-moun (returned)
char	*change_the_line(char *s);
void	handle_characters(char *s);
void	handle_single_quotes(char *s);
void	handle_dollar_signs(char *s);
void	handle_double_quotes(char *s);
void	handle_heredoc(char *s);





char	**mer_split(char *s);


//error of unclosed double/single quotes
// or token near each other as "ls || -la"
int		found_error_one(t_token **all);
int		found_error_two(t_token **all);
void	error_message(int err, t_token **all);

//           the two parts of parsing
//first part creating a helpfull linked list
// to give each node a type (CMD, ARG, FILEE...)
//second part to separate depending on pipe
//so each node will have
// an array of int to store type of redirections
//2d array to store file names of redirections
//2d array of commands and their arguments
void	parsing_part_one(t_token **all, char *expanded);
void	parsing_part_two(t_token **all, t_all **glo);

// parsing utils
void	creating_linked(t_token **all, char *s);
void	delete_first_node(t_token **head);
void	setup_exact_type(t_token **all);
void	remove_for(t_token **all);
void	final_thing(t_token **all, t_all **gb);
t_all	*ft_lst_final(t_token **all);
void	count_redirections(t_token **all, int *count);
int		*take_file_types(t_token **all);
void	count_cmds_args(t_token **all, int *count);
char	**take_cmds(t_token **all);
void	count_files(t_token **all, int *count);
char	**take_file_names(t_token **all);
void	initialization_of_vars(void);
void	take_the_whole_node(char *s, t_token **all);
void	take_arg_heredoc(char *s, t_token **all);
void	take_pipe(t_token **all);
void	take_append(char *s, t_token **all);
void	take_heredoc(t_token **all, char *s);
void	take_the_word(char *s);
void	found_expand(char *s, t_token **all);
void	take_node(t_token **all);
void	treatment(char *s, t_token **all);
void	take_a_lot_expanded(char *s);
void	found_expand(char *s, t_token **all);
void	take_expanded(char *s);
void	take_one_expanded(void);
void	free_tmp_str(void);
void	setup_redirections(t_token **curr);
void	final_thing(t_token **all, t_all **gb);
void	handle_pipe_case(t_token **all, t_all **gb);

//expand
// which is searching the value of a variable in the environment
char	*dollars_money_money(char *s ,int *i, int sp);
int		count_dollar_char(char *s);
int		alphabetic(char c);
char	*expand_exit_status(int count);
void	add_dollar_char(int count);
char	*expand_exit_status(int count);
int		is_digit(char c);
char	*expand_the_var(int count);
char	*expand_normal(int count, int *i);
char	*dollar_then_quotes(int count, char *s);
char	*dollar_then_digit(int count);
char	*expand_arobase(int count, int len, char *s);
char	*expanded_value(char *s);
int		take_alot_expanded_count(char *s);

//some string management
int		empty(char *s);
int		check_single_double(char *s);
char	*mer_substr(char *s, int start, int len);
char	*single_double_quotes(char *s, char c, int *i);
char	*take_word(char *s, int *i);
char	*f_join(char *s1, char *s2);
char	*remove_quotes(char *s);
char	*take_everything(char *s, int *i);
char	*mini_strjoin(char *s, char c);
int		closed_double_quotes(char *s);
char	*arg_heredoc(char *s, int *i);
int		check( char *s);
int		char_belongs_to(char c);
int		char_dont_belong_to(char c);

//linked list management
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back1(t_token **lst, t_token *new);
t_token	*ft_lstnew1(char *content, int value);
void	dollar_lhgar(t_token **all, char *s);
void	deallocating(t_token **ptr);
// void	deallocating_env(t_env **ptr);
void	deallocating1(t_all **ptr);
int		whats_next(int check);
int		syntax_error_first(t_token **all);
void	join_linked_list(t_token **all, t_token **otherall);
void	ft_lstaddback_final(t_all **lst, t_all *new);
void	free_file_names(t_all *pk);
void	free_cmds(t_all *pk);

int	empty_and_not_empty(void);
//to delete
void	print_nodes(t_all *head);
//remember to delete number from functions name

//heredoc_execution file
void	heredoc_fnction(t_all *all);
void	heredoc_fnct_sequel(t_all *all, int *prev, int i);
void	read_fnct(t_all *glo, int *pip, int i);
//redirection_execution file
void	close_pipes(t_all *all);
void	free_double_ptr(char **ptr);
void	use_execve(t_all *all, char **env);
void	close_heredoc(t_all *all);
//out_redirection file
int		creat_outfile(t_all *all);
void	creat_outfile_sequel(t_all *all, int *last, int i);
void	dup_last_out(t_all *tmp, int n);
void	out_redirect(t_all *all);
//in_redctn file
int		check_redirct(t_all *tmp, int flag);
int		last_input(t_all *tmp);
void	in_redirect(t_all *all);
//path_execution file
char	*normal_path(char *cmd, char *path);
void	check_path(t_all *all, char **env);
char	*path_with_slash(char *cmd);
int		check_empty_cmd(char *str);
//builtin_execution file
void	chdir_fnct(t_all *all, int flag);
void	print_env(int flag);
int		only_n_alpha(char *str);
void	echo_fnct(t_all *glo, int flag);
void	unset_fnct(t_all *all, int flag);
void	unset_fnct_sequel(char *variable);
char	*adrs_substr(char *s,  int start, char *t);
void		export_fnct_sequel(t_all *all, int n);
void	export_fnct(t_all *all, int flag);
//execution file
void	pipe_fnct(t_all *all);
int		compare(char *s1, char *s2);
void	use_builtins(t_all *all);
void	execution_fnct_sequel(t_all *all, char **env);
void	execution_fnct(t_all *glo, char **env);
//execution_utils file
int		strncmp_fnct(char *s1, char *s2, int n);
int		use_builtins_sequel_two(t_all *all, int flag);
void	print_error(char *str, char *s2, int flag);
char	**normal_path_sequel(char *str, char *path);
char	*change_heredoc(char *s);
int		ft_strcmp(char *s1, char *s2);
void	handler_fnct(int sig);


int		is_num(char *ptr);
void	exit_fnct(t_all *all);

void    take_env(char **arr);
void    ft_lstadd_back(t_env *new);
t_env    *ft_lstnew(char *content);
int		mer_strncmp(char *ss1, char *ss2, int n);
#endif