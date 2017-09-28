void tbb_sps_pipeline( size_t ntoken ) {
    tbb::parallel_pipeline ( 
        ntoken,
        tbb::make_filter<void,T>( 
            tbb::filter::serial_in_order,
            [&]( tbb::flow_control& fc ) -> T{
                T item = f();
                if( !item ) fc.stop();
                return item;
            }
        ) &
        tbb::make_filter<T,U>( 
            tbb::filter::parallel,
            g
        ) &
        tbb::make_filter<U,void>( 
            tbb::filter::serial_in_order, 
            h
        )
    );
}
