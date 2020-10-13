/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/13 09:26:44 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static t_llong	ft_printf_putsignedint_storenbr(va_list ap,
					t_printf_flags *flags)
{
	if (flags->flag & FLAG_LONGLONG)
		return (va_arg(ap, t_llong));
	else if (flags->flag & FLAG_LONG)
		return (va_arg(ap, long));
	else if (flags->flag & FLAG_SHORTSHORT)
		return ((char)va_arg(ap, int));
	else if (flags->flag & FLAG_SHORT)
		return ((short)va_arg(ap, int));
	return (va_arg(ap, int));
}

static int		ft_printf_putsignedint(va_list ap, t_printf_flags *flags)
{
	t_llong			nbr;
	int				nbrwidth;
	const t_uint	radix = 10;

	if (flags->flag & FLAG_WIDTH_NEXTARG)
		ft_printf_getwidth(va_arg(ap, int), flags);
	if (flags->flag & FLAG_PRECISION_NEXTARG)
		flags->precision = va_arg(ap, int);
	nbr = ft_printf_putsignedint_storenbr(ap, flags);
	nbrwidth = ft_printf_putnbr_width_digit(nbr, radix, flags);
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (flags->flag & FLAG_ZEROPADDING)
		nbrwidth += ft_printf_putsign(nbr < 0, flags);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (!(flags->flag & FLAG_ZEROPADDING))
		nbrwidth += ft_printf_putsign(nbr < 0, flags);
	if (!(nbr == 0 && flags->precision == 0))
		ft_printf_putnbr_base_digit(nbr, radix, flags->precision, 0);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

static t_ullong	ft_printf_putunsignedint_storenbr(va_list ap,
					t_printf_flags *flags)
{
	if (flags->flag & FLAG_LONGLONG)
		return ((t_ullong)va_arg(ap, t_llong));
	else if (flags->flag & FLAG_LONG)
		return ((t_ulong)va_arg(ap, long));
	else if (flags->flag & FLAG_SHORTSHORT)
		return ((t_uchar)va_arg(ap, int));
	else if (flags->flag & FLAG_SHORT)
		return ((t_ushort)va_arg(ap, int));
	return (va_arg(ap, t_uint));
}

static int		ft_printf_putunsignedint(va_list ap, t_printf_flags *flags,
					const char fc)
{
	t_ullong	nbr;
	int			nbrwidth;
	t_uint		radix;

	radix = (fc == 'u' ? 10 : 16);
	if (flags->flag & FLAG_WIDTH_NEXTARG)
		ft_printf_getwidth(va_arg(ap, int), flags);
	if (flags->flag & FLAG_PRECISION_NEXTARG)
		flags->precision = va_arg(ap, int);
	nbr = ft_printf_putunsignedint_storenbr(ap, flags);
	nbrwidth = ft_printf_putnbr_unsigned_width_digit(nbr, radix, flags);
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (!(nbr == 0 && flags->precision == 0))
		ft_printf_putnbr_unsigned_base_digit(nbr, radix, flags->precision,
												ft_isupper(fc));
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

int				ft_printf_putint(const char fc, va_list ap,
									t_printf_flags *flags)
{
	int		count;

	count = 0;
	if (fc == 'd' || fc == 'i')
		count = ft_printf_putsignedint(ap, flags);
	else if (fc == 'u' || fc == 'x' || fc == 'X')
		count = ft_printf_putunsignedint(ap, flags, fc);
	return (count);
}
