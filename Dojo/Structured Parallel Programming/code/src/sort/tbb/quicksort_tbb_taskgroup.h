void parallel_quicksort( T* first, T* last ) {
    tbb::task_group g;
    while( last-first>QUICKSORT_CUTOFF ) {
        // Divide
        T* middle = divide(first,last);
        if( !middle ) {
            g.wait();
            return;
        }

        // Now have two subproblems: [first..middle) and [middle+1..last)
        if( middle-first < last-(middle+1) )  {
            // Left problem (first..middle) is smaller, so spawn it.
            g.run([=]{parallel_quicksort( first, middle );});
            // Solve right subproblem in next iteration.
            first = middle+1;
        } else {
            // Right problem (middle..last) is smaller, so spawn it.
            g.run([=]{parallel_quicksort( middle+1, last );});
            // Solve left subproblem in next iteration.
            last = middle;
        }
    }
    // Base case
    std::sort(first,last);
    g.wait();
 }