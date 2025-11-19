// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size) {
	/* TODO: Implement malloc(). */
	if (size == 0) {
		return NULL;
	}

	void *mem_block = mmap(NULL, size, PROT_READ | PROT_WRITE,
						   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (mem_block == MAP_FAILED) {
		return NULL;
	}

	mem_list_add(mem_block, size);
	return mem_block;
}

void *calloc(size_t nmemb, size_t size) {
	/* TODO: Implement calloc(). */
	if (nmemb == 0 || size == 0) {
		return NULL;
	}

	if (nmemb > ((size_t)-1) / size) {
		return NULL;
	}

	size_t total_size = nmemb * size;

	void *mem_block = malloc(total_size);

	if (mem_block != NULL) {
		memset(mem_block, 0, total_size);
	}

	return mem_block;
}

void free(void *ptr) {
	/* TODO: Implement free(). */
	if (ptr == NULL) {
		return;
	}

	struct mem_list *block_info = mem_list_find(ptr);

	if (block_info != NULL) {
		size_t block_size = block_info->len;

		mem_list_del(ptr);
		munmap(ptr, block_size);
	}
}

void *realloc(void *ptr, size_t size) {
	/* TODO: Implement realloc(). */
	if (ptr == NULL) {
		return malloc(size);
	}

	if (size == 0) {
		free(ptr);
		return NULL;
	}

	struct mem_list *old_block = mem_list_find(ptr);

	if (old_block == NULL) {
		return NULL;
	}

	size_t old_size = old_block->len;

	if (size <= old_size) {
		return ptr;
	}

	void *new_ptr = malloc(size);


	if (new_ptr == NULL) {
		return NULL;
	}

	memcpy(new_ptr, ptr, old_size);

	free(ptr);

	return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
	/* TODO: Implement reallocarray(). */
	if (nmemb == 0 || size == 0) {
		return realloc(ptr, 0);
	}

	if (nmemb > ((size_t)-1) / size) {
		return NULL;
	}

	size_t total_size = nmemb * size;
	return realloc(ptr, total_size);
}
