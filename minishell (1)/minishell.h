#ifndef MISH_H
#define MISH_H

 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>
 #include <stdlib.h>
 #include <sys/wait.h>
 #include <fcntl.h>
 #include <signal.h>
 #include <readline/history.h>
 #include <readline/readline.h>


typedef enum {
    WORD,
    PIPE,
    PARENTHESIS,
    REDIRECTION,
    AND,
    SEMI,
    N_LINE,
    REDIN,
    REDOUT,
    REDAP,
    SQ_WORD,
    DQ_WORD,
    ENV,
    HERDOC,
} e_type;

typedef struct s_var {
    int i;
    int start;
}   t_var;

typedef struct s_token {
    char *value;
    e_type type;
    struct s_token *next;
}   t_token;

typedef struct s_red {
    int     type;
    char    *filename;
    struct s_red   *next;
}   t_red;

typedef struct s_arg {
    char    *args;
    struct s_arg   *next;
}   t_arg;

typedef struct s_fd {
    int in;
    int out;
}   t_fd;

typedef struct s_smpl_cmd {
    char    *command;
    int     nb_args;
    int     nb_reds;
    t_arg   *arg;
    t_red   *red;
    t_fd    fd;
    struct s_smpl_cmd  *next;
}   t_smpl_cmd;

typedef struct s_pipe_line
{
    int nb_smpl_cmds;
    t_smpl_cmd  *smpl_cmd;
    struct s_pipe_line *next;
}   t_pipe_line;

typedef struct s_ast 
{
    int nb_pipe_lines;
    t_pipe_line *pipe_line;
}   t_ast;


typedef struct s_data {
    int exit_status;
    int last_exit_status;
}   t_data;
t_data  g_data;

/////  lexer  ////
int	ft_strlen(char *str);
int ft_is_special(char c);
int ft_is_specials(char c);
void    handle_delimiters(t_token **head, t_var *var, char *input, t_token **current);
int ft_is_redirection(t_token *token);
int ft_is_word(char c);
t_token *ft_new_token(char *str, int type);
t_token *lexer(char *input);

t_red    *create_red_node(t_red *red, t_token **token);
void    ft_add_red(t_smpl_cmd *cmd, t_token **token);
t_arg	*create_arg_node(t_token **token);    
void    add_args(t_smpl_cmd *smpl_cmd, t_token **token);
t_smpl_cmd	*ft_init_simple_cmd(void);
t_smpl_cmd  *create_smpl_cmd(t_token **token);
t_pipe_line	*init_pipe_line(t_pipe_line *pipeline);
t_pipe_line	*create_pipe_line(t_token **token);
t_ast	*init_ast(t_ast *ast);
t_ast	*create_ast(t_token **token);

void    ft_error(char *str);
int check_nb_quotes(char   *input);
int syntax_error(t_token *token);
int ft_is_digit(char c);
int ft_isalpha(char c);
int	ft_readline(char **line);
int	ft_isspace(char c);
int	ft_strisspace(char *str);
char	*ft_strjoin(char *str1, char *str2);
int	ft_perror(char *msg, char *utils, char *s);
void    file_error(void);
void    echo(char **arg);


t_token    *ft_expand(t_token **token);
char	*exp_var_env(char	*dollar);

int ft_execute(t_smpl_cmd *cmd, char **env);
char    **cmd_to_arr(t_smpl_cmd *cmd);
char	*get_next_line(int fd);

void execute_simple_command(t_smpl_cmd *cmd, char **env);
void execute_piped_command(t_pipe_line *pipeline, char **env);

void	handle_signals(int signo);

#endif