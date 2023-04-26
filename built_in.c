#include "shell.h"


/**
 * exit_shell - exit the shell
 * @info: contains usable arguments
 * Return: exits when prompted
 */

int _exit_shell(info_t *info)
{
	int structarg;

	if (info->argv[1])
	{
		structarg = _erratoi(info->argv[1]);

		if (structarg == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');

			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);

}
