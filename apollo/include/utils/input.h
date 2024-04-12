#pragma once

#include "core/core.h"

#include <stdbool.h>

struct apWindow;

// key inputs

enum apKeyStatus {
	AP_KEY_PRESSED				= 0x001,
	AP_KEY_HELD					= 0x002,
	AP_KEY_RELEASED				= 0x003
};

/*
 * @func: AP_input_key_get_code
 * @params:
 *	-
 * @ret: APi32
 * @brief:
 * @desc:
*/
APi32 APOLLO_API AP_input_key_get_code(char key);

APu08 APOLLO_API AP_input_key_get_name(APi32 code); 

bool APOLLO_API AP_input_key_get_pressed(char key);

bool APOLLO_API AP_input_key_get_pressed__code(APi32 code);

enum apKeyStatus APOLLO_API AP_input_key_get_status(char key);

enum apKeyStatus APOLLO_API AP_input_key_get_status__code(APi32 code);
