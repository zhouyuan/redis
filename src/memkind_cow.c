#include "server.h"
#include <memkind.h>

void* dupPMAddr(unsigned char* ptr) {
      if(server.rdb_child_pid != -1 && zmalloc_get_location(ptr) == PMEM_LOCATION){
	  size_t len = memkind_malloc_usable_size(NULL, ptr);
	  void* copy = zmalloc_pmem(len);
	  if (copy != NULL) {
	    memcpy(copy, ptr, len);
	    serverAssert(memcmp(copy, ptr, len) == 0);
            //freeContentAsync(ptr);
            return copy;
          } else {
            serverAssert(0);
          }
    }
    return ptr;
}

void memkind_free_wrapper(void* ptr) {
    if (server.rdb_child_pid != -1 && PMEM_LOCATION == zmalloc_get_location(ptr)) {
        // delay free
    } else {
        memkind_free(NULL, ptr);
    }
}
void* memkind_alloc_wrapper(size_t size) {

}

void* memkind_realloc_wrapper(void* ptr, size_t size){
    if (server.rdb_child_pid != -1 && PMEM_LOCATION == zmalloc_get_location(ptr)) {
        // delay free
	  void* newptr = dupPMAddr(ptr);
	  return memkind_realloc(NULL, newptr, size);
      } else {
	  return memkind_realloc(NULL, ptr, size);
      }
  }


