const int ds = 4; // Slant of a space cut (in grid units per time step)

#define TRAPEZOID(u0,u1) \
    u0+i*w,                          /* left side */  \
    ds,                              /* left slope */ \
    i<K-1 ? u0+(i+1)*w : u1,         /* right side */ \
    -ds                              /* right slope */

#define TRIANGLE(u0,du0,u1,du1) \
    i<K ? u0+i*w : u1,              /* left side */  \
    i==0 ? du0 : -ds,               /* left slope */ \
    i<K ? u0+i*w : u1,              /* right side */ \
    i<K? ds : du1                   /* right slope */

void recursive_trapezoid(int t0, int t1, 
           int x0, int dx0, int x1, int dx1,
           int y0, int dy0, int y1, int dy1, 
           int z0, int dz0, int z1, int dz1 )
{
    int dt = t1-t0;
    if( dt>1 ) {
        int dx = x1-x0, dy = y1-y0, dz = z1-z0;
        if (dx >= dx_threshold && dx >= dy && dx >= dz && dx >= 2*ds*dt*K) {
            int w = dx / K;
            cilk_for (int i=0; i<K; ++i)
                recursive_trapezoid(t0, t1,
                    TRAPEZOID(x0,x1),
                    y0, dy0, y1, dy1,
                    z0, dz0, z1, dz1);
            cilk_for (int i=K; i>=0; --i)
                recursive_trapezoid(t0, t1, 
                    TRIANGLE(x0,dx0,x1,dx1),
                    y0, dy0, y1, dy1, 
                    z0, dz0, z1, dz1);
            return;
        } 
        if (dy >= dyz_threshold && dy >= dz && dy >= 2*ds*dt*K) {
            int w = dy / K;
            cilk_for (int i=0; i<K; ++i)
                recursive_trapezoid(t0, t1,
                    x0, dx0, x1, dx1,
                    TRAPEZOID(y0,y1),
                    z0, dz0, z1, dz1);
            cilk_for (int i=K; i>=0; --i)
                recursive_trapezoid(t0, t1,
                    x0, dx0, x1, dx1,
                    TRIANGLE(y0,dy0,y1,dy1),
                    z0, dz0, z1, dz1);
            return;
        } 
        if (dz >= dyz_threshold && dz >= 2*ds*dt*K) {
            int w = dz / K;
            cilk_for (int i=0; i<K; ++i)
                recursive_trapezoid(t0, t1,
                    x0, dx0, x1, dx1,
                    y0, dy0, y1, dy1,
                    TRAPEZOID(z0,z1));
            cilk_for (int i=K; i>=0; --i)
                recursive_trapezoid(t0, t1, 
                    x0, dx0, x1, dx1,
                    y0, dy0, y1, dy1,
                    TRIANGLE(z0,dz0,z1,dz1));
            return;
        } 
        if (dt > dt_threshold) {
            int halfdt = dt / 2;
            recursive_trapezoid(t0, t0 + halfdt,
                x0, dx0, x1, dx1,
                y0, dy0, y1, dy1, 
                z0, dz0, z1, dz1);
            recursive_trapezoid(t0 + halfdt, t1, 
                x0 + dx0*halfdt, dx0, x1 + dx1*halfdt, dx1,
                y0 + dy0*halfdt, dy0, y1 + dy1*halfdt, dy1, 
                z0 + dz0*halfdt, dz0, z1 + dz1*halfdt, dz1);
            return; 
        }
    } 
    base_trapezoid(t0, t1, 
        x0, dx0, x1, dx1,
        y0, dy0, y1, dy1,
        z0, dz0, z1, dz1);
}
