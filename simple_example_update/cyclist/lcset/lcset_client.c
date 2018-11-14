#include "stdlib.h"
#include <stdbool.h>
#include "lcset.h"
#include "threading.h"
#include <assert.h>
#include <limits.h>

int readNumber()
{
		int v;
		v = rand();
		return v % 8;
}

void adder_thread(struct set *set)
{
    //pre
    int x = 0;
    for (;x<get_maxelems(set);)
    {
        if (INT_MAX <= x) abort();
        {
            add(set, x);
        }
        x++;
    }
	//post
}

void remover_thread(struct set *set)
{
    //pre
        int x = rand() % get_maxelems(set);
		bool success = false;
        for (;!success;)
        {
            {
                success = _remove(set, x);
            }
            if (success) {
                bool success2;
                {
                    success2 = contains(set, x);
                }
                assert(!success2);
            }
        }
    //post
}

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    unsigned int seed  = atoi(argv[2]);
    srand(seed);
    struct set *set = create_set(n);
    thread_start(adder_thread, set);
    remover_thread(set);

    dispose_set(set);
}
