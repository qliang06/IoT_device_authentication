/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
    This text contains proprietary, confidential information of Intrinsic ID B.V.,
    and may be used, copied, distributed and/or published only pursuant to the
    terms of a valid license agreement with Intrinsic ID B.V.\n
    This copyright notice must be retained as part of this text at all times.
*/

#include "broadkey_demo_app.h"
#include "iidbroadkey.h"
#include "iidreturn_codes.h"
#include "iid_print.h"
#include "iid_usart.h"

#define SYMMETRIC_OUT_KEY_SIZE_BYTES    (16)
#define BK_CONFIGURATION_PRO_ENABLED
#define CLIENT_BOARD
//#define HOST_BOARD

/**************************** STATIC DECLARATIONS *************************/
static uint8_t demo_version(void);
static uint8_t demo_init(uint8_t  * const sram_puf);
static uint8_t demo_enroll_or_start(uint8_t  * const sram_ac);
//static uint8_t demo_get_random_bytes(void);
//add by Qin 19/11/2020
static uint8_t demo_get_random_bytes(uint8_t  * const random_arr);

static uint8_t demo_get_symmetric_key(void);
static uint8_t demo_get_private_key(void);

#if defined(BK_CONFIGURATION_PRO_ENABLED) || defined(BK_CONFIGURATION_PLUS_ENABLED)
static uint8_t demo_wrap_and_unwrap(void);
#endif

#if defined(BK_CONFIGURATION_PRO_ENABLED)
static uint8_t demo_derive_public_key_from_private_key(void);
static uint8_t demo_create_private_and_public_key_codes(bk_ecc_private_key_code_t * const ecc_private_key_code,
                                                        bk_ecc_public_key_code_t  * const ecc_public_key_code);
static uint8_t demo_import_and_export_public_key(void);
//add by Qin 11/19/2020
static uint8_t au_get_randomnum(uint8_t * const message,
        						const uint32_t message_length);

static uint8_t demo_ecdsa_sign_and_verify(const bk_ecc_private_key_code_t * const ecc_private_key_code,
                                          const bk_ecc_public_key_code_t  * const ecc_public_key_code,
                                          const uint8_t                   * const message,
                                          const uint32_t                          message_length);
static uint8_t demo_ecdh_shared_secret(const bk_ecc_private_key_code_t * const ecc_private_key_code,
                                       const bk_ecc_public_key_code_t  * const ecc_public_key_code);
static uint8_t demo_generate_and_process_cryptogram(const bk_ecc_private_key_code_t * const sender_ecc_private_key_code,
                                                    const bk_ecc_public_key_code_t  * const sender_ecc_public_key_code);
#endif /* defined(BK_CONFIGURATION_PRO_ENABLED) */

static void read_ac(uint8_t * const ac_data);

