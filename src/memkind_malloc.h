size_t jemk_malloc_usable_size(void *ptr);
int jemk_get_defrag_hint(void* ptr, int *bin_util, int *run_util);
int jemk_mallctl(const char *name, void *oldp, size_t *oldlenp, void *newp, size_t newlen);
void jemk_dallocx(void *ptr, int flags);

void *memkind_alloc_wrapper(size_t size);
void *memkind_calloc_wrapper(size_t number, size_t size);
void *memkind_realloc_wrapper(void *ptr, size_t size);
void memkind_free_wrapper(void *ptr);
size_t memkind_malloc_used_memory(void);
void *pmem_memcpy_wrapper(void *pmemdest, const void *src, size_t len);
void *pmem_memset_wrapper(void *pmemdest, int c, size_t len);
