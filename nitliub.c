#include "shell.h"

/**
 * _myexit – shell exits in code 
 * @infor: the Structure containing arguments. maintain function prototype
 * constant function prototype.
 * Return: return exit with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *infor)
{
	int exit;

	if (infor->argv[1]) /* If there is an exit arguement */
	{
		exit = _erratoi(infor->argv[1]);
		if (exit == -1)
		{
			infor->status = 2;
			print_error(infor, "Illegal number: ");
			_eputs(infor->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infor->err_num = _erratoi(infor->argv[1]);
		return (-2);
	}
	infor->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory
 * @info: the struct has potential arguments for prototype
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *h, *dir, buffer[1024];
	int chdir_ret;

	h = getcwd(buffer, 1024);
	if (!h)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(h);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process in code
 * @inform: Structure having potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *inform)
{
	char **arg_array;

	arg_array = inform->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp unused workaround */
	return (0);
}