/************************** PUBLIC FUNCTIONS *****************************/
void broadkey_demo_app(uint8_t * const sram_puf, uint8_t * const sram_ac)
{
    PRE_HIS_ALIGN bk_ecc_private_key_code_t ecc_private_key_code POST_HIS_ALIGN;
    PRE_HIS_ALIGN bk_ecc_public_key_code_t ecc_public_key_code POST_HIS_ALIGN;
    PRE_HIS_ALIGN uint8_t message[32] POST_HIS_ALIGN = {0xab, 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89,
                                                        0xab, 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89,
                                                        0xab, 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89,
                                                        0xab, 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89};

    //sending random number to host_board and also using for verifying signature by Qin 11/19/2020;
    PRE_HIS_ALIGN uint8_t h_message[16] POST_HIS_ALIGN = {0};
    //using for create signature by client_board by Qin 11/19/2020;
    PRE_HIS_ALIGN uint8_t c_message[16] POST_HIS_ALIGN = {0};

    iid_return_t retval;

    /* Setup USART with Baudrate 115200 */
    iid_usart_setup(115200);

//    print_string("\r\n                **** Welcome to BroadKey Demo ***\r\n");
//    print_string("\r\n---BK Version---\r\n");
    /***********************
    * BroadKey Version     *
    ***********************/
//    if (demo_version())
//    {
//        goto EXIT;
//    }

    print_string("\r\n\r\n---BK Init---\r\n");
    /***********************
    * Initialize BroadKey *
    ***********************/
    if (demo_init(sram_puf))
    {
        goto EXIT;
    }

    print_string("\r\n\r\n---BK Enroll and Start---\r\n");
    /******************************
     *  BroadKey Enroll or Start  *
     ******************************/
    if (demo_enroll_or_start(sram_ac))
    {
        goto EXIT;
    }

    /*******************************************************
     *                      S A F E
     *******************************************************/
    //print_string("\r\n\r\n---BK Get Random Bytes---\r\n");
    /********************************
     *  BroadKey  Get Random Bytes  *
     ********************************/
#if defined(HOST_BOARD)
    if (demo_get_random_bytes(h_message))
    {
        goto EXIT;
    }
#endif //defined(HOST_BOARD)

    //print_string("\r\n\r\n---BK Get Symmetric Key---\r\n");
    /*********************************
     *  BroadKey  Get Symmetric Key  *
     *********************************/
//    if (demo_get_symmetric_key())
//    {
//        goto EXIT;
//    }

    //print_string("\r\n\r\n---BK Get ECC Private Key---\r\n");
    /***********************************
     *  BroadKey  Get ECC Private Key  *
     ***********************************/
//    if (demo_get_private_key())
//    {
//        goto EXIT;
//    }

    /*******************************************************
     *                     P  L  U  S                      *
     *******************************************************/
#if defined(BK_CONFIGURATION_PRO_ENABLED) || defined(BK_CONFIGURATION_PLUS_ENABLED)
//    print_string("\r\n\r\n---BK Wrap and Unwrap the (user) key---\r\n");
//    if (demo_wrap_and_unwrap())
//    {
//        goto EXIT;
//    }
#endif /* defined(BK_CONFIGURATION_PRO_ENABLED) || defined(BK_CONFIGURATION_PLUS_ENABLED) */

    /*******************************************************
     *                     P  R  O                         *
     *******************************************************/
#if defined(BK_CONFIGURATION_PRO_ENABLED)
    /****************************************************
     *  BroadKey GET PRIVATE KEY AND DERIVE PUBLIC KEY  *
     ****************************************************/
//    print_string("\r\n\r\n---BK ECC get Private Key and Derive Public Key---\r\n");
//    if (demo_derive_public_key_from_private_key())
//    {
//        goto EXIT;
//    }

//add by Qin 11/19/2020
#if defined(CLIENT_BOARD)
    if(au_get_randomnum(c_message, sizeof(c_message))){
       	goto EXIT;
       }
#endif //defined(CLIENT_BOARD)
    /*************************************************
     *  BroadKey CREATE PRIVATE AND PUBLIC KEY CODE  *
     *************************************************/
//    print_string("\r\n\r\n---BK ECC Create Private and Public Key Code---\r\n");
    if (demo_create_private_and_public_key_codes(&ecc_private_key_code, &ecc_public_key_code))
    {
        goto EXIT;
    }

    /*******************************************
     *  BroadKey IMPORT AND EXPORT PUBLIC KEY  *
     *******************************************/
//    print_string("\r\n\r\n---BK Import and Export Public Key---\r\n");
//    if (demo_import_and_export_public_key())
//    {
//        goto EXIT;
//    }

    /****************************************
     *  BroadKey ECDSA SIGN AND VERIFY KEY  *
     ****************************************/
//    print_string("\r\n\r\n---BK ECDSA Sign and Verify Key---\r\n");
//add by Qin 11/19/2020;
#if defined(CLIENT_BOARD)
    if (demo_ecdsa_sign_and_verify(&ecc_private_key_code, &ecc_public_key_code, c_message, sizeof(c_message)))
    {
        goto EXIT;
    }
#endif //defined(CLIENT_BOARD)

//add by Qin 11/19/2020
#if defined(HOST_BOARD)
        if (demo_ecdsa_sign_and_verify(&ecc_private_key_code, &ecc_public_key_code, h_message, sizeof(h_message)))
        {
            goto EXIT;
        }
#endif //defined(HOST_BOARD)
//    if (demo_ecdsa_sign_and_verify(&ecc_private_key_code, &ecc_public_key_code, message, sizeof(message)))
//    {
//        goto EXIT;
//    }

    /*********************************
     *  BroadKey ECDH SHARED SECRET  *
     *********************************/
//    print_string("\r\n\r\n---BK Get Shared Secret---\r\n");
//    if (demo_ecdh_shared_secret(&ecc_private_key_code, &ecc_public_key_code))
//    {
//        goto EXIT;
//    }

    /*************************************
     *  GENERATE AND PROCESS CRYPTOGRAM  *
     *************************************/
//    print_string("\r\n\r\n---BK Generate and Process Cryptogram---\r\n");
//    if (demo_generate_and_process_cryptogram(&ecc_private_key_code, &ecc_public_key_code))
//    {
//        goto EXIT;
//    }
#endif /* defined(BK_CONFIGURATION_PRO_ENABLED) */

EXIT:
#if defined(CLIENT_BOARD)
    print_string("\r\n--- End of the Authentication of client_board Demo Application! ---\r\n");
#endif
#if defined(HOST_BOARD)
    print_string("\r\n--- End of the Authentication of host_board Demo Application! ---\r\n");
#endif

    return;
}

/*********************
*  BroadKey Version  *
**********************/
static uint8_t demo_version(void)
{
   uint8_t major_version;
   uint8_t minor_version;
   uint8_t product_id;
   uint8_t patch;
   uint8_t build_number;
   char p_id[2];
   iid_return_t retval;

   retval = bk_get_product_info(&product_id,
                                &major_version,
                                &minor_version,
                                &patch,
                                &build_number);

   if (IID_SUCCESS != retval)
   {
       print_error("bk_get_product_info", retval);
       return 1;
   }

   p_id[0] = product_id;
   p_id[1] = '\0';
   print_string("product_id: ");
   print_string(p_id);

   print_string("\r\nmajor_version: ");
   print_num(major_version);

   print_string("\r\nminor_version: ");
   print_num(minor_version);

   print_string("\r\npatch: ");
   print_num(patch);

   print_string("\r\nbuild_number: ");
   print_num(build_number);

   return 0;
}

/*************************
 *  Initialize BroadKey  *
 *************************/
static uint8_t demo_init(uint8_t  * const sram_puf)
{
    iid_return_t retval;

    //print_string("bk_init ...");

    retval = bk_init(sram_puf, BK_SRAM_PUF_SIZE_BYTES);

    if (IID_SUCCESS != retval)
    {
        //print_error("bk_init", retval);
        return 1;
    }

    //print_string("done!\r\n");

    return 0;
}

/****************************
 * BroadKey Enroll or Start *
 ****************************/
