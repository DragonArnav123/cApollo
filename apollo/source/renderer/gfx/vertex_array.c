#include "APpch.h"
#include "renderer/gfx/vertex_array.h"
#include "renderer/gfx/vertex_layout.h"
#include "renderer/gfx/buffer.h"
#include "log/log.h"

#include "glad/glad.h"

typedef struct apVertexArray {
	// id
	APu32 id;

	// vertex buffer
	struct apBuffer *vbuffer;

	// index buffer
	struct apBuffer *ibuffer;

	// layout
	struct apVertexLayout *layout;
} apVertexArray;

apVertexArray APOLLO_API *AP_vao_create(
		void *vertex_buffer,
		APu32 vertex_buffer_size, 
		void *index_buffer,
		APu32 index_buffer_size) {
	// create the vertex array
	struct apVertexArray *vao = 
		(struct apVertexArray *) malloc(sizeof(struct apVertexArray));

	// create the id
	glGenVertexArrays(1, &vao->id);

	// bind the array
	AP_vao_bind(vao);

	// create the vbo
	vao->vbuffer = 
		AP_buffer_create(
				vertex_buffer,
				vertex_buffer_size,
				AP_VERTEX_BUFFER,
				false);

	// create the ibo
	vao->ibuffer =
		AP_buffer_create(
				index_buffer,
				index_buffer_size,
				AP_INDEX_BUFFER,
				false);

	// create the layout
	vao->layout = APint_vao_layout_create();

	// unbind the vertex array
	AP_vao_unbind();

	// unbind the buffers
	AP_buffer_unbind(AP_VERTEX_BUFFER);
	AP_buffer_unbind(AP_INDEX_BUFFER);

	AP_LOG_LOG("%s %d %s", "Created vertex array object: ", vao->id, " succesfully!");
	
	return vao;
}

void APOLLO_API AP_vao_destroy(struct apVertexArray *this) {
	// destroy the buffers
	AP_buffer_destroy(this->vbuffer);
	AP_buffer_destroy(this->ibuffer);

	// destroy the layout
	AP_vao_layout_free_res(this->layout);

	AP_LOG_LOG("%s %d %s", "Destroyed vertex array object: ", this->id, " succesfully!");

	// delete the vertex array id
	glDeleteVertexArrays(1, &this->id);

	// free the allocated memory itself
	free(this);
}

void APOLLO_API AP_vao_bind(const struct apVertexArray *this) {
	glBindVertexArray(this->id);
}

void APOLLO_API AP_vao_unbind(void) {
	glBindVertexArray(0x000);
}

void APOLLO_API AP_vao_update(struct apVertexArray *this) {
	// bind the vertex array
	AP_vao_bind(this);

	AP_vao_layout_fill_attributes(this->layout);
}

APu32 APOLLO_API AP_vao_get_id(const struct apVertexArray *this) {
	return this->id;
}

struct apBuffer APOLLO_API *AP_vao_get_vertex_buffer(struct apVertexArray *this) {
	return this->vbuffer;
}

struct apBuffer APOLLO_API *AP_vao_get_index_buffer(struct apVertexArray *this) {
	return this->ibuffer;
}

struct apVertexLayout APOLLO_API *AP_vao_get_layout(struct apVertexArray *this) {
	return this->layout;
}

void APOLLO_API *AP_vao_copy(struct apVertexArray *dest, const struct apVertexArray *src) {
	// copy the vertex buffer
	AP_buffer_copy(dest->vbuffer, src->vbuffer);

	// copy the index buffer
	AP_buffer_copy(dest->ibuffer, src->ibuffer);

	// copy the layout 
	AP_vao_layout_copy(dest->layout, src->layout);

	// update the vao
	AP_vao_update(dest);
}
