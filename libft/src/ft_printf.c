/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 00:42:19 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/07 10:09:32 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "../header/libft.h"

static char			*flagger(char *flags);
static int			sorter(int fd, char *flags, va_list args);
static int			executer(int fd, char *s, va_list args);

// Replicates printf behaviour
int	ft_printf(int fd, const char *s, ...)
{
	va_list	args;
	int		count;
	int		varlen;

	count = 0;
	va_start(args, s);
	while (*s != '\0')
	{
		while (*s == '%')
		{
			varlen = executer(fd, (char *)s, args);
			if (varlen < 0)
				return (0);
			s = s + 2;
			count = count + varlen;
		}
		if (*s != '\0')
		{
			ft_putchar_fd(*s, fd);
			count++;
			s++;
		}
	}
	va_end(args);
	return (count);
}

static int	executer(int fd, char *s, va_list args)
{
	char	*realflags;
	int		varlen;

	realflags = NULL;
	realflags = flagger((char *)s);
	varlen = sorter(fd, realflags, args);
	free(realflags);
	return (varlen);
}

// Creates a string with the appropriate flags
// It needs to be freed.
static char	*flagger(char *flags)
{
	int		i;
	char	*ret;

	i = 1;
	while (flags[i] != 'c'
		|| flags[i] != 's' || flags[i] != 'p'
		|| flags[i] != 'd' || flags[i] != 'i'
		|| flags[i] != 'u' || flags[i] != 'x'
		|| flags[i] != 'X' || flags[i] != '%')
	{
		if (flags[i] == 'c'
			|| flags[i] == 's' || flags[i] == 'p'
			|| flags[i] == 'd' || flags[i] == 'i'
			|| flags[i] == 'u' || flags[i] == 'x'
			|| flags[i] == 'X' || flags[i] == '%')
			break ;
		i++;
	}
	i++;
	ret = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(ret, flags, i + 1);
	return (ret);
}

static int	sorter(int fd, char *flags, va_list args)
{
	if (flags[ft_strlen(flags) - 1] == 's')
		return (stringprinter(fd, va_arg(args, char *)));
	if (flags[ft_strlen(flags) - 1] == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		return (1);
	}
	if (flags[ft_strlen(flags) - 1] == '%')
		return (percentprinter(fd, flags));
	if (flags[ft_strlen(flags) - 1] == 'x'
		|| flags[ft_strlen(flags) - 1] == 'X')
		return (hexprinter(fd, flags, va_arg(args, unsigned int)));
	if (flags[ft_strlen(flags) - 1] == 'p')
		return (pointerprinter(fd, va_arg(args, unsigned long)));
	if (flags[ft_strlen(flags) - 1] == 'd'
		|| flags[ft_strlen(flags) - 1] == 'i')
		return (numberprinter(fd, va_arg(args, unsigned int)));
	if (flags[ft_strlen(flags) - 1] == 'u')
		return (unsignedprinter(fd, va_arg(args, unsigned long)));
	return (0);
}
