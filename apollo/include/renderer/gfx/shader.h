#pragma once

#include "core/core.h"

/*
 * @enum: apShaderType
 * @brief: enum for shader types
 * @desc:
 *	holds enum values for shader types
*/
enum apShaderType {
	AP_VERTEX_SHADER			= 0x000,
	AP_FRAGMENT_SHADER			= 0x001,
	AP_GEOMETRY_SHADER			= 0x002,
	AP_COMPUTE_SHADER			= 0x003
};

/*
 * @struct: apShader
 * @brief: shader struct
 * @desc:
 *	represents a shader (not a shader program!!!)
 *	represents vertex_shader / fragment_shader / geometry_shader / compute_shader etc.
*/
struct apShader;
typedef struct apShader apShader;

/*
 * @func: AP_shdr_create
 * @params:
 *	- file_path [const APfilepath_t (const char *)]: file path to where the shader is held
 *	- type [enum apShaderType]: type of the shader
 * @ret: apShader *
 * @brief: creates a shader
 * @desc:
 *	creates and registers a shader
 *	if file_path is not NULL, also sets the shader source and compiles the shader
 *	if file_path is NULL, does not compile the shader. To compile the shader again use @AP_shdr_set_src
*/
apShader APOLLO_API *AP_shdr_create(const APfilepath_t file_path, enum apShaderType type);

/*
 * @func: AP_shd_restroy
 * @params:
 *	- shader [struct apShader *]: pointer to shader object
 * @ret: void
 * @brief: destroys shader
 * @desc:
 *	destroys as well as deregisters (deletes) the shader
 *	frees the allocated source
 *	frees the allocated memory for the struct iteself
*/
void APOLLO_API AP_shdr_destroy(struct apShader *shader);

/*
 * @func: AP_shdr_set_src
 * @params:
 *	- shader [struct apShader *]: pointer to shader object
 *	- file_path [const APfilepath_t (const char *)]: file path of where the shader is held
 * @ret: void
 * @brief: sets the shader source
 * @desc:
 *	sets the shader source as well as compiles it 
 *	does not create a new shader id, to create a new shader use @AP_shdr_create
 *	frees the previously allocated source memory
*/
void APOLLO_API AP_shdr_set_src(struct apShader *shader, const APfilepath_t file_path);

/*
 * @func: AP_shdr_get_id
 * @params:
 *	- shader [const struct apShader *]: pointer to shader object of which's id you want
 * @ret: APu32
 * @brief: returns the shader id
 * @desc:
 *	returns the shader id by value
*/
APu32 APOLLO_API AP_shdr_get_id(const struct apShader *shader);

/*
 * @func: AP_shdr_get_src
 * @params:
 *	- shader [const struct apShader *]: pointer to shader object of which's source you want
 * @ret: const char *
 * @brief: returns shader source
 * @desc:
 *	returns the shader source of the shader
*/
const char APOLLO_API *AP_shdr_get_src(const struct apShader *shader);

/*
 * @func: AP_shdr_copy
 * @params:
 *	- dest [struct apShader *]: pointer to destination shader object
 *	- src [const struct apShader *]: pointer to source shader object
 * @ret: void
 * @brief: copies one shader to the other
 * @desc:
 *	copies the shader source and the shader type from src to dest
 *	does not copy shader id
 *	automatically recompiles the shader once its copied, no need to recompile it using @AL_shdr_recompile
*/
void APOLLO_API AP_shdr_copy(struct apShader *dest, const struct apShader *src);

/*
 * @func: AP_shdr_recompile
 * @params:
 *	- shader [const struct apShader *]: pointer to shader object
 * @ret: void
 * @brief: recompiles shader source
 * desc:
 *	recompiles shader source
*/
void APOLLO_API AP_shdr_recompile(const struct apShader *shader);
