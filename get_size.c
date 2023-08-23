#include "main.h"

/**
 * get_size - Function that calculates the size to cast the argument
 * @format: For formatted string in which to print the arguments
 * @i: For listing of arguments to be printed.
 *
 * Return: S an integer value.
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int s = 0;

	if (format[curr_i] == 'l')
		s = S_LONG;
	else if (format[curr_i] == 'h')
		s = S_SHORT;

	if (s == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (s);
}
