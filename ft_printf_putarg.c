/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putarg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 09:04:45 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/11 16:16:24 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static int		ft_printf_putarg_put(const char fc, va_list ap, t_printf_flags *flags)
{
	if (fc == '%')
		return (ft_printf_putpercent(ap, flags));
	if (fc == 'd' || fc == 'i' || fc == 'u' || fc == 'x' || fc == 'X')
		return (ft_printf_putint(fc, ap, flags));
	return (1);
}

char			*ft_printf_putarg(const char *format, va_list ap, int *count)
{
	t_printf_flags	flags;

	format = ft_printf_findflags(format, &flags);
	*count += ft_printf_putarg_put(*(format++), ap, &flags);
	return ((char *)format);
}
