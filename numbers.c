#include "main.h"

/**
 * convert_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output_buffer: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_di(va_list args, buffer_t *output_buffer,
		unsigned char flags, int width, int precision, unsigned char length)
{
	long int number;
	unsigned int bytes_stored = 0;
	char padding_char;

	if (length == LONG)
		number = va_arg(args, long int);
	else
		number = va_arg(args, int);
	if (length == SHORT)
		number = (short)number;

	if (SPACE_FLAG == 1 && number >= 0)
		bytes_stored += _memcpy(output_buffer, " ", 1);

	if (precision <= 0 && NEG_FLAG == 0)
	{
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && number >= 0)
			bytes_stored += _memcpy(output_buffer, "+", 1);
		if (ZERO_FLAG == 1 && number < 0)
			bytes_stored += _memcpy(output_buffer, "-", 1);

		padding_char = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= get_digit_count(number); width > 0; width--)
			bytes_stored += _memcpy(output_buffer, &padding_char, 1);
	}

	if (ZERO_FLAG == 0 && number < 0)
		bytes_stored += _memcpy(output_buffer, "-", 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && number >= 0))
		bytes_stored += _memcpy(output_buffer, "+", 1);

	if (!(number == 0 && precision == 0))
		bytes_stored += convert_sbase(output_buffer, number, "0123456789",
				flags, 0, precision);
	bytes_stored += print_neg_width(output_buffer, bytes_stored, flags, width);
	return (bytes_stored);
}

/**
 * get_digit_count - Returns the number of digits in a long int
 * @number: The number to count
 *
 * Return: The number of digits
 */
static inline unsigned int get_digit_count(long int number)
{
	unsigned int count = 0;

	if (number == LONG_MIN)
		return (19);

	for (number = (number < 0) ? -number : number; number > 0; number /= 10)
		count++;

	count += (number == 0) ? 1 : 0;
	count += (number < 0) ? 1 : 0;
	count += (PLUS_FLAG == 1 && number >= 0) ? 1 : 0;
	count += (SPACE_FLAG == 1 && number >= 0) ? 1 : 0;

	return (count);
}

/**
 * convert_binary - Converts an unsigned int argument to binary
 * and stores it to a buffer contained in a struct.
 * @params: A va_list pointing to the argument to be converted.
 * @modifiers: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @buffer: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int convert_binary(va_list params, buffer_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char length)
{
	unsigned int number;

	number = va_arg(params, unsigned int);
	(void)length;
	return (convert_ubase(buffer, number, “01”, modifiers, width, precision));
}
