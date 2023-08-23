#include "main.h"

/************************* PRINT_CHAR *************************/

/**
 * print_char - User defined fucntion for printing characters
 * @types: For list a of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculations
 * @width: For width
 * @precision: For precision specification
 * @size: for size specifying
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char s = va_arg(types, int);

	return (handle_write_char(s, buffer, flags, width, precision, size));
}
/************************* PRINT_A_STRING *************************/
/**
 * print_string - User defined function for printing a string
 * @types: For list a of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width.
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT_PERCENT_SIGN *************************/
/**
 * print_percent - User defined function for printing a percent sign
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width.
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT_INT *************************/
/**
 * print_int - User defined function for printing integer
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width.
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/************************* PRINT_BINARY *************************/
/**
 * print_binary - User defined function for printing an unsigned number
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width.
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Numbers of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, j, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (j = 1; j < 32; j++)
	{
		m /= 2;
		a[j] = (n / m) % 2;
	}
	for (j = 0, sum = 0, count = 0; j < 32; j++)
	{
		sum += a[j];
		if (sum || j == 31)
		{
			char z = '0' + a[j];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
