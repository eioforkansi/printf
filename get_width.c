#include "main.h"

/**
 * get_width - Function that calculates the width for printing
 * @format: For formatted string in which to print the arguments.
 * @i: For listing of arguments to be printed.
 * @list: For listing of arguments.
 *
 * Return: W an integer.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int w = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			w *= 10;
			w += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (w);
}
