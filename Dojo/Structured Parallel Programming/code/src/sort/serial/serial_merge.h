void serial_merge( T* xs, T* xe, T* ys, T* ye, T* zs ) {
    while( xs!=xe && ys!=ye ) {
        bool which = *ys < *xs;
        *zs++ = std::move(which ? *ys++ : *xs++);
    }
    std::move( xs, xe, zs );
    std::move( ys, ye, zs );
}
