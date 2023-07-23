CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRCS=fd_printf.c \
	fd_printf_char.c \
	fd_printf_decimal.c \
	fd_printf_lowercase_hexa.c \
	fd_printf_pointer.c \
	fd_printf_string.c \
	fd_printf_unsigned.c \
	fd_printf_uppercase_hexa.c 
OBJS=${SRCS:.c=.o}
NAME=libftprintf.a
AR=ar -rc


all:${NAME}

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

${NAME}:${OBJS}
	$(AR) ${NAME} $^

clean:
	rm -rf ${OBJS}

fclean:
	rm -rf ${OBJS} ${NAME}

re: clean all
