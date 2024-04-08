#include "renderer/gfx/buffer.h"
#include "log/log.h"

#include "glad/glad.h"

typedef struct apBuffer {
	// id for the buffer
	APu32 id;

	// buffer data
	void *buffer;

	// buffer data size in bytes
	APu32 size;

	// buffer type
	enum apBufferType type;

	// is the buffer dynamic (changing) or static
	bool is_static; 
} apBuffer;

static GLenum APint_get_gl_buffer_type(enum apBufferType type) {
	switch (type) {
		case AP_VERTEX_BUFFER:
			return GL_ARRAY_BUFFER;

		case AP_INDEX_BUFFER:
			return GL_ELEMENT_ARRAY_BUFFER;
	}

	return APOLLO_FALSE;
}

struct apBuffer APOLLO_API *AP_buffer_create(
		void *data,
		APu32 data_size,
		enum apBufferType type,
		bool is_static) {
	// allocate memory
	struct apBuffer *buffer= 
		(struct apBuffer *) malloc(sizeof(struct apBuffer));

	// register the this
	glGenBuffers(1, &buffer->id);

	// set the this type
	buffer->type = type;
	buffer->is_static = is_static;

	// check if data is valid
	if (data == NULL) {
		AP_LOG_WARN("%s", "Data given is NULL. Skipping filling buffer data!");
	} else if (data_size == 0) {
		// check if size is valid
		AP_LOG_FATAL("%s", "Data size given for buffer is 0. Skipping filling buffer data!");
	} else {
		// set this data
		AP_buffer_set_data(buffer, data, data_size);
	}

	AP_LOG_LOG(
			"%s %s %s",
			"Compiled creating ",
			type == AP_VERTEX_BUFFER ?
				"vertex buffer" :
				"fragment buffer",
			" succesfully!");;

	return buffer;
}

void APOLLO_API AP_buffer_destroy(struct apBuffer *this) {
	AP_LOG_INFO("%s %d %c %s", "Deleted buffer: ", this->id, ' ', "succesfully.");

	// delete the gl buffer
	glDeleteBuffers(1, &this->id);

	// free the data
	free(this->buffer);

	// free the buffer itself
	free((void *) this);
}

void APOLLO_API AP_buffer_bind(const struct apBuffer *this) {
	// bind the buffer
	GLenum type = APint_get_gl_buffer_type(this->type);

	glBindBuffer(type, this->id);
}

void APOLLO_API AP_buffer_unbind(enum apBufferType type) {
	// bind the buffer
	GLenum glType = APint_get_gl_buffer_type(type);

	glBindBuffer(glType, 0);
}

void APOLLO_API AP_buffer_set_data(struct apBuffer *this, void *data, APu32 data_size) {
	// set the buffer properties
	this->buffer = data;
	this->size = data_size;

	// get the buffer type
	GLenum type = APint_get_gl_buffer_type(this->type);

	APu16 type_size = 0u;

	switch (this->type) {
		case AP_VERTEX_BUFFER:
			type_size = sizeof(GLfloat);
			break;

		case AP_INDEX_BUFFER:
			type_size = sizeof(GLuint);
			break;
	}

	// bind the buffer
	AP_buffer_bind(this);

	// set the buffer data
	glBufferData(
			type,
			type_size * this->size,
			this->buffer,
			this->is_static ?
				GL_STATIC_DRAW :
				GL_DYNAMIC_DRAW);
}

void APOLLO_API AP_buffer_free_res(struct apBuffer *this) {
	free (this->buffer);
	this->size = 0u;
}

void APOLLO_API AP_buffer_copy(
		struct apBuffer *this,
		const struct apBuffer *other) {
	this->buffer = other->buffer;
	this->size = other->size;
	this->type = other->type;
	this->is_static = other->is_static;
}
