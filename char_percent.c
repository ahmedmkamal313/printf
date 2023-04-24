/**
 * ConvertChar - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @arguments: A va_list pointing to the argument to be converted.
 * @buffer: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int ConvertChar(va_list arguments, buffer_t *buffer,
		unsigned char flags, int width, int precision, unsigned char length)
{
	char character;
	unsigned int bytes = 0;

	(void)precision;
	(void)length;

	character = va_arg(arguments, int);

	bytes += print_width(buffer, bytes, flags, width);
	bytes += _memcpy(buffer, &character, 1);
	bytes += print_neg_width(buffer, bytes, flags, width);

	return (bytes);
}
