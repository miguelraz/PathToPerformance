class quicksort_task: public tbb::task {
    /*override*/tbb::task* execute();
    T *first, *last;
    bool has_local_join;
    void prepare_self_as_stealable_continuation();
public:
    quicksort_task( T* first_, T* last_ ) : first(first_), last(last_), has_local_join(false) {}
};

void quicksort_task::prepare_self_as_stealable_continuation() {
    if( !has_local_join ) {
        task* local_join  = new( allocate_continuation() ) tbb::empty_task();
        local_join->set_ref_count(1);
        set_parent(local_join);
        has_local_join = true;
    }
    recycle_to_reexecute();
}

tbb::task* quicksort_task::execute() {
    if( last-first<=QUICKSORT_CUTOFF ) {
        std::sort(first,last);
        // Return NULL continuation
        return NULL;
    } else {
        // Divide
        T* middle = divide(first,last);
        if( !middle ) return NULL; 

        // Now have two subproblems: [first..middle) and [middle+1..last)

        // Set up current task object as continuation of itself.
        prepare_self_as_stealable_continuation();

        // Now recurse on smaller subproblem.
        tbb::task* smaller;
        if( middle-first < last-(middle+1) )  {
            // Left problem (first..middle) is smaller.
            smaller = new( allocate_additional_child_of(*parent()) ) quicksort_task( first, middle );
            // Continuation will do larger subproblem
            first = middle+1;
        } else {
            // Right problem (middle..last) is smaller.
            smaller = new( allocate_additional_child_of(*parent()) ) quicksort_task( middle+1, last );
            // Continuation will do larger subproblem
            last = middle;
        }
        // Dive into smaller subproblem
        return smaller;
    }
}

void parallel_quicksort( T* first, T* last ) {
    // Create root task
    tbb::task& t = *new( tbb::task::allocate_root() ) quicksort_task( first, last );
    // Run it
    tbb::task::spawn_root_and_wait(t);
}