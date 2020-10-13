/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 08:57:15 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/13 15:35:50 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static int		ft_printf_putsignedint(va_list ap, t_printf_flags *flags)
{
	t_llong			nbr;
	int				nbrwidth;
	const t_uint	radix = 10;

	ft_printf_getwidth_prec(ap, flags);
	nbr = va_arg(ap, int);
	nbrwidth = ft_printf_putnbr_width_digit(nbr, radix, flags);
	if (flags->precision >= 0)
		flags->flag = flags->flag & ~FLAG_ZEROPADDING;
	if (nbr < 0 && (flags->flag & FLAG_ZEROPADDING))
		ft_printf_putsign(nbr < 0, flags);
	if (nbrwidth < flags->width && !(flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	if (nbr < 0 && !(flags->flag & FLAG_ZEROPADDING))
		ft_printf_putsign(nbr < 0, flags);
	if (!(nbr == 0 && flags->precision == 0))
		ft_printf_putnbr_base_digit(nbr, radix, flags->precision, 0);
	if (nbrwidth < flags->width && (flags->flag & FLAG_LEFTADJUST))
		ft_printf_putpadding(flags->width - nbrwidth, flags);
	return (nbrwidth < flags->width ? flags->width : nbrwidth);
}

static int		ft_printf_putunsignedint(va_list ap, t_printf_flags *flags,
					const char fc)
{
	t_ullong	nbr;
	int			nbrwidth;
	t_uint		radix;

	radix = (fc == 'u' ? 10 : 16);
	ft_printf_getwidth_prec(ap, flags);
	nbr = va_arg(ap, t_uint);
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
