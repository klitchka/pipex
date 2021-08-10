/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaparici <aaparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:00:56 by aaparici          #+#    #+#             */
/*   Updated: 2021/08/10 18:33:12 by aaparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**sh_cmd(char **argv, int n_cmd)
{
	char	**cmd;
	size_t	cmd_len;

	cmd = malloc(sizeof(char **) * 4);
	if_e(!cmd, ENOMEM, "malloc() failed.\nError");
	cmd[0] = NULL;
	cmd_len = ft_strlen(argv[n_cmd + 2]) + 1;
	cmd[0] = malloc(sizeof(char *) * 8);
	if_e(cmd[0] == NULL, ENOMEM, "malloc() failed.\nError");
	ft_strlcpy(cmd[0], "/bin/sh", 8);
	cmd[1] = malloc(sizeof(char *) * 3);
	if_e(cmd[1] == NULL, ENOMEM, "malloc() failed.\nError");
	ft_strlcpy(cmd[1], "-c", 3);
	cmd[2] = malloc(sizeof(char *) * cmd_len);
	if_e(cmd[2] == NULL, ENOMEM, "malloc() failed.\nError");
	ft_strlcpy(cmd[2], argv[n_cmd + 2], cmd_len);
	cmd[3] = NULL;
	return (cmd);
}

void	child_process(int outfile, char ***argv_env, int n_cmd, int *pfd)
{
	char	**cmd;
	char	**argv;
	char	**env;

	argv = argv_env[0];
	env = argv_env[1];
	cmd = NULL;
	if (n_cmd == 0)
		if_e(dup2(pfd[1], STDOUT_FILENO) == -1, errno, "dup2() failed.\nError");
	else
	{
		if_e(dup2(pfd[0], STDIN_FILENO) == -1, errno, "dup2() failed.\nError");
		if_e(dup2(outfile, STDOUT_FILENO) == -1, errno, "dup2() failed.\nError");
	}
	cmd = sh_cmd(argv, n_cmd);
	if_e(execve(cmd[0], cmd, env) == -1,
		errno, "execve() failed.\nError");
	free(cmd);
}

void	parent_process(int n_cmd, int *pfd, pid_t pids)
{
	int		status;

	if (n_cmd == 0)
		close(pfd[1]);
	if (n_cmd == 1)
		close(pfd[0]);
	if_e(waitpid(pids, &status, 0) == -1,
		errno, "wait() failed.\nError");
	if (WIFEXITED(status) != 0
		&& WEXITSTATUS(status) != 0
		&& n_cmd == 1)
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	int		infile;
	int		outfile;
	int		pfd[2];
	int		n_cmd;
	pid_t	pids;

	if_e(argc != 5, EINVAL,
		"usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\nError");
	if_e(close(STDIN_FILENO) == -1, errno, "close() failed.\nError");
	infile = open(argv[1], O_RDONLY);
	if_e((errno == EACCES || errno == ENOENT), errno, "");
	outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if_e(errno == EACCES, errno, "");
	if_e(pipe(pfd) == -1, errno, "pipe() failed.\nError");
	n_cmd = 0;
	while (n_cmd < 2)
	{
		pids = fork();
		if_e(pids < 0, errno, "fork() fail.\nError");
		if (pids == 0)
			child_process(outfile, (char **[2]){argv, env}, n_cmd, pfd);
		parent_process(n_cmd, pfd, pids);
		n_cmd++;
	}
	return (EXIT_SUCCESS);
}
