/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:01:52 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/13 12:20:39 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

# define FLAG_ZEROPADDING		0x1
# define FLAG_LEFTADJUST		0x2
# define FLAG_WIDTH_NEXTARG		0x4
# define FLAG_PRECISION_NEXTARG 0x8
# define FLAG_PUTPOSSIGN		0x10
# define FLAG_PUTPOSSPACE		0x20
# define FLAG_ALTERNATE			0x40
# define FLAG_LONG				0x80
# define FLAG_LONGLONG			0x100
# define FLAG_SHORT				0x200
# define FLAG_SHORTSHORT		0x400

typedef	struct	s_printf_flags
{
	int			flag;
	int			width;
	int			precision;
}				t_printf_flags;

int				ft_printf(const char *format, ...);

char			*ft_printf_findflags(const char *format, t_printf_flags *flags);
void			ft_printf_initflags(t_printf_flags *flags);
void			ft_printf_getwidth(int width_arg, t_printf_flags *flags);

void			ft_printf_putnbr_base_digit(t_llong nbr, t_uint radix,
					int digit, int flag_upcase);
void			ft_printf_putnbr_unsigned_base_digit(t_ullong nbr, t_uint radix,
					int digit, int flag_upcase);
int				ft_printf_putnbr_width_digit(t_llong nbr, t_uint radix,
					t_printf_flags *flags);
int				ft_printf_putnbr_unsigned_width_digit(t_ullong nbr,
					t_uint radix, t_printf_flags *flags);

char			*ft_printf_putarg(const char *format, va_list ap, int *count);
int				ft_printf_putbyte(va_list ap, t_printf_flags *flags);
int				ft_printf_putstr(va_list ap, t_printf_flags *flags);
int				ft_printf_putint(char fc, va_list ap, t_printf_flags *flags);
int				ft_printf_putpointer(va_list ap, t_printf_flags *flags);
int				ft_printf_putpercent(va_list ap, t_printf_flags *flags);

void			ft_printf_putpadding(int width, t_printf_flags *flags);
void			ft_printf_putsign(int flag_neg, t_printf_flags *flags);

#endif
