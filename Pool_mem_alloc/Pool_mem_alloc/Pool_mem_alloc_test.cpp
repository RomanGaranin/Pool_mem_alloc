/*
*	Test for Pool memory alloocator module
*	(c) Roman Garanin
*	17.01.2020
*/

#define _CRT_SECURE_NO_WARNINGS
#include "Pool_mem_alloc.h"
#include "stdio.h"

static uint8_t some_memory1[8000];
static uint8_t some_memory2[8000];

static void* pool_1;
static void* pool_2;

void test_pool_mem_alloc();
void test_pool_mem_not_alloc();

void test_free_pool_mem();
void test_no_free_pool_mem();

int main()
{
    Init_pool_mem_alloc(&pool_1, (void*)some_memory1);
	test_pool_mem_alloc();
	test_pool_mem_not_alloc();

	Init_pool_mem_alloc(&pool_2, (void*)some_memory2);

	test_free_pool_mem();
}

void test_pool_mem_alloc()
{
	uint8_t* p;
	uint8_t counter = 0;
	printf("Test pool memory allocate start...\r\n");
	for (uint16_t i = 0; i < POOL_BLOKS_NUM; i++)
	{
		p = (uint8_t*)pool_mem_alloc(&pool_1);
		if (!p)
		{
			printf("No available memory!\r\n");
			printf("Test Failed!\r\n");
			return;
		}
		counter++;
		sprintf((char*)p, "%d The block is allocated on address ==%p== \r\n", counter, p);
		printf((char*)p);

	}
	printf("Test Ok!\r\n");
}

void test_pool_mem_not_alloc()
{
	uint8_t* p;
	uint8_t counter = 0;
	printf("Test pool memory no allocate start...\r\n");
	for (uint16_t i = 0; i < POOL_BLOKS_NUM; i++)
	{
		p = (uint8_t*)pool_mem_alloc(&pool_1);
		if (!p)
		{
			printf("No available memory!\r\n");
			printf("Test Ok!\r\n");
			return;
		}
		counter++;
		sprintf((char*)p, "%d The block is allocated on address ==%p== \r\n", counter, p);
		printf((char*)p);
		printf("Test Fail!\r\n");
		return;
	}
}

void test_free_pool_mem()
{
	printf("Test pool memory free start...\r\n");
	uint8_t* p = (uint8_t*)pool_mem_alloc(&pool_2);
	sprintf((char*)p, "The block is allocated on address ==%p== \r\n", p);
	printf((char*)p);
	pool_mem_free(p, &pool_2);
	uint8_t* pp = (uint8_t*)pool_mem_alloc(&pool_2);

	if (p == pp)
	{
		sprintf((char*)pp, "The block alloc on   same address ==%p== \r\n", p);
		printf((char*)pp);
		printf("Test ok!");
	}
	else
	{
		printf("Test Fail!\r\n");
	}

}

void test_no_free_pool_mem()
{
	//Have not any idea how to test it yet!
	printf("Test no free pool memory start...\r\n");
	printf("Have not any idea how to test it yet!\r\n");
}
