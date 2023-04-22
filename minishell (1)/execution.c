#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>


char	*get_next_line(int fd)
{
	char	line[8000000];
	char	buf;
	int		i;

	i = 0;
	write(0, "> ", 2);
	while (read(fd, &buf, 1) == 1)
	{
		line[i++] = buf;
		if (buf == '\n')
			break ;
	}
	line[i] = '\0';
	if (!line[0])
		return (NULL);
	return (strdup(line));
}

char *find_path(char *command, char **envp)
{
    char *path,  *temp;
    int len;

    path = getenv("PATH");
    if (path == NULL)
        return NULL;
    path = strtok(path, ":");
    while (path != NULL)
    {
        temp = (char *) malloc(ft_strlen(path) + ft_strlen(command) + 2);
        strcpy(temp, path);
        strcat(temp, "/");
        strcat(temp, command);
        if (access(temp, X_OK) == 0)
            return temp;
        free(temp);
        path = strtok(NULL, ":");
    }
    ft_perror("command not found: ", command, NULL);
    g_data.exit_status = 127;
    exit (127);
}

void    exec_redout_redin(t_red *red, int output_fd, int input_fd)
{
    if (red->type == REDOUT)
    {
        output_fd = open(red->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (output_fd == -1)
            file_error();
        dup2(output_fd, 1);
        close(output_fd);
    }
    else
    {
        input_fd = open(red->filename, O_RDONLY, 0);
        if (input_fd == -1)
            file_error();
        dup2(input_fd, 0);
        close(input_fd);
    }
}

void    file_error(void)
{
    perror("open");
    exit(EXIT_FAILURE);
}

// void    exec_here_doc(t_red *red, int output_fd, int input_fd)
// {
//     char    *line;
//     int        fds[2];

//     while (red && red->type == HERDOC)
//     {
//         close(fds[1]);
//         close(fds[0]);
//         if (pipe(fds) < 0)
//             file_error();
//         while (1)
//         {
//             write(0, "> ", 2);
//             line = readline("");

//             if (strncmp(line, red->filename, ft_strlen(line)) == 0)
//                 break;
//             if(strchr(line, '$'))
//                 line = exp_var_env(line + 1);
//             write(fds[1], line, ft_strlen(line));
//             write(fds[1], "\n", 1);
//         }
//          red = red->next;
//     }
//     close(fds[1]);
//     dup2(fds[0], 0);
//     close(fds[0]);
// }


void    exec_here_doc(t_red **red, int output_fd, int input_fd)
{
    char    *input;

    while ((*red) && (*red)->type == HERDOC)
    {
        output_fd = open("/tmp/.minishell_tmp",
		O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
        if (output_fd == -1)
            file_error();
        input = get_next_line(STDIN_FILENO);
        while (input && strncmp(input, (*red)->filename, ft_strlen((*red)->filename)) != 0)
        {
            write(output_fd, input, ft_strlen(input));
            input = get_next_line(STDIN_FILENO);
        }
        if (!(*red)->next || (*red)->next->type != HERDOC)
            break;
        (*red) = (*red)->next;
    }
    close(output_fd);
    input_fd = open("/tmp/.minishell_tmp", O_RDONLY, 0);
    dup2(input_fd, 0);
    close(input_fd);
}

void    exec_redap(t_red *red, int output_fd, int input_fd)
{
    output_fd = open(red->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (output_fd == -1)
        file_error();
    dup2(output_fd, 1);
    close(output_fd);
}

void exec_red(t_red *red, t_smpl_cmd *cmd)
{
    while (red)
    {
        int input_fd;
        int output_fd; 

        input_fd = cmd->fd.in;
        output_fd = cmd->fd.out;        
        if (red->type == REDOUT || red->type == REDIN)
            exec_redout_redin(red, output_fd, input_fd);
        else if (red->type == REDAP)
            exec_redap(red, output_fd, input_fd);
        else if (red->type == HERDOC)
        {
            if (cmd->command == NULL)
                cmd->command = strdup("cat");
            exec_here_doc(&red, output_fd, input_fd);
        }
        red = red->next;
    }
}

int    exec_command(t_smpl_cmd *cmd, char **env)
{
    t_arg   *arg = cmd->arg;
    char **args;
    int i = 0;
    if (!strchr(cmd->command, '/'))
        cmd->command = find_path(cmd->command, env);
    if (!cmd->command)
    {
        g_data.exit_status = 127;
        exit(127);
    }
    args[i++] = cmd->command;
    while (arg)
    {
        args[i++] = arg->args;
        arg = arg->next;
    }
    args[i] = NULL;
    if (execve(cmd->command, args, env) == -1)
    {
        ft_perror("no such file or directory: ", cmd->command, NULL);
        exit(127);
    }
    return (0);
}

void execute_simple_command(t_smpl_cmd *cmd, char **env) 
{
    t_arg *arg = cmd->arg;
    t_red *red = cmd->red;
    int pid;
    int p = 0;
    g_data.exit_status = 0;

    pid = fork();
    if (pid == 0)
    {
        if(red)
            exec_red(red, cmd);
        if(cmd->command)
        exec_command(cmd, env);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &g_data.exit_status, 0);
        // printf("exit status: %d\n", WEXITSTATUS(g_data.exit_status));
    }
    else
    {
        g_data.exit_status = 1;
        perror("fork");
    }
}

void    exec_child(int *fd, t_smpl_cmd *smpl_cmd, char **env)
{
    close(fd[0]);
    dup2(fd[1], 1);
    execute_simple_command(smpl_cmd, env);
    // close(fd[1]);
    exit(0);
}

void execute_piped_command(t_pipe_line *pipeline, char **env)
{
    int fd[2];
    int i;
    pid_t pid;
    t_smpl_cmd *smpl_cmd = pipeline->smpl_cmd;

    i = -1;
    while (++i < pipeline->nb_smpl_cmds - 1)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
            exec_child(fd, smpl_cmd, env);
        else if (pid > 0)
        {
            close(fd[1]);
            dup2(fd[0], 0);
            waitpid(pid, &g_data.exit_status, 0);
        }
        else
            perror("fork");
        smpl_cmd = smpl_cmd->next;
    }
    execute_simple_command(smpl_cmd, env);
}
