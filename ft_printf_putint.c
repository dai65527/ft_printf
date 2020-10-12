/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 18:46:27 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static int		ft_printf_putsignedint(va_list ap, t_printf_flags *flags)
{
	int				nbr;
	int				nbrwidth;
	const t_uint	radix = 10;

	if (flags->flag & FLAG_WIDTH_NEXTARG)
		ft_printf_getwidth(va_arg(ap, int), flags);
	if (flags->flag & FLAG_PRECISION_NEXTARG)
		flags->precision = va_arg(ap, int);
	nbr = va_arg(ap, int);
	nbrwidth = ((nbr == 0 && flags->precision == 0)
		? 0 : ft_printf_putnbr_width_digit(nbr, radix, flags->precision));
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (nbr < 0 && (flags->flag & FLAG_ZEROPADDING))
		write(1, "-", 1);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (nbr < 0 && !(flags->flag & FLAG_ZEROPADDING))
		write(1, "-", 1);
	if (!(nbr == 0 && flags->precision == 0))
		ft_printf_putnbr_base_digit(nbr, radix, flags->precision, 0);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

static int		ft_printf_putunsignedint(va_list ap, t_printf_flags *flags,
					const char fc)
{
	t_uint	nbr;
	int		nbrwidth;
	t_uint	radix;

	radix = (fc == 'u' ? 10 : 16);
	if (flags->flag & FLAG_WIDTH_NEXTARG)
		ft_printf_getwidth(va_arg(ap, int), flags);
	if (flags->flag & FLAG_PRECISION_NEXTARG)
		flags->precision = va_arg(ap, int);
	nbr = va_arg(ap, int);
	nbrwidth = ((nbr == 0 && flags->precision == 0)
		? 0 : ft_printf_putnbr_width_digit(nbr, radix, flags->precision));
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
