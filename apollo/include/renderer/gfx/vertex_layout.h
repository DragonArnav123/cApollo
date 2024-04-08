#pragma once

#include "core/core.h"

/*
 * @struct: apVertexLayout
 * @brief: depicts Gl vertex layout
 * @desc:
 *	struct for handling an opengl vertex layout
*/
struct apVertexLayout;
typedef struct apVertexLayout apVertexLayout;
struct apVertexLayoutElement;
typedef struct apVertexLayoutElement apVertexLayoutElement;

/*
 * @func: AP_vao_layout_create
 * @params:
 *	- void
 * @ret: apVertexLayout 
 * @brief: creates an new layout
 * @desc:
 *	creates a new layout and  initializes stride to 0
*/
struct apVertexLayout APOLLO_API AP_vao_layout_create(void);

/*
 * @func: AP_vao_layout_push_uchar
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_uchar(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_uint16
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_uint16(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_uint32
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_uint32(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_uint64
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_uint64(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_char
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_char(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_int16
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_int16(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_int32
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_int32(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_int64
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_int64(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_float
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_float(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_push_double
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 *	- count [APi32]: number of elements of type you want to push
 * @ret: void
 * @brief: pushes to layout
 * @desc:
 *	pushed number of that type to the layout
*/
void APOLLO_API AP_vao_layout_push_double(struct apVertexLayout *layout, APi32 count);

/*
 * @func: AP_vao_layout_get_elements
 * @params:
 *	- layout [struct apVertexLayout *]: pointer to vertex layout object
 *	- buffer [struct apVertexLayoutElement **]: (in) a pointer which will be set to the vertex element pointer
 *	- size [APu32 *]: (in) a pointer which will be set to array size
 * @ret: void
 * @brief: provides access to elements of the layout and their quantity
 * @desc:
 *	sets the two input parameters for the concerned values
*/
void APOLLO_API AP_vao_layout_get_elements(
		struct apVertexLayout *layout,
		struct apVertexLayoutElement **elem_array_in,
		APu32 *elem_array_size_in);

/*
 * @func: AP_vao_layout_get_stride
 * @params:
 *	- layout [struct apVertexLayout *layout]: pointer to concerned layout
 * @ret: APu64
 * @brief: returns stride
 * @desc:
 *	returns the stride of layout
*/
APu64 APOLLO_API AP_vao_layout_get_stride(struct apVertexLayout *layout);

/*
 * @func: AP_vao_layout_free_res
 * @params:
 *	- layout [struct apVertexLayout *]: pointer to vertex layout object
 * @ret: void
 * @brief: frees the associated resource
 * @desc:
 *	frees the associated memory allocated
*/
void APOLLO_API AP_vao_layout_free_res(struct apVertexLayout *layout);

/*
 * @func: AP_vao_layout_copy
 * @params:
 *	- dest [struct apVertexLayout *]: pointer to vertex layout object to where you want to copy
 *	- src [const struct apVertexLayout *]: pointer to vertex layout object from where you want to copy
 * @ret: void
 * @brief: copies one layout to other
 * @desc:
 *	allocates new memory in dest and copies data from src
 *	does not free originally allocated memory in dest
 *	use @AP_vao_layout_free_res to free allocated memory
*/
void APOLLO_API AP_vao_layout_copy(struct apVertexLayout *dest, const struct apVertexLayout *src);

/*
 * @func: AP_vao_layout_copy
 * @params:
 *	- layout [const struct apVertexLayout *]: pointer to vertex layout object of which's attributes you want to send
 * @ret: void
 * @brief: fills the attributes
 * @desc:
 *	sends the vertex attributes to the gpu
*/
void APOLLO_API AP_vao_layout_fill_attributes(const struct apVertexLayout *layout);

// internal functions
APi32 APint_get_type_size(APi32 type);

struct apVertexLayout *APint_vao_layout_create();
