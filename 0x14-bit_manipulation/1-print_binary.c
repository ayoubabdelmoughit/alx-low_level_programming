#include "main.h"
/**
 * print_binary - print an unsigned int in binary
 *
 * @n:
 *
 * Return: void
 */
void print_binary(unsigned long int n)
{
	unsigned long int prinbit = 1ul << 63;
	char a = '0';

	while (!(prinbit & n) && prinbit != 0)
		prinbit = prinbit >> 1;

	if (prinbit == 0)
		write(1, &a, 1);

	while (prinbit)
	{
		if (prinbit & n)
			a = '1';
		else
			a = '0';
		write(1, &a, 1);
		prinbit = prinbit >> 1;
	}
}
