#pragma once

#include "core/core.h"

struct apShader;
typedef struct apShader apShader;
enum apShaderTpye;

/*
 * @struct: apShaderProgram
 * @brief: represents a shader program
 * @desc:
 *	represents a shader program, holds pointers to 
 *		vertex shader 
 *		fragment shader
 *		geometry shader
*/
struct apShaderProgram;
typedef struct apShaderProgram apShaderProgram;

/*
 * @func: AP_shdrprog_create
 * @params:
 *	- vfile [const APfilepath_t]: file path to vertex shader
 *	- ffile [const APfilepath_t]: file path to fragment shader
 *	- gfile [const APfilepath_t]: file path to geometry shader
 * @ret: apShaderProgram *
 * @brief: creates a new shader program
 * @desc:
 *	creates a new shader program and the associated files
 *	if any file path is NULl, it skips the compilation of that shader
 *	to change the src of any shader use @AP_shdrprog_change_shader_src
 *	to recompile a particular shader use @AP_shdrprog_recompile_shader
 *	to recompile all shaders use @AP_shdrprog_recompile_all_shaders
*/
apShaderProgram APOLLO_API *AP_shdrprog_create(
		const APfilepath_t vfile,
		const APfilepath_t ffile,
		const APfilepath_t gfile);

/*
 * @func: AP_shdrprog_destroy
 * @params:
 *	- program [struct apShaderProgram *]: pointer to program object you want to destroy
 * @ret: void
 * @brief: destroys a shader program
 * @desc:
 *	destroys the shader program
 *	destroys the associated shaders as well
 *	frees the associated resources as well
*/
void APOLLO_API AP_shdrprog_destroy(struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_bind
 * @params:
 *	- program [const struct apShaderProgram]: pointer to program object you want to bind
 * @ret: void
 * @brief: binds the shader program
 * @desc:
 *	binds the program and the shaders
 *	does not set uniforms, to set uniforms use @AP_shdrprog_set_uniform...
*/
void APOLLO_API AP_shdrprog_bind(const struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_unbind
 * @params:
 *	- void
 * @ret: void
 * @brief: unbinds shader program
 * @desc:
 *	unbinds current shader program, i.e. binds NULL to shader program
*/
void APOLLO_API AP_shdrprog_unbind(void);

/*
 * @func: AP_shdrprog_get_vertex_shader
 * @params:
 *	- program [const struct apShaderProgram *]: pointer to program object of which's shader you want
 * @ret: const apShader *
 * @brief: returns the vertex shader 
 * @desc:
 *	returns a const version of the vertex shader of the program
*/
const struct apShader APOLLO_API *AP_shdrprog_get_vertex_shader(const struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_get_fragment_shader
 * @params:
 *	- program [const struct apShaderProgram *]: pointer to program object of which's shader you want
 * @ret: const apShader *
 * @brief: returns the fragment shader 
 * @desc:
 *	returns a const version of the fragment shader of the program
*/
const struct apShader APOLLO_API *AP_shdrprog_get_fragment_shader(const struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_get_geometry_shader
 * @params:
 *	- program [const struct apShaderProgram *]: pointer to program object of which's shader you want
 * @ret: const apShader *
 * @brief: returns the geometry  shader 
 * @desc:
 *	returns a const version of the geometry shader of the program
*/
const struct apShader APOLLO_API *AP_shdrprog_get_geometry_shader(const struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_id
 * @params:
 *	- program [const struct apShaderProgram *]: pointer to program object of which's shader you want
 * @ret: APu32
 * @brief: returns the shader program id 
 * @desc:
 *	returns the id of the shader program
*/
APu32 APOLLO_API AP_shdrprog_id(const struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_recompile_shader
 * @params:
 *	- program [struct apShaderProgram *]: pointer to the program you want to recompile
 *	- type [enum apShaderType]: which shader you want to recompile
 * @ret: void
 * @brief: recompiles a particular shader
 * @desc:
 *	recompiles the shader using @AP_shdr_recompile, follows all the caviats of the same
 *	to recompile all the shaders use @AP_shdrprog_recompile_all_shaders
*/
void APOLLO_API AP_shdrprog_recompile_shader(struct apShaderProgram *program, enum apShaderType type);

/*
 * @func: AP_shdrprog_recompile_all_shaders
 * @params:
 *	- program [struct apShaderProgram *]: pointer to the program you want to recompile
 * @ret: void
 * @brief: recompiles the shader program
 * @desc:
 *	recompiles all the shaders of the program, to recompile just a specific shader use @AP_shdrprog_recompile_shader
*/
void APOLLO_API AP_shdrprog_recompile_all_shaders(struct apShaderProgram *program);

/*
 * @func: AP_shdrprog_change_shader_src
 * @params:
 *	- program [struct apShaderProgram *]: pointer to the program you want to recompile
 *	- file_path [const APfilepath_t]: path to the shader file
 * @ret: void
 * @brief: changes the shader source
 * @desc:
 *	changes the shader source and recompiles the shader
 *	to change the source of all shaders use @AP_shdprog_change_all_shader_src
 *	to recompile the shader use @AP_shdrprog_recompile_shader
 *	to recompile all shaders use @AP_shdrprog_recompile_all_shaders
*/
void APOLLO_API AP_shdrprog_change_shader_src(
		struct apShaderProgram *program,
		const APfilepath_t file_path,
		enum apShaderType type);

/*
 * @func: AP_shdrprog_change_all_shader_src
 * @params:
 *	- program [struct apShaderProgram *]: pointer to the program you want to recompile
 *	- vfile [const APfilepath_t]: path to the vertex shader file
 *	- ffile [const APfilepath_t]: path to the fragment shader file
 *	- gfile [const APfilepath_t]: path to the geometry shader file
 * @ret: void
 * @brief: changes the shader source
 * @desc:
 *	changes all the shaders' source and recompiles the shader the shader
 *	to change the source of a particular shader use @AP_shdprog_change_shader_src
*/
void APOLLO_API AP_shdprog_change_all_shader_src(
		struct apShaderProgram *program,
		const APfilepath_t vfile,
		const APfilepath_t ffile,
		const APfilepath_t gfile);

// todo: set uniform