static uint8_t demo_enroll_or_start(uint8_t  * const sram_ac)
{
    PRE_HIS_ALIGN uint8_t activation_code[BK_AC_SIZE_BYTES] POST_HIS_ALIGN;
    unsigned int i;
    //uint32_t retcode;
    iid_return_t retval;
    uint8_t input[2] = { 0 };

    print_string("BroadKey enroll...:\r\n");
//    print_string("The ac code is little endian.\r\n");
//    print_string("Press 1 for enroll(invalid in this program).\r\n");
//    print_string("Press 2 for start(the ac code is big endian).\r\n");
//    print_string("Press 3 for start(the ac code is little endian).\r\n");
//
//    do
//    {
//        print_string(" Input : ");
//
//        iid_usart_read(input, 1);
//
//        print_string(input);
//        print_string("\r\n");
//    } while (('1' != input[0]) && ('2' != input[0]) && ('3' != input[0]));

    input[0] = '3';

    if ('1' == input[0])
    {
        /***********************
        * BroadKey  Enroll     *
        ***********************/
        print_string("\r\nNo bk_enroll ...");

        /*retval = bk_enroll(activation_code);

        //if (IID_SUCCESS != IID_SUCCESS)		//Bug
        if (IID_SUCCESS != retval)				//FY, 190418a
        {
            print_error("bk_enroll", retval);
            return 1;
        }*/

        print_string("done!\r\n");

        /*print_string("The Activation code is :\r\n");

        for (i = 0 ; i < BK_AC_SIZE_BYTES; i++)
        {
            print_hexbyte(activation_code[i]);
        }

        print_string("\r\n");*/

        return 0;
    }
    else
    {
        /*print_string("\r\nPlease copy the activation code exactly as previously printed by the enroll function\r\n");

        read_ac(activation_code);

        print_string("The Activation code is :\r\n");

        for (i = 0 ; i < BK_AC_SIZE_BYTES; i++)
        {
            print_hexbyte(activation_code[i]);
        }

        print_string("\r\n");*/

extern void endian_big_little_u32_array(uint32_t *in, uint32_t len);

//    	print_string("\r\nac_addr = 0x");
//    	print_hexword((uint32_t)sram_ac);

    	for (i = 0 ; i < BK_AC_SIZE_BYTES; i++)
		{
			activation_code[i] = sram_ac[i];
		}

    	//print_string("\r\nThe activation code is ");
    	if ('2' == input[0])
    	{
    		print_string("big endian\r\n");
    		endian_big_little_u32_array((uint32_t *)activation_code, BK_AC_SIZE_BYTES / 4);
    	}
    	else
    	{
    		print_string("little endian\r\n");
    	}

//        print_string("\r\n00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
        print_string("Begin.\r\n");

        for (i = 0 ; i < BK_AC_SIZE_BYTES; i++)
		{
			print_hexbyte(activation_code[i]);

			if (0 == ((i + 1) % 16))
			{
				print_string("\r\n");
			}
			else
			{
				print_string(" ");
			}
		}

        print_string("\r\nEnd.\r\n");
//        print_string("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
//
        print_string("\r\nbk_start ...");

        retval = bk_start(activation_code);

        if (IID_SUCCESS != retval)
        {
            print_error("bk_start", retval);
            return 1;
        }

        print_string("Board initialization done!\r\n");
    }

    return 0;
}

/********************************
 *  BroadKey  Get Random Bytes  *
 ********************************/
//iid_return_t bk_generate_random(const uint16_t  number_of_bytes, uint8_t * const data_buffer);

static uint8_t demo_get_random_bytes(uint8_t * const random_arr)
{
#if defined(HOST_BOARD)
		uint16_t num_bytes = 16;
	    //uint8_t  data_buffer[16];
	    unsigned i;
	    iid_return_t retval;

	    //print_string("bk_generate_random ...");

	    retval = bk_generate_random(num_bytes, random_arr);
	    //retval = bk_generate_random(num_bytes, data_buffer);
	    if (IID_SUCCESS != retval)
	    {
	        //print_error("bk_generate_random", retval);
	        return 1;
	    }

	    print_string("Host waiting Signal to send out the Random number:\r\n");
		uint8_t input[2] = { 0 };
		do
			   {
				   //print_string(" Input : ");

				   iid_usart_read(input, 1);

				   //print_string(input);
				   //print_string("\r\n");
			   } while (('#' != input[0]));

		print_string("#\r\n");
//	    print_string("done!\r\n");
//
//	    print_string("The Random generated bytes are :\r\n");

	    for (i = 0 ; i < num_bytes; i++)
	    {
	        print_hexbyte(random_arr[i]);
	    }

	    print_string("\r\n");
#endif
	    return 0;

}

/************************
 *  BroadKey  Get Key   *
 ************************/
static uint8_t demo_get_symmetric_key(void)
{
    PRE_HIS_ALIGN uint8_t key[SYMMETRIC_OUT_KEY_SIZE_BYTES] POST_HIS_ALIGN;
    unsigned int i;
    uint8_t index = 0;
    iid_return_t retval;

    print_string("bk_get_key ...");

    retval = bk_get_key(BK_SYM_KEY_TYPE_128, index, key);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_get_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The Key is :\r\n");

    for (i = 0 ; i < SYMMETRIC_OUT_KEY_SIZE_BYTES; i++)
    {
        print_hexbyte(key[i]);
    }

    print_string("\r\n");
    return 0;
}

/********************************
 *  BroadKey Get ECC PRIVATE Key    *
 ********************************/
