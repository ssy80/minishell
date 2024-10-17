#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int	ft_plen(char *str, int i)
{
	if (!str)
		return (ft_plen("(null)", 0));
	if (!*str)
		return (i);
	write(1, str, 1);
	return (ft_plen(str + 1, i + 1));
}

int	putnum(long num, int base)
{
	char	*b;

	b = "0123456789abcdef";
	if (num < 0)
		return (putnum(-1 * num, base) + write(1, "-", 1));
	if (num / base == 0)
		return (write(1, &b[num % base], 1));
	return (putnum(num / base, base) + putnum(num % base, base));
}

// <STR> -> <ALLCHAR><STR><PSTR><PNUM><PHEX> | EMPTY
int	ptf(char *str, int i, int n, va_list args)
{
	if (!str[i])
		return (n);
	// <PSTR> -> <STR>%s<STR>
	if (str[i] == '%' && str[i + 1] == 's')
		return (ptf(str, i + 2, n + ft_plen(va_arg(args, char *), 0), args));
	// <PNUM> -> <STR>%d<STR>
	if (str[i] == '%' && str[i + 1] == 'd')
		return (ptf(str, i + 2, n + putnum(va_arg(args, int), 10), args));
	// <PHEX> -> <STR>%x<STR>
	if (str[i] == '%' && str[i + 1] == 'x')
		return (ptf(str, i + 2, n + putnum(va_arg(args, int), 16), args));
	write(1, &str[i], 1);
	return (ptf(str, i + 1, n + 1, args));
}

int	ft_printf(char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	count = ptf(str, 0, 0, args);
	va_end(args);
	return (count);
}

/* 
grammar
<ALLCHAR> -> .* (any ascii character) | EMPTY
START -> <STR>
<STR> -> <ALLCHAR><STR><PSTR><PNUM><PHEX> | EMPTY
<PSTR> -> <STR>%s<STR> | EMPTY
<PNUM> -> <STR>%d<STR> | EMPTY
<PHEX> -> <STR>%x<STR> | EMPTY
 */
// int main(void)
// {
// 	int a = ft_printf("%s0123456789%s%x\n","HAHA","abc",58976232);
// 	printf("%d\n", a);
// 	int b =  ft_plen("abc",0);
// 	printf("%d\n", b);
// 	int c = ft_printf("abbc%s %d\n", NULL,55);
// 	printf("%d\n",c);
// }