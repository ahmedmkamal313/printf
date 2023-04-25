#include "main.h"

/**
 * cleanup - Peforms cleanup operations for _printf.
 * @arg_list: A va_list of arguments provided to _printf.
 * @buffer: A buffer_t struct containing the output string.
 */
void cleanup(va_list arg_list, buffer_t *buffer)
{
	va_end(arg_list);
	write(1, buffer->start, buffer->len);
	free_buffer(buffer);
}

/**
 * run_printf - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @arg_list: A va_list of arguments.
 * int - i
 * Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list arg_list, buffer_t *output)
{
	int index, width, precision, result = 0;
	char offset;
	unsigned char flags, length;
	unsigned int (*converter)(va_list, buffer_t *, unsigned char,
			int, int, unsigned char);

	for (index = 0; *(format + index); index++)
	{
		length = 0;
		if (*(format + index) == '%')
		{
			offset = 0;
			flags = handle_flags(format + index + 1, &offset);
			width = handle_width(arg_list, format + index + offset + 1, &offset);
			precision = handle_precision(arg_list, format + index + offset + 1,
					&offset);
			length = handle_length(format + index + offset + 1, &offset);

			converter = handle_specifiers(format + index + offset + 1);
			if (converter != NULL)
			{
				index += offset + 1;
				result += converter(arg_list, output, flags, width, precision, length);
				continue;
			}
			else if (*(format + index + offset + 1) == '\0')
			{
				result = -1;
				break;
			}
		}
		result += _memcpy(output, (format + index), 1);
		index += (length != 0) ? 1 : 0;
	}
	cleanup(arg_list, output);
	return (result);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *buffer;
	va_list arg_list;
	int result;

	if (format == NULL)
		return (-1);
	buffer = init_buffer();
	if (buffer == NULL)
		return (-1);

	va_start(arg_list, format);

	result = run_printf(format, arg_list, buffer);

	return (result);
}
