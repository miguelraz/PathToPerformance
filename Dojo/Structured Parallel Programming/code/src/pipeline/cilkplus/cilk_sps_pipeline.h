// Function for third stage
extern void h_( HState*, U u );
// Mutable state for third stage
HState s;
// Reducer for third stage.
reducer_consume<HState,U> sink( &s, h_ );
 
void Stage2( T t ) { 
    U u = g(t);      // Second stage
    sink.consume(u); // Feed item to third stage
}

void cilk_sps_pipeline() {
    while( T t = f() )        // First stage is serial
        cilk_spawn Stage2(t); // Spawn second stage
    cilk_sync;
}