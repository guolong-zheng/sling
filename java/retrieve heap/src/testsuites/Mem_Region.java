package testsuites;

public class Mem_Region {
   static MemReg memory_region_init(BackingFile file_,
                                int file_offset_,
                                int file_size_,
                                int start_address_,
                                int size_)
    {
        //pre
        MemReg mr = new MemReg();
        mr.file = file_;
        mr.file_offset = file_offset_;
        mr.file_size = file_size_;
        mr.start_address = start_address_;
        mr.size = size_;
        mr.prev = null;
        mr.next = null;
        //post
        return mr;
    }

    static MemReg memory_region_create_user_space_region()
    {
        //pre
        MemReg r  = memory_region_init(null, 0, 0, 0, 1);
        MemReg r1 = memory_region_init(null, 0, 0, 786432, 65536);
        r.next = r1;
        r1.prev = r;
        //post
        return r;
    }

   static MemReg split_memory_region(MemReg curr, int offset)
    {
        //pre
        if (offset >= curr.size) {
            //post
            return null;
        }

        MemReg old_next = curr.next;
        MemReg next = null;
        if (offset > curr.file_size) {
            next = memory_region_init(null, 0, 0, curr.start_address + offset, curr.size - offset);
        } else {
            next = memory_region_init(curr.file, 0, 0, curr.start_address + offset, curr.size - offset);
            curr.file_size = offset;
        }

        curr.size = offset;
        next.prev = curr;
        next.next = old_next;

        if(old_next != null) {
            old_next.prev = next;
        }
        curr.next = next;
        //post
        return next;
    }

    public static void main(String args[]){
        MemReg m = memory_region_create_user_space_region();
        MemReg mem = memory_region_init(null, 0, 0, 786432, 60);
        split_memory_region(mem, 10);
        split_memory_region(mem, 100);
    }
}

class BackingFile {
    int file_id;
}

class MemReg {
    BackingFile file;
    int file_offset;
    int file_size;
    int start_address;
    int size;
    MemReg prev;
    MemReg next;
}
