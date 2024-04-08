#pragma once

struct Sandbox;
typedef struct Sandbox Sandbox;

void initialize();

void terminate();

void set_window_dimensions(int width, int height, const char *title);

void on_begin(int argc, const char **argv, struct Sandbox **app_ptr);

void on_update(float delta_time);

void on_end(struct Sandbox *app);

void run_app(struct Sandbox *app);
