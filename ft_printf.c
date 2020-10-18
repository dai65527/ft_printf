/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 07:26:44 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/18 14:24:58 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

int				ft_printf(const char *format, ...)
{
	int			count;
	va_list		ap;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			format = ft_printf_putarg(format + 1, &ap, &count);
		else
		{
			ft_putchar_fd(*(format++), 1);
			count++;
		}
	}
	va_end(ap);
	return (count);
}
