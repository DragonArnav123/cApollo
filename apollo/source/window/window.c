#include "APpch.h"
#include "core/core.h"
#include "window/window.h"

#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include "renderer/stb_image_loader.h"

// hold the current context
const apWindow *g_current_ctx = NULL;

// ap internal
static void APint_set_gl_viewport(const apWindow *window);

apWindow APOLLO_API *AP_wndw_create(
		int width,
		int height,
		char *title,
		char *icon_path) {
	// create the window
	apWindow *win = (apWindow *) malloc(sizeof(apWindow));
	assert(win);

	if (width <= 0)
		width = APOLLO_DEFAULT_WINDOW_WIDTH;
	if (height <= 0)
		height = APOLLO_DEFAULT_WINDOW_HEIGHT;
	if (title == NULL)
		title = APOLLO_DEFAULT_WINDOW_TITLE;

	// set the window properties
	win->dimensions[0] = width;
	win->dimensions[1] = width;
	win->title = title;

	win->glfw_win =
		glfwCreateWindow(width, height, title, NULL, NULL);

	// assert the window
	assert(win->glfw_win);

	// set the viewport as window width and height by default
	win->viewport.bottom_left[0] =
		win->viewport.bottom_left[1] = 0;
	win->viewport.top_right[0] = win->dimensions[0];
	win->viewport.top_right[1] = win->dimensions[1];

	APint_set_gl_viewport(win);

	win->icon_image = (struct GLFWimage *) malloc(sizeof(struct GLFWimage));

	AP_wndw_set_icon(win, icon_path);

	return win;
}

void APOLLO_API AP_wndw_destroy(apWindow *this) {
	// delete the glfw window
	glfwDestroyWindow(this->glfw_win);

	// free the apWindow
	free((void *) this);
}

void APOLLO_API AP_wndw_close(const apWindow *this) {
	glfwSetWindowShouldClose(this->glfw_win, GLFW_TRUE);
}

void APOLLO_API AP_wndw_open(const apWindow *this) {
	glfwSetWindowShouldClose(this->glfw_win, GLFW_FALSE);
}

bool APOLLO_API AP_wndw_is_open(const apWindow *this) {
	return (bool) !glfwWindowShouldClose(this->glfw_win);
}

bool APOLLO_API AP_wndw_is_current_ctxt(const apWindow *window) {
	return (g_current_ctx == window);
}

const apWindow APOLLO_API * const AP_wndw_get_current_ctxt(const apWindow *window) {
	return g_current_ctx;
}

void APOLLO_API AP_wndw_use_wndw(const apWindow *this) {
	glfwMakeContextCurrent(this->glfw_win);
	g_current_ctx = this;
}

void APOLLO_API AP_wndw_free_current_ctxt(void) {
	glfwMakeContextCurrent(NULL);
	g_current_ctx = NULL;
}

void APOLLO_API AP_wndw_set_width(apWindow *this, int width) {
	if (width > 0)
		this->dimensions[0] = width;
	glfwSetWindowSize(this->glfw_win, this->dimensions[0], this->dimensions[1]);
}

void APOLLO_API AP_wndw_set_height(apWindow *this, int height) {
	if (height > 0)
		this->dimensions[1] = height;
	glfwSetWindowSize(this->glfw_win, this->dimensions[0], this->dimensions[1]);
}

void APOLLO_API AP_wndw_set_title(apWindow *this, char *title) {
	if (title != NULL)
		this->title = title;
	glfwSetWindowTitle(this->glfw_win, this->title);
}

void APOLLO_API AP_wndw_set_icon(apWindow *this, char *icon_path) {
	// if path is null, dont bother
	if (icon_path == NULL)
		return;

	// read the necessary data from stbi image

	// Set the texture to be right side up
	stbi_set_flip_vertically_on_load(true);

	// Get the texture data
	unsigned char *image_data = 
		stbi_load(
				icon_path,
				&this->icon_image->width,
				&this->icon_image->height,
				NULL,
				0);

	// Check if data is null
	if (!image_data) {
		// log
		return;
	}

	// allocate memory
	this->icon_image->pixels = (unsigned char *) malloc(sizeof(image_data));

	// memcpy
	memcpy(this->icon_image->pixels, image_data, sizeof(*image_data));
}

void APOLLO_API AP_wndw_set_viewport(apWindow *this, apViewport viewport) {
	// set the bottom left
	this->viewport.bottom_left[0] =
		viewport.bottom_left[0] >= 0 ?
			viewport.bottom_left[0] :
				this->viewport.bottom_left[0];
	this->viewport.bottom_left[1] =
		viewport.bottom_left[1] >= 0 ?
			viewport.bottom_left[1] :
				this->viewport.bottom_left[1];

	// set the top right
	this->viewport.top_right[0] =
		viewport.top_right[0] >= 0 ?
			viewport.top_right[0] :
				this->viewport.top_right[0];
	this->viewport.top_right[1] =
		viewport.top_right[1] >= 0 ?
			viewport.top_right[1] :
				this->viewport.top_right[1];

	// set the viewport
	APint_set_gl_viewport(this);
}

void APOLLO_API AP_wndw_poll_events(void) {
	glfwPollEvents();
}

void APOLLO_API AP_wndw_swap_buffers(const apWindow *window) {
	glfwSwapBuffers(window->glfw_win);
}

static void int_AP_wndw_resize_callback() {
	// todo
}

/*
TODO:
	callbacks
	maybe add a wayfor custom callbacks
*/

static void APint_set_gl_viewport(const apWindow *window) {
	glViewport(
			window->viewport.bottom_left[0],
			window->viewport.bottom_left[1],
			window->viewport.top_right[0],
			window->viewport.top_right[1]);
}
