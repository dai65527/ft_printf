/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 11:02:54 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/12 11:08:15 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

int		ft_printf_putnbr_width_digit(long long nbr, t_uint radix, int digit)
{
	int					count;
	unsigned long long	nbr_abs;

	count = 0;
	if (nbr == 0)
		return (digit > 1 ? digit : 1);
	nbr_abs = nbr < 0 ? -nbr : nbr;
	if (nbr < 0)
		count++;
	while (nbr_abs > 0 || digit > 0)
	{
		nbr_abs /= radix;
		digit--;
		count++;
	}
	return (count);
}

void		ft_printf_putnbr_unsigned_base_digit(unsigned long long nbr, t_uint radix, int digit, int flagupcase)
{
	const char	*base;
	const char	baselow[] = "0123456789abcdef";
	const char	baseup[] = "0123456789ABCDEF";

	if (radix > 16)
		return ;
	base = (flagupcase ? baseup : baselow);
	if (nbr >= radix || digit - 1 > 0)
		ft_printf_putnbr_unsigned_base_digit(nbr / radix, radix, digit - 1, flagupcase);
	write(1, base + nbr % radix, 1);
}

void		ft_printf_putnbr_base_digit(long long nbr, t_uint radix, int digit, int flag_upcase)
{
	unsigned long long	nbr_abs;

	nbr_abs = nbr < 0 ? -nbr : nbr;
	ft_printf_putnbr_unsigned_base_digit(nbr_abs, radix, digit, flag_upcase);
}
