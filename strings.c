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
