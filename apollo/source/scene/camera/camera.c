#include "APpch.h"
#include "scene/camera/camera.h"
#include "global/global.h"
#include "window/window.h"

#include "cglm/cglm.h"

///////////////////////////////////////////
/// Orthographic Camera
///////////////////////////////////////////
struct apOrthographicCam APOLLO_API AP_cam_ortho_create(
		vec2 pos,
		APf32 min,
		APf32 max) {
	struct apOrthographicCam cam = {
		.pos = { pos[0], pos[1] },
		.min = min,
		.max = max
	};

	// update the camera
	AP_cam_ortho_update(&cam);

	return cam;
}

void APOLLO_API AP_cam_ortho_update(struct apOrthographicCam *this) {
	// set the view matrix
	glm_mat4_identity(this->view_proj.view);

	// @todo: check to see if we should use window instead of viewport
	const struct apWindow *window = AP_wndw_get_current_ctxt();

	// projection matrix
	glm_ortho(
			window->viewport.bottom_left[0],
			window->viewport.bottom_left[1], 
			window->viewport.top_right[0],
			window->viewport.top_right[1], 
			this->min,
			this->max,
			this->view_proj.proj);
}
///////////////////////////////////////////
///////////////////////////////////////////
