struct heap_block_t {
  uint32_t size;
  int free;
  heap_block* next;
};

constexpr uint32_t HEAP_SIZE = 4096;
constexpr auto BLOCK_SIZE = sizeof(heap_block_t);

struct heap_info_t {
  uint32_t size;
  heap_block* head;
};

heap_info_t heap_info;

void init_heap() {

}

void *malloc(uint32_t size) {

}

void free(void *ptr) {

}

int main(int argc, const char** argv) {
  return 0;
}
