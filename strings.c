#include "main.h"

/**
 * store_string - Stores an argument as a string to a buffer contained.
 * @args: A va_list pointing to the argument to be stored.
 * @output: A buffer_t struct containing a character array.
 * @flags: format_flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int store_string(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len)
{
	char *str_arg, *null_str = "(null)";
	int str_size;
	unsigned int stored = 0;

	(void)format_flags;
	(void)len;

	str_arg = va_arg(args, char *);
	if (str_arg == NULL)
		return (_memcpy(output, null_str, 6));

	for (str_size = 0; *(str_arg + str_size);)
		str_size++;

	stored += print_string_width(output, format_flags, wid, prec, str_size);

	prec = (prec == -1) ? str_size : prec;
	while (*str_arg != '\0' && prec > 0)
	{
		stored += _memcpy(output, str_arg, 1);
		prec--;
		str_arg++;
	}

	stored += print_neg_width(output, stored, format_flags, wid);

	return (stored);
}

/**
 * convert_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: format_flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int ret = 0;

	(void)format_flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_string_width(output, format_flags, wid, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		ret += _memcpy(output, (str + end), 1);
		end--;
	}

	ret += print_neg_width(output, ret, format_flags, wid);

	return (ret);
}

/**
 * convert_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be converted.
 * @flags: format_flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A lenth modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int ret = 0;

	(void)format_flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_string_width(output, format_flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; *(str + i) != '\0' && i < prec; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				ret += _memcpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			ret += _memcpy(output, (str + i), 1);
	}

	ret += print_neg_width(output, ret, format_flags, wid);

	return (ret);
}

/**
 * convert_S - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: fotmat_flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */

unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;

	(void)len;
	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	ret += print_string_width(output, format_flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (index = 0; *(str + index) != '\0' && index < prec; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			ret += _memcpy(output, hex, 2);
			if (*(str + index) < 16)
				ret += _memcpy(output, &zero, 1);
			ret += convert_ubase(output, *(str + index),
					"0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		ret += _memcpy(output, (str + index), 1);
	}

	ret += print_neg_width(output, ret, format_flags, wid);

	return (ret);
}
