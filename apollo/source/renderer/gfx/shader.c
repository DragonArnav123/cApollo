#include "APpch.h"
#include "renderer/gfx/shader.h"
#include "utils/file_manager.h"
#include "log/log.h"

#include "glad/glad.h"

typedef struct apShader {
	// shader id
	APu32 id;

	// shader source code
	char *src;

	// shader type
	enum apShaderType type;
} apShader;

static GLenum APint_get_shader_type(enum apShaderType type) {
	switch (type) {
		case AP_VERTEX_SHADER:
			return GL_VERTEX_SHADER;

		case AP_FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;

		case AP_GEOMETRY_SHADER:
			return GL_GEOMETRY_SHADER;

		case AP_COMPUTE_SHADER:
			return GL_COMPUTE_SHADER;
	}
}

static APi08 APint_compile_shader(const apShader *this) {
	// set the shader source
	glShaderSource(
			this->id,
			1,
			(const GLchar *const *) &this->src, NULL);

	// compile the shader
	glCompileShader(this->id);

	// do some basic error checking
	APi32 result;

	glGetShaderiv(this->id, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE) {
		// get the info log length
		APi32 length;
		glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &length);

		// allocate the buffer on the stack
		char *log = (char *) alloca(length + 1); // + 1 for '\0'

		// get the log
		glGetShaderInfoLog(this->id, length, &length, log);

		// print the log
		AP_LOG_FATAL("%s %d %s %s", "Could not compile shader src for shader: ", this->id, "\n\t", log);

		return APOLLO_FALSE;
	}

	return APOLLO_TRUE;
}

apShader APOLLO_API *AP_shdr_create(
		const APfilepath_t file_path, 
		enum apShaderType type) {
	// create the shader
	struct apShader *shader =
		(struct apShader *) malloc(sizeof(struct apShader));

	// create the shader id
	shader->id = glCreateShader(APint_get_shader_type(type));
	shader->type = type;

	if (file_path == NULL) {
		AP_LOG_WARN("%s", "No source provided for shader, skipping compilation of shader.");
	} else {
		AP_shdr_set_src(shader, file_path);
	}

	AP_LOG_LOG("%s", "Completed shader generation succesfully!.");

	return shader;
}

void APOLLO_API AP_shdr_destroy(struct apShader *this) {
	AP_LOG_INFO("%s %d %c %s", "Deleted shader: ", this->id, ' ', "succesfully.");

	// destroy the shader id
	glDeleteShader(this->id);

	this->id = 0;
	// free the source
	free(this->src);
}

void APOLLO_API AP_shdr_set_src(
		struct apShader *this,
		const APfilepath_t file_path) {
	// read from the file
	char *shader_src = AP_fm_read_from_file(file_path);

	// check if src is valid
	if (shader_src == NULL) {
		AP_LOG_FATAL("%s", "Source given for shader is NULL. Could not update shader source!");
		free(shader_src);

		return;
	}

	AP_LOG_INFO("%s %d %s %s", "Source for shader_id : ", this->id, "\n\t", shader_src);

	// if we already have one source, free it
	if (this->src != NULL) {
		free(this->src);
	}

	// allocate the memory
	this->src = (char *) malloc(sizeof(char) * (strlen(shader_src) + 1)); // + 1 for '\0'

	// copy the shader
	strcpy(this->src, shader_src);
	this->src[strlen(shader_src)] = '\0';

	// compile the shader
	APi32 result = APint_compile_shader(this);

	if (result == APOLLO_TRUE)
		AP_LOG_INFO("%s %d", "Shader was compiled succesfully! id: ", this->id);
	else 
		AP_LOG_FATAL("%s %d", "Failed to compile shader: ", this->id);

	free(shader_src);
}

APu32 APOLLO_API AP_shdr_get_id(const struct apShader *this) {
	return this->id;
}

const char APOLLO_API *AP_shdr_get_src(const struct apShader *this) {
	return this->src;
}

void APOLLO_API AP_shdr_copy(
		struct apShader *dest, 
		const struct apShader *src) {
	// copy the concerned data to the dest
	// first free the allocated resources
	free(dest->src);

	// allocate new memory to dest
	dest->src = 
		(char *) malloc(
				sizeof(char) * (strlen(src->src) + 1)); // + 1 for '\0'
	dest->type = src->type;

	// copy the src
	strcpy(dest->src, src->src);
	
	// compile the shader
	APint_compile_shader(dest);
}

void APOLLO_API AP_shdr_recompile(const struct apShader *shader) {
	// recompile the shader
	APint_compile_shader(shader);
}
