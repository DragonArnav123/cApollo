#pragma once

struct apWindow;
struct apVertexArray;
struct apShader;
struct apOrthographicCam;
struct apPerspectiveCam;

typedef struct apGlobal {
	// current active window
	struct apWindow *active_window;

	// current active vertex array
	struct apVertexArray *active_vao;

	// current active shader
	struct apShader *active_shader;

	// current in use orthographic camera
	struct apOrthographicCam *active_cam_ortho;
	
	// current in use perspective camera
	struct apPerspectiveCam *active_cam_persp;
} apGlobal;

struct apGlobal *APint_global_initialize();
apGlobal *APint_global_get();
void APint_global_terminate();
