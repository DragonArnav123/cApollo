#pragma once

#include "core/core.h"

/*
 * @struct: apVertexArray
 * @brief: struct to respresent a vertex array
 * @desc:
 *	represents a vertex array
 *	consists of
 *		id
 *		vertex buffer (apBuffer)
 *		index buffer (apBuffer)
 *		layout (apVertexLayout)
*/
typedef struct apVertexArray apVertexArray;

enum apBufferType;
typedef struct apBuffer apBuffer;

typedef struct apVertexLayout apVertexLayout;
typedef struct apVertexLayoutElement apVertexLayoutElement;

/*
 * @func: AP_vao_create
 * @params:
 *	- vertex_buffer [void *]: pointer to buffer data for vertex buffer
 *	- vertex_buffer_size [Apu32]: size of vertex buffer data in bytes
 *	- index_buffer [void *]: pointer to buffer data for index buffer
 *	- indeex_buffer_size [Apu32]: size of index buffer data in bytes
 * @ret: apVertexArray *
 * @brief: creates a new vertex array
 * @desc:
 *	creates a new vertex array, vertex buffer and index buffer and layout using their respective create
 *	functions
*/
apVertexArray APOLLO_API *AP_vao_create(
		void *vertex_buffer,
		APu32 vertex_buffer_size, 
		void *index_buffer,
		APu32 index_buffer_size);

/*
 * @func: AP_vao_destroy
 * @params:
 *	- vao [struct apVertexArray *]: pointer to the vao object you want to destroy
 * @ret: void
 * @brief: destroys a vertex array
 * @desc:
 *	destroys the vertex array and the vertex buffer and the index buffer and frees all allocated memory
*/
void APOLLO_API AP_vao_destroy(struct apVertexArray *vao);

/*
 * @func: AP_vao_bind
 * @params:
 *	- vao [const struct apVertexArray *]: pointer to vao object you want to bind
 * @ret: void
 * @brief: binds a given vertex array object
 * @desc:
 *	binds the given vertex array object
*/
void APOLLO_API AP_vao_bind(const struct apVertexArray *vao);

/*
 * @func: AP_vao_unbind
 * @params:
 *	- void
 * @ret: void
 * @brief: unbinds the current bound vertex array object
 * @desc:
 *	unbinds the current bound vertex array object( binds 0 )
*/
void APOLLO_API AP_vao_unbind(void);

/*
 * @func: AP_vao_update
 * @params:
 *	- vao [struct apVertexAray *]: pointer to vao object you want to update
 * @ret: void
 * @brief: updates the given vertex array object
 * @desc:
 *	updates the vertex array object, updates all the values and fills and sends the vertex array attributes
 *	to the gpu using @AP_vao_layout_fill_attributes
*/
void APOLLO_API AP_vao_update(struct apVertexArray *vao);

/*
 * @func: AP_vao_get_id
 * @params:
 *	- vao [const struct apVertexArray *]: pointer to vao object of which's id you want
 * @ret: APu32
 * @brief: returns the id of the given vertex array object 
 * @desc:
 *	returns the id of the given vertex array object 
*/
APu32 APOLLO_API AP_vao_get_id(const struct apVertexArray *vao);

/*
 * @func: AP_vao_get_vertex_buffer
 * @params:
 *	- vao [const struct apVertexArray *]: pointer to vao object of which's vertex buffer you want
 * @ret: struct apBuffer *
 * @brief: returns the pointer to the vertex buffer object of the given vertex array object 
 * @desc:
 *	returns the pointer to the vertex buffer object of the given vertex array object 
*/
struct apBuffer APOLLO_API *AP_vao_get_vertex_buffer(struct apVertexArray *vao);

/*
 * @func: AP_vao_get_index_buffer
 * @params:
 *	- vao [const struct apVertexArray *]: pointer to vao object of which's index buffer you want
 * @ret: struct apBuffer *
 * @brief: returns the pointer to the index buffer object of the given vertex array object 
 * @desc:
 *	returns the pointer to the index buffer object of the given vertex array object 
*/
struct apBuffer APOLLO_API *AP_vao_get_index_buffer(struct apVertexArray *vao);

/*
 * @func: AP_vao_get_layout
 * @params:
 *	- vao [const struct apVertexArray *]: pointer to vao object of which's layout you want
 * @ret: struct apVertexlayout *
 * @brief: returns the pointer to the layout of the given vertex array object 
 * @desc:
 *	returns the pointer to the layout of the given vertex array object 
*/
struct apVertexLayout APOLLO_API *AP_vao_get_layout(struct apVertexArray *vao);

/*
 * @func: AP_vao_copy
 * @params:
 *	- dest [struct apVertexArray *]: pointer to the destination vertex array
 *	- src [const struct apVertexArray *]: pointer to the source vertex array
 * @ret: void
 * @brief: copies the vertex array
 * @desc:
 *	copies everything except id of the source buffer
 *	copies buffers using @AP_buffer_copy, copies layouts using @AP_vao_layout_copy
 *	automatically updates and fills and resends vertex attributes to gpu using @AP_vao_update
*/
void APOLLO_API *AP_vao_copy(struct apVertexArray *dest, const struct apVertexArray *src);
