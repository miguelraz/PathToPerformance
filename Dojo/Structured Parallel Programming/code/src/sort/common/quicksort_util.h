// Size of parallel base case.
ptrdiff_t QUICKSORT_CUTOFF = 500;

// Choose median of three keys.
T* median_of_three(T* x, T* y, T* z) {
    return *x<*y ? *y<*z ? y : *x<*z ? z : x 
         : *z<*y ? y : *z<*x ? z : x;
}

// Choose a partition key as median of medians.
T* choose_partition_key( T* first, T* last ) {
    size_t offset = (last-first)/8;
    return median_of_three(
        median_of_three(first, first+offset, first+offset*2),
        median_of_three(first+offset*3, first+offset*4, last-(3*offset+1)), 
        median_of_three(last-(2*offset+1), last-(offset+1), last-1 )
    );
}

// Choose a partition key and partition [first...last) with it.
// Returns pointer to where the partition key is in partitioned sequence.
// Returns NULL if all keys in [first...last) are equal.
T* divide( T* first, T* last ) {
    // Move partition key to front.
    std::swap( *first, *choose_partition_key(first,last) );
    // Partition 
    T key = *first;
    T* middle = std::partition( first+1, last, [=](const T& x) {return x<key;} ) - 1;
    if( middle!=first ) {
        // Move partition key to between the partitions
        std::swap( *first, *middle );
    } else {
        // Check if all keys are equal
        if( last==std::find_if( first+1, last, [=](const T& x) {return key<x;} ) )
            return NULL;
    }
    return middle;
}
