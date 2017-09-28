#if HAVE_CILKPLUS

#include "cilk/cilk.h"
#include "reducer_consume.h"
#include <cassert>

// State type for unit testing.
struct state_type {
    int next;       // Index of next item to be consumed
    explicit state_type( int i ) : next(i) {}
};

// Item type for unit testing.
struct item_type {    
    int index;      // Index of item
    explicit item_type( int i ) : index(i) {}
};

// Reduction function for unit testing.
void func( state_type* s, item_type i ) {
    // Check that item is consumed in proper order. 
    assert( s->next==i.index );
    s->next+=1;
}

void test_reducer_consume() {
    const int N = 100000;
    state_type s(0);
    reducer_consume<state_type,item_type> sr(&s,func);
    // Create items in parallel and consume them
    cilk_for( int i=0; i<N; ++i ) 
        sr.consume(item_type(i));
    assert( s.next==N );
}

#endif /* HAVE_CILKPLUS */
