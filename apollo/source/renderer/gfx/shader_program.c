#include "APpch.h"
#include "renderer/gfx/shader.h"
#include "renderer/gfx/shader_program.h"
#include "log/log.h"

#include "glad/glad.h"

typedef struct apShaderProgram {
	// this id
	APu32 id;

	// vertex shader
	struct apShader *vertex;

	// fragment shader
	struct apShader *fragment;

	// geometry shader
	struct apShader *geometry;
} apShaderProgram;

static APi32 APint_compile_shader_program(struct apShaderProgram *this) {
	// attach the shaders to the program
	glAttachShader(this->id, AP_shdr_get_id(this->vertex));
	glAttachShader(this->id, AP_shdr_get_id(this->fragment));
	/* glAttachShader(program->id, AP_shdr_get_id(program->geometry)); */

	// link the program
	glLinkProgram(this->id);

	// validate the program
	glValidateProgram(this->id);

	// some basic error checking
	APi32 result;
	glGetProgramiv(this->id, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE) {
		// get the length of info log
		APi32 length;
		glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);

		// allocate the log buffer on thet stack
		char log[length + 1]; // + 1 for '\0'

		// get the log
		glGetProgramInfoLog(this->id, length, &length, log);

		AP_LOG_FATAL("%s %d %s %s", "Failed to compile shader program: ", this->id, "\n\t", log);

		return APOLLO_FALSE;
	}

	return APOLLO_TRUE;
}

apShaderProgram APOLLO_API *AP_shdrprog_create(
		const APfilepath_t vfile,
		const APfilepath_t ffile,
		const APfilepath_t gfile) {
	// create the shader program
	struct apShaderProgram *program =
		(struct apShaderProgram *) malloc(sizeof(struct apShaderProgram));

	// create the shader id
	program->id = glCreateProgram();

	// create the shaders
	program->vertex = AP_shdr_create(vfile, AP_VERTEX_SHADER);
	program->fragment = AP_shdr_create(ffile, AP_FRAGMENT_SHADER);
	program->geometry = /* AP_shdr_create(gfile, AP_GEOMETRY_SHADER); */ NULL;

	APi32 result = APint_compile_shader_program(program);

	if (result == APOLLO_FALSE) { } else {
		AP_LOG_LOG("%s %d %s", "Created program: ", program->id, " succesfully!");
	}

	return program;
}
	
void APOLLO_API AP_shdrprog_destroy(struct apShaderProgram *this) {
	// delete the shaders
	AP_shdr_destroy(this->vertex);
	AP_shdr_destroy(this->fragment);
	/* AP_shdr_destroy(this->geometry); */

	APu32 id = this->id;

	// delete the program
	glDeleteProgram(this->id);

	// free the struct iself
	free(this);

	AP_LOG_LOG("%s %d %s", "Deleted program: ", id, " succesfully!");
}

void APOLLO_API AP_shdrprog_bind(const struct apShaderProgram *this) {
	// use the program
	glUseProgram(this->id);
}

void APOLLO_API AP_shdrprog_unbind(void) {
	glUseProgram(0x000);
}

const struct apShader APOLLO_API *AP_shdrprog_get_vertex_shader(
		const struct apShaderProgram *this) {
	return this->vertex;
}

const struct apShader APOLLO_API *AP_shdrprog_get_fragment_shader(
		const struct apShaderProgram *this) {
	return this->fragment;
}

const struct apShader APOLLO_API *AP_shdrprog_get_geometry_shader(const struct apShaderProgram *this) {
	return this->geometry;
}

APu32 APOLLO_API AP_shdrprog_id(const struct apShaderProgram *this) {
	return this->id;
}

void APOLLO_API AP_shdrprog_recompile_shader(struct apShaderProgram *this, enum apShaderType type) {
	switch (type) {
		case AP_VERTEX_SHADER:
			AP_shdr_recompile(this->vertex);
			break;

		case AP_FRAGMENT_SHADER:
			AP_shdr_recompile(this->fragment);
			break;

		case AP_GEOMETRY_SHADER:
			/* AP_shdr_recompile(this->geometry); */
			break;
		
		case AP_COMPUTE_SHADER:
			// do nothing
			break;
	}
}

void APOLLO_API AP_shdrprog_recompile_all_shaders(struct apShaderProgram *this) {
	// recompile the vertex shader
	AP_shdr_recompile(this->vertex);

	// recompile the fragment shader
	AP_shdr_recompile(this->fragment);

	// recompile the geometry shader
	/* AP_shdr_recompile(this->geometry); */
}

void APOLLO_API AP_shdrprog_change_shader_src(
		struct apShaderProgram *this,
		const APfilepath_t file_path,
		enum apShaderType type) {
	switch (type) {
		case AP_VERTEX_SHADER:
			AP_shdr_set_src(this->vertex, file_path);
			break;

		case AP_FRAGMENT_SHADER:
			AP_shdr_set_src(this->fragment, file_path);
			break;

		case AP_GEOMETRY_SHADER:
			AP_shdr_set_src(this->geometry, file_path);
			break;
		
		case AP_COMPUTE_SHADER:
			// do nothing
			break;
	}
}

void APOLLO_API AP_shdprog_change_all_shader_src(
		struct apShaderProgram *this,
		const APfilepath_t vfile,
		const APfilepath_t ffile,
		const APfilepath_t gfile) {
	// set the shader source for the vertex shader
	AP_shdr_set_src(this->vertex, vfile);

	// set the shader source for the fragment shader
	AP_shdr_set_src(this->fragment, ffile);

	// set the shader source for the geometry shader
	/* AP_shdr_set_src(this->geometry, gfile); */
}
