#include "sandbox.h"

#include "Apollo.h"
#include <GL/gl.h>

typedef struct Sandbox {
	apWindow *win;
} Sandbox;

static APi32 g_win_width = 0;
static APi32 g_win_height = 0;
static const char *g_win_title = NULL;

void initialize() {
	// initialize the engine
	AP_initialize();
}

void terminate() {
	// terminate the engine
	AP_terminate();
}

void set_window_dimensions(int width, int height, const char *title) {
	g_win_width = width;
	g_win_height = height;
	g_win_title = title;
}

void on_begin(int argc, const char **argv, struct Sandbox **app_ptr) {
	// create the sandbox
	*app_ptr = (Sandbox *) malloc(sizeof(Sandbox));

	// create the window
	(*app_ptr)->win =
		AP_wndw_create(g_win_width, g_win_height, (char *) g_win_title, NULL);
}

void on_update(float delta_time) {
	glBegin(GL_TRIANGLES);

	glVertex2f(0.0f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);

	glEnd();
}

void on_end(struct Sandbox *app) {
	// destroy the window
	AP_wndw_destroy(app->win);

	// destroy the app 
	free((void *) app);
}

void run_app(struct Sandbox *app) {
	bool is_running = true;
	float last_time = 0.0f;

	AP_wndw_use_wndw(app->win);

	while (is_running) {
		// calculate delta time
		// clear the screen
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		AP_wndw_poll_events();

		on_update(1.0f);

		AP_wndw_swap_buffers(app->win);

		is_running = AP_wndw_is_open(app->win);
	}
}
