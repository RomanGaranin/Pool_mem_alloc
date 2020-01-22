Pool memory allocator
=====================
This project is an attempt to complete a test task for employment.
# The task:
Develop platform independent pool memory allocator module.
# Requarements:
* The module should allow to allocate a fixed size memory blocks in fixed size memory pool.
* The pool allocates in static memory.
* The sizes of pool and memory blocks defines by the user before build.
* The module should be platform independent and thread safety.
* The module should be covered by tests for 2-3 cases.

# Description.
For realization I decided to use an one side linked list. (The idea was prompt me by  [mtrebi /memory-allocators](https://github.com/mtrebi/memory-allocators.git)). 
Each memory block has a pointer which point to the next memory block. The pointer of the last memory block is equal 0. For allocation the block we need some global pointer. First time this pointer should point to the first block. For allocating the block just return the pointer to the data of the block then move the global pointer to the next block. For freeing the block of memory the pointer inside this block should being pointed to the first block of memory pool that pointed by the global pointer. After that the global pointer should being pointed to the freed block. For thread safety each thread should have its own memory pool and global pointer to this pool.

# Decomposition:
After description we can imagine what functions may consist the module.
* A function for initialization the pool.
* A function for memory allocation.
* A fanction for memory free.

# TODO:
* Mutex inside pool.
