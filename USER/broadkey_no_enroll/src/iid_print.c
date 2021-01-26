/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
    This text contains proprietary, confidential information of Intrinsic ID B.V.,
    and may be used, copied, distributed and/or published only pursuant to the
    terms of a valid license agreement with Intrinsic ID B.V.\n
    This copyright notice must be retained as part of this text at all times.
*/

#include "iid_platform.h"
#include "iid_print.h"
#include "iid_usart.h"

#define _32BIT_INT_PRINT_LIMIT    (11) /* maximum 10 digits + '\0' in an 32 integer */

/**************** STATIC FUNCTIONS DECLARATIONS *****************/
static unsigned stringlen(const char* string);
static void itoa(int n, char s[]);
static void reverse(char s[]);

/**************** PUBLIC FUNCTIONS ****************/
void print_string(const char *data)
{
    uint16_t num_bytes;

    if (data == NULL)
    {
        return;
    }

    num_bytes = stringlen(data);

    if (num_bytes)
    {
        iid_usart_write((uint8_t *)data, num_bytes);
    }
}

void print_hexbyte(uint8_t ch)
{
    uint8_t b;

    b = ((0xF0 & ch) >> 4);
    b += (b < 10) ? 48 : 55; /* Convert to ASCII */

    /* Write higher nibble */
    iid_usart_write(&b, 1);

    b = (0xF & ch);
    b += (b < 10) ? 48 : 55; /* Convert to ASCII */

    /* write lower nibble */
    iid_usart_write(&b, 1);
}

void print_hexhalfword(uint16_t hword)
{
    print_hexbyte((hword >> 8) & 0xFF);
    print_hexbyte((hword) & 0xFF);
}

void print_hexword(uint32_t word)
{
    print_hexbyte((word >> 24) & 0xFF);
    print_hexbyte((word >> 16) & 0xFF);
    print_hexbyte((word >> 8) & 0xFF);
    print_hexbyte((word) & 0xFF);
}

void print_num(int32_t num)
{
    unsigned num_bytes = 0;
    uint8_t buffer[_32BIT_INT_PRINT_LIMIT];

    itoa(num, (char *) buffer);
    num_bytes = stringlen((char *) buffer);

    iid_usart_write(buffer, num_bytes);
}

void print_error(char * const func_name, uint32_t err_code)
{
    print_string("Error: Function \"");
    print_string(func_name);
    print_string("\" failed with return value 0x");
    print_hexword(err_code);
    print_string("\r\n");
}

/**************** STATIC FUNCTIONS DEFINITIONS *****************/
static unsigned stringlen(const char* string)
{
    unsigned num_bytes = 0;

    while (string[num_bytes] != '\0')
    {
        num_bytes++;
    }

    return num_bytes;
}

static void reverse(char s[])
{
    unsigned i, j;
    char c;

    for (i = 0, j = stringlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void itoa(int n, char s[])
{
    unsigned i = 0;
    int sign;

    if ((sign = n) < 0)  /* record sign */
    {
        n = -n;          /* make n positive */
    }

    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */

    if (sign < 0)
    {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}
