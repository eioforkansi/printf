#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Function that prints the value of a pointer variable
 * @types: For list a of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int m = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[m--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	m++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, m, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT_NON_PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int m = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[m] != '\0')
	{
		if (is_printable(str[m]))
			buffer[m + offset] = str[m];
		else
			offset += append_hexa_code(str[m], buffer, m + offset);

		m++;
	}

	buffer[m + offset] = '\0';

	return (write(1, buffer, m + offset));
}

/************************* PRINT_REVERSE *************************/
/**
 * print_reverse - Function  that prints reverse string.
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Numbers of characters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int m, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (m = 0; str[m]; m++)
		;

	for (m = m - 1; m >= 0; m--)
	{
		char z = str[m];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT_A_STRING_IN_ROT13 *************************/
/**
 * print_rot13string - Function that print a string in rot13.
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculations
 * @width: for width
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Numbers of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int mm, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (mm = 0; str[mm]; mm++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[mm])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[mm];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
