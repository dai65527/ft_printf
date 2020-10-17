/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:01:52 by dnakano           #+#    #+#             */
/*   Updated: 2020/10/17 14:02:53 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdint.h>
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

# define FLT_MTSSIZE	1076
# define FLT_INTSIZE	309
# define FLT_FRACBIT	52
# define FLT_EXPBIAS	1023
# define FLT_EXPBIT		11

typedef	struct	s_printf_flags
{
	int			flag;
	int			width;
	int			precision;
}				t_printf_flags;

typedef struct	s_float
{
	u_int8_t	sign;
	int32_t		exp;
	u_int64_t	frac;
	int8_t		int_dec[FLT_INTSIZE];
	int8_t		mts_dec[FLT_MTSSIZE];
}				t_float;

int				ft_printf(const char *format, ...);

char			*ft_printf_findflags(const char *format, va_list ap, t_printf_flags *flags);
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
int				ft_printf_putpercent(t_printf_flags *flags);
int				ft_printf_putfloat(const char fc, va_list ap,
									t_printf_flags *flags);

void			ft_printf_putpadding(int width, t_printf_flags *flags);
void			ft_printf_putsign(int flag_neg, t_printf_flags *flags);
void			ft_printf_putintalternate(const char fc);

t_float			ft_store_iflt(double num);
void			ft_itg_dbl(int8_t *itg, int size);
void			ft_arr_add(int8_t *a, int8_t *b, int size);
void			ft_mts_divbytwo(int8_t *mts, int size);
void			ft_float_round(t_float *iflt, int digit);
void			ft_float_roundup(t_float *iflt, int digit);

#endif
