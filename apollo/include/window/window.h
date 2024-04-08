#pragma once

#include "core/core.h"
#include "window/viewport.h"

#include "cglm/ivec2.h"

#define APOLLO_DEFAULT_WINDOW_WIDTH 1600
#define APOLLO_DEFAULT_WINDOW_HEIGHT 800
#define APOLLO_DEFAULT_WINDOW_TITLE "cApolloEngine: Window"

struct GLFWwindow;
struct GLFWimage;

/*
 * @struct: apWindow
 * @typedef: apWindow
 * @brief: window struct
 * @desc:
 *	handles dimensions, viewport, and window properties
*/
typedef struct apWindow {
	// dimensions (width and height) of the window
	ivec2 dimensions;

	// viewport struct to manage window viewport
	apViewport viewport;

	// title of the window
	char *title;

	// pointer to a GLFWimage used to show icon of the window (DO NOT MODIFY !)
	struct GLFWimage *icon_image;

	// pointer to a GLFWwindow which holds the window (DO NOT MODIFY !)
	struct GLFWwindow *glfw_win;
} apWindow;

/*
 * @func: AP_wndw_create
 * @param:
 *	- width [APi32]: width of the window
 *	- height [APi32]: height of the window
 *	- title [char *]: title of the window
 *	- icon_path [char *]: file path for image file for window icon
 * @ret: apWindow * : pointer to a newly created window
 * @brief: returns the pointer to a newly created window
 * @desc:
 *	a new window is created but it is not set as the current context, make it the current context using function
 *	@AP_wndw_use_wndw
 *	viewport by default is set as the entire window, to change it use @AP_wndw_set_viewport
*/
apWindow APOLLO_API *AP_wndw_create(
		APi32 width,
		APi32 height,
		char *title,
		char *icon_path);
/*
 * @func: AP_wndw_destroy
 * @param:
 *	- window [apWindow *]: pointer to an apollo window
 * @ret: void
 * @brief: destroys the window
 * @desc:
 *	removes the window from current context, then destroys it
 *	also frees the apWindow *, the GLFWwindow * and the GLFWimage *
*/
void APOLLO_API AP_wndw_destroy(apWindow *window);

/*
 * @func: AP_wndw_close
 * @param:
 *	- window [const apWindow *]: pointer to an apollo window
 * @ret: void
 * @brief: closes the window
 * @desc:
 *	closes the window but doesn't destroy it
 *	doesn't remove it as current context
 *	to reopen a window, use @AP_wndw_open
*/
void APOLLO_API AP_wndw_close(const apWindow *window);

/*
 * @func: AP_wndw_open
 * @param:
 *	- window [const apWindow *]: pointer to an apollo window
 * @ret: void 
 * @brief: opens the window
 * @desc:
 *	reopens a closed window
 *	doesn't set it as current context, use @AP_wndw_use_wndw to make it the current context
 *	to close the window, use @AP_wndw_close
*/
void APOLLO_API AP_wndw_open(const apWindow *window);

/*
 * @func: AP_wndw_is_open
 * @param:
 *	- window [const apWindow *]: pointer to an apollo window
 * @ret: bool <stdbool.h>
 * @brief: checks and returns if a window is open
 * @desc:
 *	it checks if a window is open, but doesn't check if the window is the current context or not
 *	to check if a window is the current context, use @AP_wndw_is_current_ctxt
*/
bool APOLLO_API AP_wndw_is_open(const apWindow *window);

/*
 * @func: AP_wndw_is_current_ctxt
 * @param:
 *	- window [const apWindow *]: pointer to an apollo window
 * @ret: bool <stdbool.h>
 * @brief: checks and returns if a window is current context
 * @desc:
 *	it checks if a window is current context, but doesn't check if the window is open or close
 *	to check if a window is open, use @AP_wndw_is_open
*/
bool APOLLO_API AP_wndw_is_current_ctxt(const apWindow *window);

/*
 * @func: AP_wndw_get_current_ctxt
 * @param:
 *	- void
 * @ret: const apWindow * const
 * @brief: returns the current window context
 * @desc:
 *	it returns pointer to a window that is the current context
*/
const apWindow APOLLO_API * const AP_wndw_get_current_ctxt(const apWindow *window);

/*
 * @func: AP_wndw_use_wndw
 * @param:
 *	- window [const apWindow *]: pointer to an apollo window
 * @ret: void
 * @brief: sets the window in use
 * @desc:
 *	sets the window as current context, but doesn't open the window if it is closed
 *	to reopen a window use @AP_wndw_open
*/
void APOLLO_API AP_wndw_use_wndw(const apWindow *window);

/*
 * @func: AP_wndw_free_current_ctxt
 * @param:
 *	- void
 * @ret: void
 * @brief: frees the current context
 * @desc:
 *	frees the current set context but doesn't destroy it
*/
void APOLLO_API AP_wndw_free_current_ctxt(void);

/*
 * @func: AP_wndw_set_width
 * @param:
 *	- window [apWindow *]: pointer to an apollo window
 *	- width [APi32]: width to be set for window
 * @ret: void
 * @brief: sets the width for the window
 * @desc:
 *	doesn't change the width if width is less than or equal to zero
*/
void APOLLO_API AP_wndw_set_width(apWindow *window, APi32 width);

/*
 * @func: AP_wndw_set_height
 * @param:
 *	- window [apWindow *]: pointer to an apollo window
 *	- height [APi32]: height to be set for window
 * @ret: void
 * @brief: sets the height for the window
 * @desc:
 *	doesn't change the height if height is less than or equal to zero
*/
void APOLLO_API AP_wndw_set_height(apWindow *window, APi32 heght);

/*
 * @func: AP_wndw_set_title
 * @param:
 *	- window [apWindow *]: pointer to an apollo window
 *	- title [char *]: title to be set
 * @ret: void
 * @brief: sets the title for the window
 * @desc:
 *	if given title is NULL, title doesn't change
*/
void APOLLO_API AP_wndw_set_title(apWindow *window, char *title);

/*
 * @func: AP_wndw_set_icon
 * @param:
 *	- window [apWindow *]: pointer to an apollo window
 *	- icon_path [char *]: file path to the icon file
 * @ret: void
 * @brief: sets the window icon
 * @desc:
 *	uses stbi_image library to load the icon,
 *	if given icon_path is NULL, previous set icon_path is retained
*/
void APOLLO_API AP_wndw_set_icon(apWindow *window, char *icon_path);

/*
 * @func: AP_wndw_set_viewport
 * @param:
 *	- window [apWindow *]: pointer to an apollo window
 *	- viewport [apViewport]: struct in header "window/viewport.h"
 * @ret: void
 * @brief: sets the viewport
 * @desc:
 *	only alters the viewport of the window, doesn't change the width or height
 *	to change the width or height use @AP_wndw_set_width and @AP_wndw_set_height respectively
*/
void APOLLO_API AP_wndw_set_viewport(apWindow *window, apViewport viewport);

/*
 * @func: AP_wndw_poll_events
 * @param:
 *	- void
 * @ret: void
 * @brief: polls window events
 * @desc:
 *	calls glfwPollEvents in order to poll window events
*/
void APOLLO_API AP_wndw_poll_events(void);

/*
 * @func: AP_wndw_swap_buffers
 * @param:
 *	- window [const apWindow *]: pointer to apollo window
 * @ret: void
 * @brief: swaps buffers
 * @desc:
 *	calls glfwSwapBuffers to swap front and back buffer
*/
void APOLLO_API AP_wndw_swap_buffers(const apWindow *window);
