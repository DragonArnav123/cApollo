#pragma once

#include "core/core.h"

#include "cglm/vec2.h"
#include "cglm/mat4.h"

typedef struct apViewProjMat {
	mat4 view;
	mat4 proj;
} apViewProjMat;

///////////////////////////////////////////
/// Perspective Camera
///////////////////////////////////////////
typedef struct apPerspectiveCam {

} apPerspectiveCam;

///////////////////////////////////////////
///////////////////////////////////////////

///////////////////////////////////////////
/// Orthographic Camera
///////////////////////////////////////////
typedef struct apOrthographicCam {
	// position
	vec2 pos;

	// near clip space
	APf32 min;

	// far clip space
	APf32 max;

	// view proj mat
	struct apViewProjMat view_proj;
} apOrthographicCam;

/*
 * @func: AP_cam_ortho_create
 * @params:
 *	- pos [vec2 (cglm)]: position of the camera
 *	- min [APf32 [float]]: near clip distance
 *	- max [APf32 [float]]: far clip distance
 * @ret: struct apOrthographicCam 
 * @brief: sets a new camera in given memory position
 * @desc:
 *	creates a new orthographic camera in the given position,
 *	for the pos the coordinate system is ->
 *	origin at left bottom corner of the screen and y-axis = windowHeight and x-axis = windowWidth
 *	updates the camera after creating it
*/
struct apOrthographicCam APOLLO_API AP_cam_ortho_create(
		vec2 pos,
		APf32 min,
		APf32 max);

/*
 * @func: AP_cam_ortho_update
 * @params:
 *	- cam [struct apOrthoGraphicCam *]: pointer to camera you want to update
 * @ret: void
 * @brief: updates the camera
 * @desc:
 *	updates the view matrix and the projection matrix of the camera
*/
void APOLLO_API AP_cam_ortho_update(struct apOrthographicCam *cam);
///////////////////////////////////////////
///////////////////////////////////////////
