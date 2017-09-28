void cilk_stencil( int t0, int t1, int x0, int x1, int y0, int y1, int z0, int z1 ) {
    recursive_trapezoid(t0, t1,
                        ds, 0, Nx-ds, 0,
                        ds, 0, Ny-ds, 0,
                        ds, 0, Nz-ds, 0);
}