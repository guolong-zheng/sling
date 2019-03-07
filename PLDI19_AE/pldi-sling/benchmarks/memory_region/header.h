typedef struct backing_file {
  int file_id;
} BackingFile;

typedef struct mem_reg {
  BackingFile * file;
  int file_offset;
  int file_size;
  int start_address;
  int size;
  struct mem_reg * prev;
  struct mem_reg * next;
} MemReg;
