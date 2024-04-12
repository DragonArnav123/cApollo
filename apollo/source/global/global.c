#include "APpch.h"
#include "global/global.h"
#include "core/core.h"
#include "log/log.h"
#include "window/window.h"
#include "renderer/gfx/vertex_array.h"
#include "renderer/gfx/shader.h"
#include "scene/camera/camera.h"

static struct apGlobal *g_ap_global = NULL;

struct apGlobal *APint_global_initialize() {
	if (g_ap_global == NULL) {
		AP_LOG_INFO("%s", "Initializing Apollo GLOBAL struct.");

		// create the new global
		memset(g_ap_global, 0, sizeof(struct apGlobal));

		// set everything to zero
		(*g_ap_global) = (struct apGlobal) { 0 };
	} 

	if (g_ap_global != NULL)
		AP_LOG_INFO("%s", "Initialized Apollo GLOBAL struct succesfully!");
	else
		AP_LOG_FATAL("%s", "Failed to initialize Apollo GLOBAL struct succesfully!");

	return g_ap_global;
}

struct apGlobal *APint_global_get() {
	return g_ap_global;
}

void APint_gloal_terminate() {
	free(g_ap_global);
}
