/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
    This text contains proprietary, confidential information of Intrinsic ID B.V.,
    and may be used, copied, distributed and/or published only pursuant to the
    terms of a valid license agreement with Intrinsic ID B.V.\n
    This copyright notice must be retained as part of this text at all times.
*/

#ifndef __IID_PRINT_H__
#define __IID_PRINT_H__

#include "iid_platform.h"

/**************** PUBLIC FUNCTIONS ****************/
/**
 * print_string: Print the string (with '\0' at the end) on the terminal.
 */
void print_string(const char *data);

/**
 * print_num: Print 32bit integer number.
 */
void print_num(int32_t num);

/**
 * print_hexbyte: Print the byte in hexadecimal form.
 */
void print_hexbyte(uint8_t ch);

/**
 * print_hexhalfword: Print the 2bytes in hexadecimal form.
 */
void print_hexhalfword(uint16_t hword);

/**
 * print_hexword: Print the 4bytes in hexadecimal form.
 */
void print_hexword(uint32_t word);

/**
 * print_error: Print the function name string (with '\0' at the end) and error code.
 */
void print_error(char * const func_name, uint32_t err_code);

#endif /* __IID_PRINT_H__ */
