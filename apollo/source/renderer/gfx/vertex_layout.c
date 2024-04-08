#include "APpch.h"
#include "renderer/gfx/vertex_layout.h"

#include "glad/glad.h"

APi32 APint_get_type_size(APi32 type) {
	switch (type) {
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);

		case GL_UNSIGNED_SHORT:
			return sizeof(GLushort);

		case GL_UNSIGNED_INT:
			return sizeof(GLuint);

		case GL_BYTE:
			return sizeof(GLbyte);

		case GL_SHORT:
			return sizeof(GLshort);

		case GL_INT:
			return sizeof(GLint);

		case GL_FLOAT:
			return sizeof(GLfloat);

		case GL_DOUBLE:
			return sizeof(GLdouble);
	}

	return 0;
}

typedef struct apVertexLayoutElement {
	APi32 type;
	bool normalize;
	APi32 count;
} apVLE;

typedef struct apVertexLayout {
	// our elements
	apVLE *elements;

	// number of elements
	APu32 elem_size;

	// stride
	APu64 stride;

	// is it the first time
	bool first_time;
} apVertexLayout;

struct apVertexLayout *APint_vao_layout_create() {
	struct apVertexLayout *vao = 
		(struct apVertexLayout *) malloc(sizeof(struct apVertexLayout));

	*vao = AP_vao_layout_create();

	return vao;
}

static void APint_vao_layout_push(
		struct apVertexLayout *this,
		const struct apVertexLayoutElement element) {
	// increase the elem size
	this->elem_size++;

	// increase the array size
	// if its the first time malloc it
	if (this->first_time) {
		this->first_time = false;
		this->elements = (apVLE *) malloc(sizeof(apVLE));
	} else {
		realloc(this->elements, this->elem_size);
	}

	this->elements[this->elem_size - 1] = element;
}

struct apVertexLayout APOLLO_API AP_vao_layout_create(void) {
	struct apVertexLayout layout = {
		.elements = NULL,
		.elem_size = 1,
		.stride = 0,
		.first_time = true
	};

	return layout;
}

void APOLLO_API AP_vao_layout_push_uchar(
		struct apVertexLayout *this,
		APi32 count) {
	apVLE e = {
		.type = GL_UNSIGNED_BYTE,
		.normalize = GL_TRUE,
		.count = count
	};

	APint_vao_layout_push(this, e);
}

void APOLLO_API AP_vao_layout_push_uint16(
		struct apVertexLayout *this, 
		APi32 count) {
	apVLE e = {
		.type = GL_UNSIGNED_SHORT,
		.normalize = GL_TRUE,
		.count = count
	};

	APint_vao_layout_push(this, e);
}

void APOLLO_API AP_vao_layout_push_uint32(
		struct apVertexLayout *this,
		APi32 count) {
	apVLE e = {
		.type = GL_UNSIGNED_INT,
		.normalize = GL_TRUE,
		.count = count
	};

	APint_vao_layout_push(this, e);
}

void APOLLO_API AP_vao_layout_push_uint64(
		struct apVertexLayout *this, 
		APi32 count) {
	assert(0);
}

void APOLLO_API AP_vao_layout_push_char(
		struct apVertexLayout *this,
		APi32 count) {
	apVLE e = {
		.type = GL_BYTE,
		.normalize = GL_TRUE,
		.count = count
	};

	APint_vao_layout_push(this, e);
}

void APOLLO_API AP_vao_layout_push_int16(
		struct apVertexLayout *this,
		APi32 count) {
	apVLE e = {
		.type = GL_SHORT,
		.normalize = GL_TRUE,
		.count = count
	};

	APint_vao_layout_push(this, e);
}

void APOLLO_API AP_vao_layout_push_int32(
		struct apVertexLayout *this, 
		APi32 count) {
	apVLE e = {
		.type = GL_INT,
		.normalize = GL_TRUE,
		.count = count
	};

	APint_vao_layout_push(this, e);

}

void APOLLO_API AP_vao_layout_push_int64(
		struct apVertexLayout *this,
		APi32 count) {
	assert(0);
}

void APOLLO_API AP_vao_layout_push_float(
		struct apVertexLayout *this,
		APi32 count) {
	apVLE e = {
		.type = GL_FLOAT,
		.normalize = GL_FALSE,
		.count = count
	};

	APint_vao_layout_push(this, e);

}

void APOLLO_API AP_vao_layout_push_double(
		struct apVertexLayout *this, 
		APi32 count) {
	apVLE e = {
		.type = GL_DOUBLE,
		.normalize = GL_FALSE,
		.count = count
	};

	APint_vao_layout_push(this, e);

}

void APOLLO_API AP_vao_layout_get_elements(
		struct apVertexLayout *this,
		struct apVertexLayoutElement **elem_array_in,
		APu32 *elem_array_size_in) {
	// set the data
	*elem_array_size_in = this->elem_size;
	*elem_array_in = this->elements;
}

APu64 APOLLO_API AP_vao_layout_get_stride(struct apVertexLayout *this) {
	return this->stride;
}

void APOLLO_API AP_vao_layout_free_res(struct apVertexLayout *layout) {
	free(layout->elements);
	layout->elem_size = 
		layout->stride = 0;
}

void APOLLO_API AP_vao_layout_copy(
		struct apVertexLayout *dest,
		const struct apVertexLayout *src) {
	// allocate new memory
	dest->elements = (apVLE *) malloc(sizeof(apVLE) * src->elem_size);

	// copy the stride and num elments
	dest->stride = src->stride;
	dest->elem_size = src->elem_size;

	// copy the buffer
	memcpy(dest->elements, src->elements, sizeof(apVLE) * src->elem_size);
}

void APOLLO_API AP_vao_layout_fill_attributes(
		const struct apVertexLayout *this) {
	// offset
	void *offset = 0;

	// iterate through the elemnts and fill the attributes
	for (size_t i = 0; i < this->elem_size; i++) {
		// get the element
		apVLE *e = &this->elements[i];

		// enable the attribute
		glEnableVertexAttribArray(i);

		// fill the attribute
		glVertexAttribPointer(
				i,
				e->count,
				e->type,
				e->normalize,
				this->stride,
				offset);

		// correct the offset
		offset += e->count * APint_get_type_size(e->type);
	}
}
