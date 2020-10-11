# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2020/10/11 17:04:12 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra
NAME			:= libftprintf.a
OUTPUTDIR		:= .
OUTPUTS			:= $(addprefix $(OUTPUTDIR)/,$(NAME))
SRCNAME			:= ft_printf.c ft_printf_findflags.c ft_printf_putarg.c\
					ft_printf_putint.c ft_printf_putpadding.c\
					ft_printf_putpercent.c
# BONUSSRCNAME	:= 
SRCDIR			:= .
SRCS			:= $(addprefix $(SRCDIR)/,$(SRCNAME))
OBJNAME			:= $(SRCNAME:%.c=%.o)
# BONUSOBJNAME	:= $(BONUSSRCNAME:%.c=%.o)
OBJDIR			:= $(SRCDIR)
OBJS			:= $(addprefix $(OBJDIR)/,$(OBJNAME))
# BONUSOBJS		:= $(addprefix $(OBJDIR)/,$(BONUSOBJNAME))
LIBNAME			:= libft.a
LIBHEADERNAME	:= libft.h
LIBDIR			:= libft
HEADERNAME		:= libftprintf.h
HEADERDIR		:= .
HEADERS			:= $(addprefix $(HEADERDIR)/,$(HEADERNAME))\
					$(addprefix $(LIBDIR)/,$(LIBHEADERNAME))
TESTDIR			:= .
TESTNAME		:= test.out
TESTSRCNAME		:= test.c
# TESTINCLUDENAME	:= 
TESTS			:= $(addprefix $(TESTDIR)/,$(TESTNAME))
TESTSRCS		:= $(addprefix $(TESTDIR)/,$(TESTSRCNAME))
TESTINCLUDES	:= $(addprefix $(TESTDIR)/,$(TESTINCLUDENAME))

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(NAME):		$(OBJS) $(HEADERS)
				cd $(LIBDIR)/ && make $(LIBNAME)
				cp $(LIBDIR)/$(LIBNAME) $(OUTPUTDIR)/
				mv $(LIBNAME) $(NAME)
				ar r $(OUTPUTS) $(OBJS)

.PHONY:			bonus
bonus:			$(OBJS) $(BONUSOBJS) $(HEADERS)
				ar cr $(OUTPUTS) $(OBJS) $(BONUSOBJS)

.c.o:
				$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $(patsubst %.c,%.o,$<)

.PHONY:			clean
clean:
				cd $(LIBDIR)/ && make clean
				rm -f $(OBJS) $(BONUSOBJS)

.PHONY:			fclean
fclean:			clean
				cd $(LIBDIR)/ && make fclean
				rm -f $(OUTPUTS)

.PHONY:			re
re:				fclean all

$(TESTNAME):	$(OUTPUTS) $(TESTSRCS) $(TESTINCLUDES) $(OUTPUTNAME)
				$(CC) $(CFLAGS) $(TESTSRCS) -L. $(patsubst lib%.a,-l%,$(NAME)) -o $(TESTS)\
					$(addprefix -include ,$(TESTINCLUDES))

.PHONY:			test
test:			$(TESTNAME)
				$(TESTDIR)/$(TESTNAME)

.PHONY:			debug
debug:
				$(warning OBJS = $(OBJS))
				$(warning SRCS = $(SRCS))
				$(warning OUTPUTS = $(OUTPUTS))
				$(warning $(patsubst lib%.a,-l%,$(NAME)))