static uint8_t demo_get_private_key(void)
{
    bk_ecc_curve_t curve = BK_ECC_CURVE_NIST_P224;
    PRE_HIS_ALIGN uint8_t private_key[28] POST_HIS_ALIGN; /* size depends on the curve, see datasheet */
    iid_return_t retval;
    unsigned int i;

    print_string("bk_get_private_key ...");

    retval = bk_get_private_key(curve,
                                0, /* No Usage Context, change NULL TO 0*/
                                0,
                                BK_ECC_KEY_SOURCE_PUF_DERIVED,
                                private_key);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_get_private_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The generated ECC Private Key is:\r\n");

    for (i = 0; i < sizeof(private_key); i++)
    {
        print_hexbyte(private_key[i]);
    }
    print_string("\r\n");
    return 0;
}

#if defined(BK_CONFIGURATION_PRO_ENABLED) || defined(BK_CONFIGURATION_PLUS_ENABLED)
/******************************************************************************************************
 *                                           P  L  U  S
 ******************************************************************************************************/

/****************************
 * BroadKey Wrap and UnWrap *
 ****************************/
static uint8_t demo_wrap_and_unwrap(void)
{
    PRE_HIS_ALIGN uint8_t user_key[16] POST_HIS_ALIGN = {0x66,0xf4,0x77,0xce,0xbe,0x0e,0x51,0x71,0x6a,0x73,0x3c,0x92,0xe2,0x8f,0xcb,0x0c};
    PRE_HIS_ALIGN uint8_t ret_user_key[sizeof(user_key)] POST_HIS_ALIGN = {0};
    PRE_HIS_ALIGN uint8_t key_code[sizeof(user_key) + BK_KEY_CODE_HEADER_SIZE_BYTES] POST_HIS_ALIGN;
    uint32_t i;
    uint8_t index = 0;
    uint8_t ret_index;
    uint16_t ret_uk_length;
    iid_return_t retval;

    print_string("The User Key to be wrapped is:\r\n");

    for (i = 0; i < sizeof(user_key); i++)
    {
        print_hexbyte(user_key[i]);
    }

    print_string("\r\n");

    /***********************
     *  BroadKey  WRAP    *
     ***********************/
    print_string("\r\nbk_wrap ...");

    retval = bk_wrap(index, user_key, sizeof(user_key), key_code);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_wrap", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The Key Code is:\r\n");

    for (i = 0 ; i < sizeof(key_code); i++)
    {
        print_hexbyte(key_code[i]);
    }

    print_string("\r\n");

    /***********************
     *  BroadKey  UNWRAP    *
     ***********************/
    print_string("\r\nbk_unwrap ...");

    retval = bk_unwrap(key_code, ret_user_key, &ret_uk_length, &ret_index);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_unwrap", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The Ret User Key is:\r\n");

    for (i = 0 ; i < sizeof(ret_user_key); i++)
    {
        print_hexbyte(ret_user_key[i]);
    }

    print_string("\r\nReturn index: ");
    print_num(ret_index);

    print_string("\r\nReturn user key length:");
    print_num(ret_uk_length);
    print_string("\r\n");

    return 0;
}

#endif /* defined(BK_CONFIGURATION_PRO_ENABLED) || defined(BK_CONFIGURATION_PLUS_ENABLED) */

#if defined(BK_CONFIGURATION_PRO_ENABLED)
/******************************************************************************************************
 *                                           P R O
 ******************************************************************************************************/
/****************************************************
 *  BroadKey GET PRIVATE KEY AND DERIVE PUBLIC KEY  *
 ****************************************************/
