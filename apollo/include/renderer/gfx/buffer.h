#pragma once

#include "APpch.h"
#include "core/core.h"

/*
 * @enum: apBufferType 
 * @brief: enum for buffer types
 * @desc:
 *	enum for support GL buffer types
*/
enum apBufferType {
	AP_VERTEX_BUFFER			= 0x000,
	AP_INDEX_BUFFER				= 0x001
};

/*
 * @struct: apBuffer 
 * @brief: struct for buffer 
 * @desc:
 *	represents a GL buffer in apollo engine
*/
struct apBuffer;
typedef struct apBuffer apBuffer;

/*
 * @func: AP_buffer_create
 * @params:
 *	- data [void *]: pointer to buffer data
 *	- data_size [APu32]: data size in bytes
 *	- type [enum apBufferType]: type of the buffer
 *	- is_static [bool <stdboo.h>]: is the buffer static or dynamic( changing )
 * @ret: struct apBuffer *
 * @brief: creates and returns a new buffer
 * @desc:
 *	creates and returns a new GLbuffer
 *	sends buffer data to the GPU, hence unbinds any previously bound buffer and keeps this buffer bound
*/
struct apBuffer APOLLO_API *AP_buffer_create(
		void *data,
		APu32 data_size, 
		enum apBufferType type,
		bool is_static);

/*
 * @func: AP_buffer_destroy
 * @params:
 *	- buffer [struct apBuffer *]: pointer to buffer
 * @ret: void
 * @brief: destroys the buffer
 * @desc:
 *	destroys and frees all allocated memory as well as destroys the buffer in GL state
*/
void APOLLO_API AP_buffer_destroy(struct apBuffer *buffer);

/*
 * @func: AP_buffer_bind
 * @params:
 *	- buffer [const struct apBuffer *]: pointer to buffer you want to bind
 * @ret: void
 * @brief: binds the buffer
 * @desc:
 *	binds the buffer to the GLstate
*/
void APOLLO_API AP_buffer_bind(const struct apBuffer *buffer);

/*
 * @func: AP_buffer_unbind
 * @params:
 *	- type [enum apBufferType]: type of buffer you want to unbind 
 * @ret: void
 * @brief: unbinds the buffer
 * @desc:
 *	unbinds the current bound buffer of the type
*/
void APOLLO_API AP_buffer_unbind(enum apBufferType type);

/*
 * @func: AP_buffer_set_data
 * @params:
 *	- buffer [struct apBuffer *buffer]: pointer to struct you want to write data to
 *	- data [void *]: pointer to data you want to add
 *	- data_size [APu32]: size of data in bytes
 * @ret: void
 * @brief: changes buffer data
 * @desc:
 *	sets the buffer data but does not free the allocated memory,
 *	to free the allocated memory use @AP_buffer_free_res
*/
void APOLLO_API AP_buffer_set_data(struct apBuffer *buffer, void *data, APu32 data_size);

/*
 * @func: AP_buffer_free_res
 * @params:
 *	- buffer [struct apBuffer *buffer]: pointer to struct you want to write data to
 * @ret: void
 * @brief: frees the allocated memory
 * @desc:
 *	frees the allocated memory 
*/
void APOLLO_API AP_buffer_free_res(struct apBuffer *buffer);

/*
 * @func: AP_buffer_copy
 * @params:
 *	- dest_buffer [struct apBuffer *]: pointer to destination buffer
 *	- src_buffer [const struct apBuffer *]: pointer to source buffer
 * @ret: void
 * @brief: copies one buffer to another
 * @desc:
 *	copies the data and size and type of src buffer to destination buffer
 *	does not free buffer data, to free buffer data use @AP_buffer_free_res
*/
void APOLLO_API AP_buffer_copy(struct apBuffer *dest_buffer, const struct apBuffer *src_buffer);
