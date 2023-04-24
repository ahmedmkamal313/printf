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
/**
 * get_length_value - Returns the value for each length
 * modifier in the format string.
 * @mod_ptr: A pointer to a possible length modifier.
 * @fmt_ptr: A pointer to the current index of the format string.
 * Return: If a length modifier is found - its corresponding value.
 *  Otherwise - 0.
*/
unsigned char get_length_value(const char *mod_ptr, char *fmt_ptr)
{
	if (*mod_ptr == ‘h’)
	{
		(*fmt_ptr)++;
		return (SHORT);
	}

	else if (*mod_ptr == 'l')
	{
		(*fmt_ptr)++;
		return (LONG);
}

	return (0);
}

/**
 * get_width_value - Returns the value for a width modifier
 * in the format string.
 * @args: A va_list of arguments.
 * @mod_ptr: A pointer to a possible width modifier.
 * @fmt_ptr: A pointer to the current index of the format string.
 * Return: If a width modifier is found - its value.
 * Otherwise - 0.
*/
int get_width_value(va_list args, const char *mod_ptr, char *fmt_ptr)
{
	int wid_value = 0;

	while ((*mod_ptr >= '0' && *mod_ptr <= '9') || (*mod_ptr == '*'))
	{
		(*fmt_ptr)++;

		if (*mod_ptr == '*')
		{
			wid_value = va_arg(args, int);
			if (wid_value <= 0)
				return (0);
			return (wid_value);
		}
		wid_value *= 10;
		wid_value += (*mod_ptr - '0');
		mod_ptr++;
	}

	return (wid_value);
}
