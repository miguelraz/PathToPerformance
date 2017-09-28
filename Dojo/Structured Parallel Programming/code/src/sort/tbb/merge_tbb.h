// merge sequences [xs,xe) and [ys,ye) to output [zs,(xe-xs)+(ye-ys)
void parallel_merge( const T* xs, const T* xe,  const T* ys, const T* ye, T* zs ) {
    const size_t MERGE_CUT_OFF = 2000;
    if( xe-xs + ye-ys <= MERGE_CUT_OFF ) {
        std::merge(xs,xe,ys,ye,zs);
    } else {
        const T *xm, *ym;
        if( xe-xs < ye-ys  ) {
            ym = ys+(ye-ys)/2;
            xm = std::upper_bound(xs,xe,*ym);
        } else {
            xm = xs+(xe-xs)/2;
            ym = std::lower_bound(ys,ye,*xm);
        }
        T* zm = zs + (xm-xs) + (ym-ys);
        tbb::parallel_invoke( [=]{parallel_merge( xs, xm, ys, ym, zs );},
                              [=]{parallel_merge( xm, xe, ym, ye, zm );} );
    }
}