static uint8_t demo_derive_public_key_from_private_key(void)
{
    bk_ecc_curve_t curve = BK_ECC_CURVE_NIST_P192;
    PRE_HIS_ALIGN uint8_t private_key[24] POST_HIS_ALIGN; /* size depends on the curve, see datasheet */
    PRE_HIS_ALIGN uint8_t public_key[49] POST_HIS_ALIGN; /* size depends on the curve, see datasheet */
    uint8_t usage_context[] = {'D', 'E', 'M', 'O', 'K', 'E', 'Y'};
    uint32_t i;
    iid_return_t retval;

    /******************************
     *  BroadKey GET PRIVATE KEY  *
     ******************************/
    print_string("bk_get_private_key ...");

    retval = bk_get_private_key(curve, usage_context, sizeof(usage_context), BK_ECC_KEY_SOURCE_RANDOM, private_key);
    //retval = bk_get_private_key(curve, usage_context, 0, BK_ECC_KEY_SOURCE_PUF_DERIVED, private_key);
    if (IID_SUCCESS != retval)
    {
        print_error("bk_get_private_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The generated Private Key is:\r\n");

    for (i = 0; i < sizeof(private_key); i++)
    {
        print_hexbyte(private_key[i]);
    }

    print_string("\r\n");

    /******************************
     *  BroadKey DERIVE PUBLIC KEY  *
     ******************************/
    print_string("\r\nbk_derive_public_key ...");

    retval = bk_derive_public_key(0, curve, private_key, public_key);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_derive_public_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The derived Public Key is:\r\n");

    for (i = 0; i < sizeof(public_key); i++)
    {
        print_hexbyte(public_key[i]);
    }

    print_string("\r\n");

    return 0;
}

static uint8_t demo_import_and_export_public_key(void)
{
    bk_ecc_curve_t curve = BK_ECC_CURVE_NIST_P256;

    //    PRE_HIS_ALIGN uint8_t ecc_x9_62_public_key[65] POST_HIS_ALIGN = /* size depends on the curve. 65 is according to NIST P256 curve */
    //                                                                    {0x04, 0xf3, 0x13, 0x94, 0x7a, 0xdb, 0x02, 0x6b, 0xc1, 0x1f, 0x3a, 0x50, 0xc4, 0x04, 0x07,
    //                                                                     0xd1, 0x12, 0x12, 0x6a, 0xb2, 0x90, 0xe8, 0xc8, 0x48, 0x7a, 0x4b, 0x3c, 0xf6, 0x8a, 0x7e,
    //                                                                     0x3b, 0x4e, 0xfe, 0x67, 0xe7, 0x69, 0xbd, 0x74, 0xb6, 0x32, 0x3c, 0x26, 0xea, 0x66, 0x43,
    //                                                                     0x81, 0xe6, 0x74, 0xd2, 0xaa, 0xdb, 0x1c, 0xa6, 0x44, 0x03, 0xfc, 0x7a, 0x72, 0x90, 0x28,
    //                                                                     0x20, 0xbf, 0x1d, 0x3d, 0x89};

   //042C4F0B9E6B94450BA6BA59CDF25F9A1816EEF2529213AC65BCEE18085FCFC68EF54653A2A05D1A914E4BC0743BDC65AB8CBD0F1BAB3AC63CCCAFCC31C9AF55A4
    PRE_HIS_ALIGN uint8_t ecc_x9_62_public_key[65] POST_HIS_ALIGN = /* size depends on the curve. 65 is according to NIST P256 curve */
                                                                        {0x04, 0x2c, 0x4f, 0x0b, 0x9e, 0x6b, 0x94, 0x45,
                                                                         0x0b, 0xa6, 0xba, 0x59, 0xcd, 0xf2, 0x5f, 0x9a,
																		 0x18, 0x16, 0xee, 0xf2, 0x52, 0x92, 0x13, 0xac,
																		 0x65, 0xbc, 0xee, 0x18, 0x08, 0x5f, 0xcf, 0xc6,
																		 0x8e, 0xf5, 0x46, 0x53, 0xa2, 0xa0, 0x5d, 0x1a,
																		 0x91, 0x4e, 0x4b, 0xc0, 0x74, 0x3b, 0xdc, 0x65,
																		 0xab, 0x8c, 0xbd, 0x0f, 0x1b, 0xab, 0x3a, 0xc6,
																		 0x3c, 0xcc, 0xaf, 0xcc, 0x31, 0xc9, 0xaf, 0x55,
																		 0xa4};

    PRE_HIS_ALIGN uint8_t temp_ecc_x9_62_public_key[sizeof(ecc_x9_62_public_key)] POST_HIS_ALIGN = {0};
    PRE_HIS_ALIGN bk_ecc_public_key_code_t ecc_x9_62_public_key_code POST_HIS_ALIGN;
    uint32_t i;
    bk_ecc_key_purpose_t purpose_flags;
    iid_return_t retval;

    print_string("The User ECC Public Key, to be imported, is:\r\n");

    for (i = 0; i < sizeof(ecc_x9_62_public_key); i++)
    {
        print_hexbyte(ecc_x9_62_public_key[i]);
    }

    print_string("\r\n");

    /********************************
     *  BroadKey IMPORT PUBLIC KEY  *
     ********************************/
    purpose_flags = BK_ECC_KEY_PURPOSE_ECDH_AND_ECDSA;

    print_string("\r\nbk_import_public_key ...");

    retval = bk_import_public_key(curve,
                                  purpose_flags,
                                  ecc_x9_62_public_key,
                                  &ecc_x9_62_public_key_code);
    if (IID_SUCCESS != retval)
    {
        print_error("bk_import_public_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The ECC Public Key Code is:\r\n");

    for (i = 0 ; i < BK_ECC_PUBLIC_KEY_CODE_SIZE_BYTES; i++)
    {
        print_hexbyte(ecc_x9_62_public_key_code[i]);
    }

    print_string("\r\n");

    /********************************
     *  BroadKey EXPORT PUBLIC KEY  *
     ********************************/
    print_string("\r\nbk_export_public_key ...");
    print_num(sizeof(ecc_x9_62_public_key));

    retval = bk_export_public_key(0,
                                  &ecc_x9_62_public_key_code,
                                  temp_ecc_x9_62_public_key,
                                  &curve,
                                  &purpose_flags);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_export_public_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The ECC Public Key is:\r\n");

    for (i = 0; i < sizeof(temp_ecc_x9_62_public_key); i++)
    {
        print_hexbyte(temp_ecc_x9_62_public_key[i]);
    }

    //----------------------------------------------------------------------------
    print_string("\r\n");

    uint8_t input[2] = { 0 };
    do
	{
		print_string(" Input : ");

		iid_usart_read(input, 1);

		print_string(input);
		print_string("\r\n");
	} while (('1' != input[0]) && ('2' != input[0]) && ('3' != input[0]));
    //------------------------------------------------------------------------------

    return 0;
}

//add by Qin 11/19/2020
static uint8_t au_get_randomnum(uint8_t * const message,
        						const uint32_t message_length)
{
#if defined(CLIENT_BOARD)
	uint32_t num_bytes= message_length;

	print_string("client_boad, waiting for Random number\r\n");
	uint8_t input[2] = { 0 };
	 do
		{
			//print_string(" Waiting to read the signature that need to be verified : ");

			iid_usart_read(input, 1);

			//print_string(host_input);
			//print_string("\r\n");
		} while (('#' != input[0]));

	iid_usart_read(message, num_bytes);

	//----------------------------------------------------------
	print_string("The Random number received from host_board is:\r\n");

	int i=0;
	for (i = 0; i < num_bytes; i++)
	{
	   print_hexbyte(message[i]);
	}

	print_string("\r\n");
#endif /* defined(CLIENT_BOARD) */
	return 0;
}

static uint8_t demo_create_private_and_public_key_codes(bk_ecc_private_key_code_t * const ecc_private_key_code,
                                                        bk_ecc_public_key_code_t  * const ecc_public_key_code)
{
    bk_ecc_curve_t curve;
    bk_ecc_key_purpose_t purpose_flags;
    bk_ecc_key_source_t key_source;
    uint32_t i;
    iid_return_t retval;

    /****************************************
     *  BroadKey CREATE PRIVATE KEY CODE    *
     ****************************************/
//    Generation device-unique keys (NIST P-192/224/256 elliptic curve key pairs)
//    private keys: 32 Bytes
//	  public keys: 65
//	  ECDSA signatures: 64
#if defined(CLIENT_BOARD)
    curve = BK_ECC_CURVE_NIST_P256;
    purpose_flags = BK_ECC_KEY_PURPOSE_ECDH_AND_ECDSA;
    key_source = BK_ECC_KEY_SOURCE_PUF_DERIVED;

    //print_string("bk_create_private_key ...");

    retval = bk_create_private_key(curve,
                                    purpose_flags,
                                    0,//NULL TO 0
                                    0,
                                    key_source,
                                    0,//NULL TO 0
                                    ecc_private_key_code);

    if (IID_SUCCESS != retval)
    {
        return 1;
    }


    /********************************************************
     *  BroadKey CREATE PUBLIC KEY FROM PRIVATE KEY CODE    *
     ********************************************************/

    retval = bk_compute_public_from_private_key(ecc_private_key_code, ecc_public_key_code);

    if (IID_SUCCESS != retval)
    {
        return 1;
    }

    /********************************************************
     *  Export the public key code created by the function above*
    ********************************************************/
    //PRE_HIS_ALIGN and POST_HIS_ALIGN macros can be used to align a variable

    PRE_HIS_ALIGN uint8_t temp_ecc_x9_62_public_key[65] POST_HIS_ALIGN = {0};
    uint8_t input[2] = { 0 };

    //print_string("\r\nbk_export_public_key ...");

    retval = bk_export_public_key(0,
    							  ecc_public_key_code,
                                  temp_ecc_x9_62_public_key,
                                  &curve,
                                  &purpose_flags);

    if (IID_SUCCESS != retval)
    {

        return 1;
    }

    print_string("client_board:Waiting Signal to send out public key:\r\n");

    do
	   {
		   iid_usart_read(input, 1);
	   } while (('@' != input[0]));

    print_string("$\r\n");
    for (i = 0; i < sizeof(temp_ecc_x9_62_public_key); i++)
    {
        print_hexbyte(temp_ecc_x9_62_public_key[i]);
    }

    print_string("\r\n");
#endif /* defined(CLIENT_BOARD) */

    return 0;
}


static uint8_t demo_ecdsa_sign_and_verify(const bk_ecc_private_key_code_t * const ecc_private_key_code,
                                          const bk_ecc_public_key_code_t  * const ecc_public_key_code,
                                          const uint8_t                   * const message,
                                          const uint32_t                          message_length)
{
    PRE_HIS_ALIGN uint8_t signature[64] POST_HIS_ALIGN;
    uint16_t signature_length;
    uint8_t message_is_hashed = 0; /* message is not hashed */
    uint32_t i;
    iid_return_t retval;

    signature_length = sizeof(signature);

    /*****************************
     *  BroadKey ECDSA SIGN KEY  *
     *****************************/
#if defined(CLIENT_BOARD)

    retval = bk_ecdsa_sign(ecc_private_key_code,
                            0, /* not a deterministic signature */
                            message,
                            message_length,
                            message_is_hashed,
                            signature,
                            &signature_length);

    if (IID_SUCCESS != retval)
    {
        return 1;
    }

    print_string("client_board: Waiting Signal to send out the signature:\r\n");
    uint8_t input[2] = { 0 };
    do
    	   {

    		   iid_usart_read(input, 1);

    	   } while (('@' != input[0]));

    print_string("!\r\n");
    for (i = 0; i < signature_length; i++)
    {
        print_hexbyte(signature[i]);
    }

    print_string("\r\n");
#endif /* defined(CLIENT_BOARD) */

    /*******************************
	 *  BroadKey ECDSA VERIFY using imported public key by noke *
	 *******************************/
#if defined(HOST_BOARD)
    bk_ecc_curve_t curve = BK_ECC_CURVE_NIST_P256;

    PRE_HIS_ALIGN uint8_t ecc_x9_62_public_key[65] POST_HIS_ALIGN = {0};
	PRE_HIS_ALIGN uint8_t temp_ecc_x9_62_public_key[65] POST_HIS_ALIGN = {0};
	PRE_HIS_ALIGN bk_ecc_public_key_code_t ecc_x9_62_public_key_code POST_HIS_ALIGN;
	bk_ecc_key_purpose_t purpose_flags;

	/********************************
	 *  BroadKey IMPORT PUBLIC KEY  *
	 ********************************/
	purpose_flags = BK_ECC_KEY_PURPOSE_ECDH_AND_ECDSA;

	print_string("host_board: Asking for public key\r\n");
	print_string("@\r\n");
	uint8_t host_input[2] = { 0 };
	 do
		{
			iid_usart_read(host_input, 1);

		} while (('$' != host_input[0]));

	iid_usart_read(ecc_x9_62_public_key, 65);
	//----------------------------------------------------------

	print_string("host_board: Asking for signature to verify\r\n");
	print_string("@\r\n");
	PRE_HIS_ALIGN uint8_t temp_signature[64] POST_HIS_ALIGN ={0};
	host_input[0] = '0';
	 do
		{

			iid_usart_read(host_input, 1);

		} while (('!' != host_input[0]));

	iid_usart_read(temp_signature, 64);

	//----------------------------------------------------------
	print_string("The User ECC Public Key, to be imported, is:\r\n");

	for (i = 0; i < sizeof(ecc_x9_62_public_key); i++)
	{
	   print_hexbyte(ecc_x9_62_public_key[i]);
	}

	print_string("\r\n");

	print_string("\r\n");
	print_string("\r\n Changing public key to Ecc Public Key Code ...");

	retval = bk_import_public_key(curve,
								  purpose_flags,
								  ecc_x9_62_public_key,
								  &ecc_x9_62_public_key_code);
	if (IID_SUCCESS != retval)
	{
		print_error("bk_import_public_key", retval);
		return 1;
	}

	print_string("done!\r\n");

	print_string("\r\n");
	print_string("The ECC Public Key Code created by imported public key is:\r\n");

	for (i = 0 ; i < BK_ECC_PUBLIC_KEY_CODE_SIZE_BYTES; i++)
	{
		print_hexbyte(ecc_x9_62_public_key_code[i]);
	}

	print_string("\r\n");

	//--------------------------------------------------------------------

	print_string("\r\n");
    print_string("The client board signed signature need to be verified is:\r\n");

	for (i = 0; i < sizeof(temp_signature); i++)
	{
		print_hexbyte(temp_signature[i]);
	}

	print_string("\r\n");

	print_string("\r\n The host board is using imported public key to verify signature:...\r\n");

	retval =  bk_ecdsa_verify(&ecc_x9_62_public_key_code,
							message,
							message_length,
							message_is_hashed,
							&temp_signature,
							signature_length);

	if (IID_SUCCESS != retval)
	{
		if (IID_INVALID_SIGNATURE == retval)
		{
			print_string("Invalid signature to the given message\r\n");
		}
		else
		{
			print_error("bk_ecdsa_verify", retval);
		}

		return 1;
	}

	print_string("Signature Verified! \r\n done!\r\n");
#endif /* defined(HOST_BOARD) */

    return 0;
}

static uint8_t demo_ecdh_shared_secret(const bk_ecc_private_key_code_t * const ecc_private_key_code,
                                       const bk_ecc_public_key_code_t  * const ecc_public_key_code)
{
    uint32_t i;
    PRE_HIS_ALIGN uint8_t shared_secret[32] POST_HIS_ALIGN;
    iid_return_t retval;

    print_string("bk_ecdh_shared_secret ...");

    retval = bk_ecdh_shared_secret(ecc_private_key_code,
                                    ecc_public_key_code,
                                    shared_secret);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_ecdh_shared_secret", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The ECDH shared secret is:\r\n");

    for (i = 0; i < sizeof(shared_secret); i++)
    {
        print_hexbyte(shared_secret[i]);
    }

    print_string("\r\n");

    return 0;
}

static uint8_t demo_generate_and_process_cryptogram(const bk_ecc_private_key_code_t * const sender_ecc_private_key_code,
                                                    const bk_ecc_public_key_code_t  * const sender_ecc_public_key_code)
{
    PRE_HIS_ALIGN uint8_t rec_private_key[32] POST_HIS_ALIGN = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                                                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                                                0x00,0x00,0x00,0x2B,0x12,0x0F,0x67,0x21};
    PRE_HIS_ALIGN bk_ecc_private_key_code_t rec_ecc_private_key_code POST_HIS_ALIGN;
    PRE_HIS_ALIGN bk_ecc_public_key_code_t rec_ecc_public_key_code POST_HIS_ALIGN;
    PRE_HIS_ALIGN uint8_t plaintext[32] POST_HIS_ALIGN = {'I', 'N', 'T', 'R', 'I', 'N', 'S', 'I',
                                                          'C', 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89,
                                                          0xab, 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89,
                                                          0xab, 0xcd, 0xef, 0x10, 0x23, 0x45, 0x67, 0x89};
    PRE_HIS_ALIGN uint8_t rec_plaintext[sizeof(plaintext)] POST_HIS_ALIGN;
    PRE_HIS_ALIGN uint8_t cryptogram[BK_ECC_CRYPTOGRAM_HEADER_SIZE_BYTES + 64 + sizeof(plaintext)] POST_HIS_ALIGN;
    PRE_HIS_ALIGN uint32_t cryptogram_length POST_HIS_ALIGN = sizeof(cryptogram);
    PRE_HIS_ALIGN uint32_t rec_plaintext_length POST_HIS_ALIGN = sizeof(rec_plaintext);
    PRE_HIS_ALIGN uint8_t derived_public_key_from_cryptogram[65] POST_HIS_ALIGN; /* size depends on the curve, here it is maximum to support all */
    uint8_t counter64_sender[8] = { 0 }; /* counter is set to all zeros */
    uint8_t counter64_receiver[8] = { 0 };
    bk_ecc_cryptogram_type_t cryptogram_type;
    bk_ecc_curve_t curve;
    bk_ecc_key_purpose_t purpose_flags;
    bk_ecc_key_source_t key_source;
    uint32_t i;
    iid_return_t retval;

    /*************************************************************************
     *  BroadKey CREATE PRIVATE KEY CODE FROM USER PROVIDED KEY FOR RECEIVER *
     *************************************************************************/
    curve = BK_ECC_CURVE_NIST_P256;
    purpose_flags = BK_ECC_KEY_PURPOSE_ECDH_AND_ECDSA;
    key_source = BK_ECC_KEY_SOURCE_USER_PROVIDED;

    print_string("bk_create_private_key from user ...");

    retval = bk_create_private_key(curve,
                                   purpose_flags,
                                   0, /*NULL TO 0 , Not using usage context */
                                   0, /* Not using usage length */
                                   key_source,
                                   rec_private_key,
                                   &rec_ecc_private_key_code);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_create_private_key from user", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The RECEIVER Private Key Code is:\r\n");

    for (i = 0; i < BK_ECC_PRIVATE_KEY_CODE_SIZE_BYTES; i++)
    {
        print_hexbyte(rec_ecc_private_key_code[i]);
    }

    print_string("\r\n");

    /************************************************************
     *  BroadKey CREATE PUBLIC KEY CODE FOR RECEIVER            *
     ************************************************************/
    print_string("\r\nbk_compute_public_from_private_key ...");

    retval = bk_compute_public_from_private_key(&rec_ecc_private_key_code, &rec_ecc_public_key_code);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_compute_pubic_key_from_private_key", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The ECC  RECEIVER Public Key Code is:\r\n");

    for (i = 0 ; i < BK_ECC_PUBLIC_KEY_CODE_SIZE_BYTES; i++)
    {
        print_hexbyte(rec_ecc_public_key_code[i]);
    }

    print_string("\r\n");

    /*********************************
     * GENERATE CRYPTOGRAM BY SENDER *
     *********************************/
    print_string("\r\nbk_generate_cryptogram ...");

    retval = bk_generate_cryptogram(&rec_ecc_public_key_code,
                                    sender_ecc_private_key_code,
                                    BK_ECC_CRYPTOGRAM_TYPE_ECDH_STATIC,
                                    counter64_sender,
                                    plaintext,
                                    sizeof(plaintext),
                                    cryptogram,
                                    &cryptogram_length);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_generate_cryptogram", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("GENERATED CRYPTOGRAM is:\r\n");

    for (i = 0 ; i < cryptogram_length; i++)
    {
        print_hexbyte(cryptogram[i]);
    }

    print_string("\r\n");

    /******************************************
     * GET SENDER PUBLIC KEY FROM CRYPTOGRAM  *
     ******************************************/
    print_string("\r\nbk_get_public_key_from_cryptogram ...");

    retval = bk_get_public_key_from_cryptogram(0,
                                               curve,
                                               cryptogram,
                                               cryptogram_length,
                                               derived_public_key_from_cryptogram);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_get_public_key_from_cryptogram", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("The Derived PUBLIC KEY from CRYPTOGRAM is:\r\n");

    for (i = 0 ; i < sizeof(derived_public_key_from_cryptogram); i++)
    {
        print_hexbyte(derived_public_key_from_cryptogram[i]);
    }

    print_string("\r\n");

    /**********************************
     * PROCESS CRYPTOGRAM BY RECEIVER *
     **********************************/
    print_string("\r\nbk_process_cryptogram ...");

    retval = bk_process_cryptogram(&rec_ecc_private_key_code,
                                    sender_ecc_public_key_code,
                                    &cryptogram_type,
                                    counter64_receiver,
                                    cryptogram,
                                    cryptogram_length,
                                    rec_plaintext,
                                    &rec_plaintext_length);

    if (IID_SUCCESS != retval)
    {
        print_error("bk_process_cryptogram", retval);
        return 1;
    }

    print_string("done!\r\n");

    print_string("RECIEVED PLAINTEXT is:\r\n");

    for (i = 0 ; i < sizeof(rec_plaintext); i++)
    {
        print_hexbyte(rec_plaintext[i]);
    }

    print_string("\r\n");

    return 0;
}
#endif /* defined(BK_CONFIGURATION_PRO_ENABLED) */

static void read_ac(uint8_t * const ac_data)
{
    uint16_t number_of_bytes = 0;
    uint8_t buffer[1];
    bool valid_char;
    uint8_t value;

    do
    {
        valid_char = false;
        do
        {
            iid_usart_read(buffer, 1);

            if (('0' <= *buffer) && ('9' >= *buffer))
            {
                value = *buffer - '0';
                valid_char = true;
            }
            else if (('A' <= *buffer) && ('F' >= *buffer))
            {
                value = *buffer - 'A' + 10;
                valid_char = true;
            }
            else if (('a' <= *buffer) && ('f' >= *buffer))
            {
                value = *buffer - 'a' + 10;
                valid_char = true;
            }
        }
        while (false == valid_char);

        if(0x01 == (number_of_bytes & 0x01))
        {
            ac_data[number_of_bytes / 2] |= value;
        }
        else
        {
            ac_data[number_of_bytes / 2] = value << 4;
        }

        number_of_bytes++;
    } while (number_of_bytes < (2 * BK_AC_SIZE_BYTES));
}
