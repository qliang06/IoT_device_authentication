/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
 *  This text contains proprietary, confidential information of Intrinsic ID B.V.,
 *  and may be used, copied, distributed and/or published only pursuant to the
 *  terms of a valid license agreement with Intrinsic ID B.V.\n
 *  This copyright notice must be retained as part of this text at all times.
 */

#ifndef _IID_RETURN_CODES_H_
#define _IID_RETURN_CODES_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*! \defgroup BroadKeyReturnCodes
 *  \ingroup BroadKey
 *  \brief The possible return codes returned by BroadKey functions.
 */

/*@{*/

/*! \brief Successful execution
 *  \details Value indicating the successful execution of the called function.
 */
#define IID_SUCCESS                  0x00

/*! \brief Generic return codes base
 *  \details Value used internally as the base value for all generic return codes.
 */
#define IID_RETURN_BASE              0x01

/*! \brief BroadKey return codes base
 *  \details Value used internally as the base value for all BroadKey-specific return codes.
 */
#define IID_RETURN_BK                0x20


/*! \brief ECC return codes base
 *  \details Value used internally as the base value for all ECC-specific return codes.
 */
#define IID_RETURN_ECC               0x30

/******************************* Generic Return Codes *******************************/
/*! \brief Function call not allowed in the current state
 *  \details Value indicating that the given function call is not allowed in the current
 *           state of the BroadKey module.
 */
#define IID_NOT_ALLOWED              (IID_RETURN_BASE + 0x00)

/*! \brief Invalid function parameters
 *  \details Value indicating that at least one of the parameters passed as argument
 *           to the function call has an invalid form and/or content.
 */
#define IID_INVALID_PARAMETERS       (IID_RETURN_BASE + 0x01)

/************************** BroadKey Specific Return Codes **************************/
/*! \brief Error startup data
 *  \details Value indicating that the appointed SRAM address does not contain
 *           qualitative start-up data which can be used as an SRAM PUF by BroadKey.
 *           Re-power the device and try again.
 */
#define IID_ERROR_STARTUP_DATA       (IID_RETURN_BK + 0x00)

/*! \brief Invalid activation code
 *  \details An invalid activation code has been supplied to the \ref bk_start function.
 */
#define IID_INVALID_AC               (IID_RETURN_BK + 0x01)

/*! \brief Invalid key code
 *  \details An invalid key code has been supplied to the \ref bk_unwrap function.
 */
#define IID_INVALID_KEY_CODE         (IID_RETURN_BK + 0x02)

/************************** ECC Specific Return Codes **************************/
/*! \brief Invalid private key
 *  \details An invalid private key has been supplied to ECC functions.
 */
#define IID_INVALID_PRIVATE_KEY      (IID_RETURN_ECC + 0x00)

/*! \brief Invalid public key
 *  \details An invalid public key has been supplied to ECC functions.
 */
#define IID_INVALID_PUBLIC_KEY       (IID_RETURN_ECC + 0x01)

/*! \brief Invalid signature
 *  \details The signature presented to the verification function is not valid.
 */
#define IID_INVALID_SIGNATURE        (IID_RETURN_ECC + 0x02)

/*! \brief Invalid public key code
 *  \details An invalid public key code has been supplied to ECC functions.
 */
#define IID_INVALID_PUBLIC_KEY_CODE  (IID_RETURN_ECC + 0x03)

/*! \brief Invalid private key code
 *  \details An invalid private key code has been supplied to ECC functions.
 */
#define IID_INVALID_PRIVATE_KEY_CODE (IID_RETURN_ECC + 0x04)

/*! \brief Presented key code not allowed to be used
 *  \details The presented public/private key code is not allowed to be used
 *           for the called ECC function.
 */
#define IID_ECC_NOT_ALLOWED          (IID_RETURN_ECC + 0x05)

/*! \brief Presented counter is invalid
 *  \details The presented counter is invalid as it either overflows when
 *           incremented or it is greater/equal than expected.
 */
#define IID_INVALID_COUNTER          (IID_RETURN_ECC + 0x06)

/*! \brief Invalid cryptogram
 *  \details An invalid cryptogram has been supplied to cryptogram functions.
 */
#define IID_INVALID_CRYPTOGRAM       (IID_RETURN_ECC + 0x07)

/*! \brief Invalid sender
 *  \details The public key specified as input of the \ref bk_process_cryptogram
 *           does not match the public key of the sender present in the cryptogram.
 */
#define IID_INVALID_SENDER           (IID_RETURN_ECC + 0x08)

/*! \brief Curve mismatch
 *  \details The curve of the private key code does not match the curve of the
 *           public key code.
 */
#define IID_CURVE_MISMATCH           (IID_RETURN_ECC + 0x09)

/*@}*/

#ifdef __cplusplus
}
#endif
#endif /* _IID_RETURN_CODES_H_ */
