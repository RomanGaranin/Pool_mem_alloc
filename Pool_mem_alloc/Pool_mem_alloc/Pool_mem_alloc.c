/*
*	Pool memory alloocator module.
*	(c) Roman Garanin
*	17.01.2020
*/

#include "Pool_mem_alloc.h"
// Pool memory block structure.
struct block
{
	struct block* next; //Pointer to the next block.
	uint8_t block_data[POOL_BLOCK_SIZE]; //Block of data.
};


void Init_pool_mem_alloc(void** pool_ptr, void* mem)
{
	//Initialize the pool pointer.
	*pool_ptr = mem;
	//Initialize a local pointer to pointer to the pool.
	struct block** pool = (struct block**)pool_ptr;
	//Connect data blocks to each other.
	for (size_t i = 0; i < POOL_BLOKS_NUM-1; i++)
	{
		(*pool)->next = (*pool)+1;
		(*pool)++;
	}
	//Terminate the last block of the pool.
	(*pool)->next = 0;
	//Initialize the pool pointer again.
	*pool_ptr = mem;
}

void* pool_mem_alloc(void** pool_ptr)
{
	//Initialize a local pointer to pointer to the pool.
	struct block** pool = (struct block**)pool_ptr;
	struct block* alloc_block_ptr;

	if (*pool != 0)
	{	//Get first free block for allocating from the pool;
		alloc_block_ptr = *pool;
		//Move the pool pointer to next free block
		*pool = (*pool)->next;
		//Terminate the allocating block.
		alloc_block_ptr->next = 0;
		//return(allocate) data from the block.
		return (void*)alloc_block_ptr->block_data;
	}
	else
	{	//No free memory in the pool.
		return NULL;
	}
}

void pool_mem_free(void* free_ptr, void** pool_ptr)
{
	if (!free_ptr)
	{
		return;
	}
	//Initialize a local pointer to pointer to the pool.
	struct block** pool = (struct block**)pool_ptr;
	struct block* free_block_ptr;
	//Define a pointer to one byte.
	uint8_t*  p= (uint8_t*)free_ptr;
	//Calculate a pointer to the freeing block.
	p -= sizeof(void*);
	free_block_ptr = (struct block*)p;

	if (!*pool)
	{	//This case if the pool was full.
		*pool = free_block_ptr;
		return;
	}
	else
	{	//This case if the pool was not full.
		free_block_ptr->next = *pool;
		*pool = free_block_ptr;
		return;
	}
}
