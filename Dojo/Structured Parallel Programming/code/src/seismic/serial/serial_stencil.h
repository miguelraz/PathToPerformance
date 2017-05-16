// Time-domain simulation of wavefield for $t \in [t0,t1)$ over volume $[x0,x1) \times [y0,y1) \times [z0,z1)$
void serial_stencil( int t0, int t1,
    int x0, int x1,
    int y0, int y1,
    int z0, int z1)
{
    // Compute array strides for y and z directions
    int sy = Nx;
    int sz = Nx*Ny;
    // March through time interval $[t0,t1)$
    for( int t=t0; t<t1; ++t) {
        // Apply stencil over $[x0,x0) \times [y0,y1) \times [z0,z1)$
        for (int z=z0; z<z1; ++z)
            for (int y=y0; y<y1; ++y)
                for (int x=x0; x<x1; ++x) {
                    int s = z * sz + y * sy + x;
                    // @{\tt a}@ points to $2A_{t}(x,y,z)$ 
                    float *a = &A[t&1][s];
                    // @{\tt a\_flip}@ points to $A_{t-1}(x,y,z)$
                    float *a_flip = &A[(t+1)&1][s];
                    // Estimate $\nabla^2 A_t(x,y,z)$
                    float laplacian = C[0] * a[0]
                        + C[1] * ((a[1] + a[-1]) +
                                  (a[sy] + a[-sy]) +
                                  (a[sz] + a[-sz]))
                        + C[2] * ((a[2] + a[-2]) +
                                  (a[2*sy] + a[-2*sy]) +
                                  (a[2*sz] + a[-2*sz]))
                        + C[3] * ((a[3] + a[-3]) +
                                  (a[3*sy] + a[-3*sy]) +
                                  (a[3*sz] + a[-3*sz]))
                        + C[4] * ((a[4] + a[-4]) +
                                  (a[4*sy] + a[-4*sy]) +
                                  (a[4*sz] + a[-4*sz]));
                   // Compute $A_{t+1}(x,y,z)$  
                   a_flip[0] = 2*a[0] - a_flip[0]
                        + Vsquared[s] * laplacian;
                }
    }
}
