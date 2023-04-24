#include "main.h"

/**
 * get_flag_value - Returns the value for each flag in the format string.
 * @flag_ptr: A pointer to a potential string of flags.
 * @fmt_ptr: A pointer to the current index of the format string.
 * Return: If flag characters are found - a bitwise value of the flags.
 * Otherwise - 0.
*/
unsigned char get_flag_value(const char *flag_ptr, char *fmt_ptr)
{
	int i, k;
	unsigned char flag_result = 0;
	flag_t flag_list[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag_ptr[i]; i++)
	{
		for (k = 0; flag_list[k].flag != 0; k++)
	{
		if (flag_ptr[i] == flag_list[k].flag)
		{
			(*fmt_ptr)++;
			if (flag_result == 0)
				flag_result = flag_list[k].value;
			else
				flag_result |= flag_list[k].value;
			break;
		}
	}
	if (flag_list[k].value == 0)
		break;
	}

	return (flag_result);
}
