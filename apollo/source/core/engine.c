#include "APpch.h"
#include "core/core.h"
#include "core/engine.h"
#include "log/log.h"
#include "window/window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

static APi32 g_engine_intialization_status = APOLLO_ENGINE_YET_TO_INTIALIZE;

static APi32 initialize_glfw(void) {
	if (!glfwInit()) {
		// failed to intiale glfw
		g_engine_intialization_status = APOLLO_FAILED_TO_INIATILIZE_GLFW;
		AP_LOG_FATAL("%s", "Failed to initialze glfw (windowing)!");
		return APOLLO_FALSE;
	}

	AP_LOG_INFO("%s", "Glfw (windowing) initialized succesfully!");

	return APOLLO_TRUE;
}

static APi32 intialize_opengl(void) {
	if (!gladLoadGLLoader((GLADloadproc) (glfwGetProcAddress)))  {
		// failed to initialize glad
		AP_LOG_FATAL("%s", "Failed to initialze glad (opengl)!");
		g_engine_intialization_status = APOLLO_FAILED_TO_INITIALIZE_OPENGL;
		return APOLLO_FALSE;
	}

	AP_LOG_INFO("%s", "Glad (opengl) initialized succesfully!");
	return APOLLO_TRUE;
}

APi32 APOLLO_API AP_initialize(void) {
	static bool s_engine_initialized = false;

	// if engine is already initialized, we can just skip this
	if (s_engine_initialized == true) {
		return APOLLO_ENGINE_INITIALIZED;
	}

	if (initialize_glfw() == APOLLO_FALSE) 
		return APOLLO_FALSE;

	// create a valid context
	struct apWindow *init_window = AP_wndw_create(800, 800, "Apollo: Initialize", NULL);

	// set as the current context
	AP_wndw_use_wndw(init_window);

	if (intialize_opengl() == APOLLO_FALSE)
		return APOLLO_FALSE;

	// destroy the window
	AP_wndw_destroy(init_window);

	// engine intialized
	s_engine_initialized = true;
	g_engine_intialization_status = APOLLO_ENGINE_INITIALIZED;

	AP_LOG_INFO("%s", "Apollo Engine initialized succesfully!");

	return APOLLO_TRUE;
}

void APOLLO_API AP_terminate(void) {
	// terminate the engine
	glfwTerminate();

	AP_LOG_INFO("%s", "Apollo Engine terminated succesfully!");

	g_engine_intialization_status = APOLLO_ENGINE_TERMINATED;
}

APi32 APOLLO_API AP_get_engine_initialization_status(void) {
	return g_engine_intialization_status;
}
