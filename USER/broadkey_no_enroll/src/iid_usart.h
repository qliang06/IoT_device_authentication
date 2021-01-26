/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
    This text contains proprietary, confidential information of Intrinsic ID B.V.,
    and may be used, copied, distributed and/or published only pursuant to the
    terms of a valid license agreement with Intrinsic ID B.V.\n
    This copyright notice must be retained as part of this text at all times.
*/

#ifndef __IID_USART_H__
#define __IID_USART_H__

#include "iid_platform.h"

/**
 * iid_usart_setup:
 *      It initialize and configures the USART port with given baudrate and following setting:
 * - Data is 8 bit.
 * - Parity is none.
 * - Stop has 1 bit.
 */
void iid_usart_setup(uint32_t baudrate);

/**
 * iid_usart_write:
 *      It writes "num_bytes" bytes of the data pointed by "data" on USART terminal.
 */
void iid_usart_write(const uint8_t * const data, uint32_t num_bytes);

/**
 * iid_usart_read:
 *      It reads "num_bytes" bytes of the data from USART terminal and stores it in data.
 */
void iid_usart_read(uint8_t * const data, uint32_t num_bytes);

#endif /* __IID_USART_H__ */
