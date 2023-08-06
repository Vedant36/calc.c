#ifndef ARENA_H
#define ARENA_H

typedef struct {
	void *rbp;
	size_t pos;
	size_t size;
} arena;

arena *arena_create(size_t size);
void *arena_allocate(arena *arena, size_t size);
#define arena_set_pos(arena, position) arena->pos = position
#define arena_get_pos(arena) arena->pos
#define arena_clear(arena) arena->pos = 0
#define arena_destroy(arena) free(arena->rbp)

#endif /* ARENA_H */

#ifdef ARENA_IMPLEMENTATION
#include <stdlib.h>
#include <assert.h>

arena *arena_create(size_t size)
{
	static arena result = {0};
	result.size = size;
	result.rbp = malloc(size);
	return &result;
}

void *arena_allocate(arena *arena, size_t size)
{
	assert(arena->pos + size < arena->size);
	arena->pos += size;
	return arena->rbp + (arena->pos - size);
}


#endif /* ARENA_IMPLEMENTATION */
