#pragma once

#include "core/core.h"

#define APOLLO_ENGINE_YET_TO_INTIALIZE			-0x1899
#define APOLLO_ENGINE_INITIALIZED				-0x1900
#define APOLLO_FAILED_TO_INIATILIZE_GLFW		-0x1901
#define APOLLO_FAILED_TO_INITIALIZE_OPENGL		-0x1902
#define APOLLO_ENGINE_TERMINATED				-0x1903

/*
 * @func: AP_initialize
 * @param:
 *	- void
 * @ret: APi32
 * @brief: initializes the dependencies
 * @desc:
 *	initializes the dependencies and the engine as well as opengl
 *	possible return values include:
 *		APOLLO_TRUE: engine has been intialized properly
 *		APOLLO_FALSE: engine has not been intialized properly
 *		APOLLO_ENGINE_INITIALIZED: engine has already been initialized
 *	does not return the error in initialization, to query the error occured
 *	use @AP_get_engine_initialization_status
*/
APi32 APOLLO_API AP_initialize(void);

/*
 * @func: AP_terminate
 * @param:
 *	- void
 * @ret: void
 * @brief: terminates the engine
 * @desc:
 *  terminates the dependencies as well as frees any engine-allocated memory
 *  frees the window set as current context but does not free any other window
 *  frees the current active shader
 *  frees the current active meshes
 *  frees the current active material
*/
void APOLLO_API AP_terminate(void);

/*
 * @func: AP_get_engine_initialization_status
 * @param:
 *	- void
 * @ret: APi32
 * @brief: returns engine intialization status
 * @desc:
 *	returns the engine intialization statis
 *	possible return values include:
 *		APOLLO_ENGINE_YET_TO_INTIALIZE: function @AP_initialize hasn't been called yet			
 *		APOLLO_ENGINE_INITIALIZED: engine has been initialized succesfully
 *		APOLLO_FAILED_TO_INIATILIZE_GLFW: engine failed to initialize glfw
 *		APOLLO_FAILED_TO_INITIALIZE_OPENGL: engine failed to initialize opengl
 *		APOLLO_ENGINE_TERMINATED: engine has been terminated
 *	since glfw is initialized before OpenGL, it is possible for the issue with GLFW be fixed 
 *	and engine still not intialize due to a potential issue with OpenGL
 *	If engine is not yet initialized, this function does not initialize the engine 
 *	to initialize the engine calle @AP_initialize. To terminate the engine call @AP_terminate
*/
APi32 APOLLO_API AP_get_engine_initialization_status(void);
