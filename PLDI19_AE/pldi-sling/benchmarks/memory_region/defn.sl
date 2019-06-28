data backing_file {
  int file_id;
};

data mem_reg {
  backing_file file;
  int file_offset;
  int file_size;
  int start_address;
  int size;
  mem_reg prev;
  mem_reg next;
};

pred dll(hd, p, tl, n) := hd=n & tl=p
     \/ (exists f,fo,fs,sa,s,p,x. hd->mem_reg{f,fo,fs,sa,s,p,x} * dll(x, hd, tl, n));
