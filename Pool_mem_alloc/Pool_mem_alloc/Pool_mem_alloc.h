/*!
*	Pool memory alloocator module.
*
*	This module provide a functions for allocate and deallocate a fixed size memmory blocks in a fixed size memory pool.
*	The sizes of pool and blocks may be changed by the user before build by editing a macros POOL_BLOCK_SIZE and POOL_BLOKS_NUM.
*	If this module will use with some RTOS, for thread safety each thread should have its own pool.
*	For each pool user have to define some memory (which provides by a platform) and a global pointer to this pool.
*	Before allocating and deallocating the blocks of memory, user have to initialize new pool and pointer to this pool 
*	by calling a function Init_pool_mem_alloc().
*	
*
*	(c) Roman Garanin
*	17.01.2020
*/

#ifndef POOL_MEM_ALLOC
#define POOL_MEM_ALLOC

#ifdef __cplusplus
extern "C" {
#endif

/*!
	brief	This macro defines a block size in bytes and number of blocks in the pool.
			Should be defined by the user.
*/
#define POOL_BLOCK_SIZE 256
#define POOL_BLOKS_NUM 16
#include "stdlib.h"
#include "stdint.h"
/*!
	brief	This function initializes the memory pool. 
			A size of pool defines by pool block size, blocks number in the pool 
			and bit dept of the of the platform. 
			Pool size = (POOL_BLOCK_SIZE + (bit dept/8)) * POOL_BLOKS_NUM
	return	No.		
*/
	void Init_pool_mem_alloc(void** pool_ptr, void* mem);

/*!
	brief	This function allocates the block of memory in the pool.
	param	pool_ptr - The pointer to the pool from which the block will allocated.
	return	Pointer to the allocated memory block in the pool.
*/
	void* pool_mem_alloc(void** pool_ptr);

/*!
	brief	This function frees the block of memory inte pool.
	param	free_ptr - Pointer to block of memory to free.
	param	pool_ptr - The pointer to the pool from which the block will deallocated.
	return	No.
*/
	void pool_mem_free(void* free_ptr, void** pool_ptr);

#ifdef __cplusplus
}
#endif
#endif // !POOL_MEM_ALLOC
