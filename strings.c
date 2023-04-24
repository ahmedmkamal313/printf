#include "main.h"

/**
 * store_string - Stores an argument as a string to a buffer contained.
 * @args: A va_list pointing to the argument to be stored.
 * @output: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int store_string(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str_arg, *null_str = "(null)";
	int str_size;
	unsigned int stored = 0;

	(void)flags;
	(void)len;

	str_arg = va_arg(args, char *);
	if (str_arg == NULL)
		return (_memcpy(output, null_str, 6));

	for (str_size = 0; *(str_arg + str_size);)
		tr_size++;

	stored += print_string_width(output, flags, wid, prec, str_size);

	prec = (prec == -1) ? str_size : prec;
	while (*str_arg != '\0' && prec > 0)
	{
		stored += _memcpy(output, str_arg, 1);
		prec–;
		str_arg++;
	}

	stored += print_neg_width(output, stored, flags, wid);

	return (stored);
}

/**
 * convert_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_string_width(output, flags, wid, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		ret += _memcpy(output, (str + end), 1);
		end--;
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
