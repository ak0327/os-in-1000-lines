#include "common.h"

void putchar(char ch);

static void putstr(const char *s) {
    while (*s) {
        putchar(*s);
        s++;
    }
}

static void putnbr(int value) {
    if (value < 0) {
        putchar('-');
        value = -value;
    }
    int divisor = 1;
    while (value / divisor > 9) {
        divisor *= 10;
    }

    while (divisor > 0) {
        putchar('0' + value / divisor);
        value %= divisor;
        divisor /= 10;
    }
}

static void puthex(int value) {
    for (int i = 7; i >= 0; i--) {
        int nibble = (value >> (i * 4)) & 0xf;
        putchar("0123456789abcdef"[nibble]);
    }
}

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case '\0':
                    putchar('%');
                    goto end;
                case '%':
                    putchar('%');
                    break;
                case 's': {
                    const char *s = va_arg(vargs, const char *);
                    putstr(s);
                    break;
                }
                case 'd': {
                    int value = va_arg(vargs, int);
                    putnbr(value);
                    break;
                }
                case 'x': {
                    int value = va_arg(vargs, int);
                    puthex(value);
                }
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }

end:
    va_end(vargs);
}
