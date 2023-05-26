#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct in code
 * @avr: the argument vector from main() in code
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **avr)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, avr);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @infor: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully in code ,
 * 1 if builtin found but not successful in code ,
 * 2 if builtin signals exit() in code
 */
int find_builtin(info_t *infor)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infor->argv[0], builtintbl[i].type) == 0)
		{
			infor->line_count++;
			built_in_ret = builtintbl[i].func(infor);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @infor: the parameter & return info struct in code
 *
 * Return: void
 */
void find_cmd(info_t *infor)
{
	char *path = NULL;
	int i, k;

	infor->path = infor->argv[0];
	if (infor->linecount_flag == 1)
	{
		infor->line_count++;
		infor->linecount_flag = 0;
	}
	for (i = 0, k = 0; infor->arg[i]; i++)
		if (!is_delim(infor->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infor, _getenv(infor, "PATH="), infor->argv[0]);
	if (path)
	{
		infor->path = path;
		fork_cmd(infor);
	}
	else
	{
		if ((interactive(infor) || _getenv(infor, "PATH=")
					|| infor->argv[0][0] == '/') && is_cmd(infor, infor->argv[0]))
			fork_cmd(infor);
		else if (*(infor->arg) != '\n')
		{
			infor->status = 127;
			print_error(infor, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @infor: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *infor)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
		{
			free_info(infor, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infor->status));
		if (WIFEXITED(infor->status))
		{
			infor->status = WEXITSTATUS(infor->status);
			if (infor->status == 126)
				print_error(infor, "Permission denied\n");
		}
	}
}

