#include "main.h"

/************************* PRINT_UNSIGNED_NUMBER *************************/
/**
 * print_unsigned - Function that prints an unsigned number
 * @types: For listing a of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculations
 * @width: for width
 * @precision: For precision specification
 * @size: For size specifying
 * Return: Number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int m = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[m--] = (num % 10) + '0';
		num /= 10;
	}

	m++;

	return (write_unsgnd(0, m, buffer, flags, width, precision, size));
}

/************* PRINT_UNSIGNED_NUMBER_IN_OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width
 * @precision: For precision specification
 * @size: for size specifying
 * Return: Number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int m = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[m--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[m--] = '0';

	m++;

	return (write_unsgnd(0, m, buffer, flags, width, precision, size));
}

/************** PRINT_UNSIGNED_NUMBER_IN_HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: For isting of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @width: for width
 * @precision: For precision specification
 * @size: for size specifying
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT_UNSIGNED_NUMBER_IN_UPPER_HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexidecimal notation
 * @types: For listing of arguments
 * @buffer: For buffer array to handle print
 * @flags:  For active flags Calculation
 * @width: for width
 * @precision: for precision specification
 * @size: For size specifying
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT_HEXX_NUM_IN_LOWER_OR_UPPER **************/
/**
 * print_hexa - Function that prints a hexadecimal number in lower or upper
 * @types: For listing of arguments
 * @map_to: For array of values to map the number to
 * @buffer: For buffer array to handle print
 * @flags:  For active flags calculation
 * @flag_ch: For active flags calculation
 * @width: for width
 * @precision: For precision specification
 * @size: For size specifying
 * @size: For size specifying
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int m = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[m--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[m--] = flag_ch;
		buffer[m--] = '0';
	}

	m++;

	return (write_unsgnd(0, m, buffer, flags, width, precision, size));
}
