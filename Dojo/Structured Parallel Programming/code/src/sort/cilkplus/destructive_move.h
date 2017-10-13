// Combines Array Notation, lambda expression, and in-place destruction.
template<typename T>
T* destructive_move( T* first, T* last, T* output ) {
    size_t n = last-first;
    []( T& in, T& out ){
        out = std::move(in);
        in.~T();
    }( first[0:n], output[0:n] );
    return output+n; 
}