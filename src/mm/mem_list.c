// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <sys/mman.h>

struct mem_list mem_list_head;

void mem_list_init(void) {
	struct mem_list *head = &mem_list_head;
	head->start = NULL;
	head->len = 0;
	head->next = head;
	head->prev = head;
}

static struct mem_list *mem_list_alloc(void) {
	struct mem_list *node;

	node = mmap(0, sizeof(*node),
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS,
				-1, 0);

	if (node == MAP_FAILED)
		return NULL;

	return node;
}

static int mem_list_free(struct mem_list *item) {
	if (!item)
		return -1;

	return munmap(item, sizeof(*item));
}

int mem_list_add(void *start, size_t len) {
	struct mem_list *node = mem_list_alloc();
	if (!node)
		return -1;

	node->start = start;
	node->len = len;

	struct mem_list *tail = mem_list_head.prev;
	tail->next = node;
	node->prev = tail;
	node->next = &mem_list_head;
	mem_list_head.prev = node;

	return 0;
}

struct mem_list *mem_list_find(void *start) {
	struct mem_list *cur = mem_list_head.next;

	while (cur != &mem_list_head) {
		if (cur->start == start)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

static struct mem_list *mem_list_extract(void *start) {
	struct mem_list *cur = mem_list_find(start);
	if (!cur)
		return NULL;

	struct mem_list *prev = cur->prev;
	struct mem_list *next = cur->next;

	prev->next = next;
	next->prev = prev;

	cur->next = cur;
	cur->prev = cur;

	return cur;
}

int mem_list_del(void *start) {
	struct mem_list *victim = mem_list_extract(start);
	if (!victim)
		return -1;

	return mem_list_free(victim);
}

void mem_list_cleanup(void) {
	struct mem_list *node = mem_list_head.next;

	while (node != &mem_list_head) {
		struct mem_list *to_delete = node;
		node = node->next;

		to_delete->prev->next = to_delete->next;
		to_delete->next->prev = to_delete->prev;

		mem_list_free(to_delete);
	}

	mem_list_head.next = &mem_list_head;
	mem_list_head.prev = &mem_list_head;
}

size_t mem_list_num_items(void) {
	size_t n = 0;
	for (struct mem_list *p = mem_list_head.next;
		 p != &mem_list_head;
		 p = p->next)
		n++;

	return n;
}
