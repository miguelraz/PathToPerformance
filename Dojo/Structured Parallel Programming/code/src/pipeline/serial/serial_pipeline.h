void serial_pipeline() {
    while( T t = f() ) {
        U u = g(t);
        h(u);
    }
}
