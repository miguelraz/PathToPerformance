#define NOMINMAX // Required on Windows to make std::max work

int Nx = 250;
int Ny = 250;
int Nz = 250;
int T = 50;
static const int K = 2;                 // Number of pieces
static const int dt_threshold = 4;
static const int dx_threshold = 512;
static const int dyz_threshold = 4;

float* A[2];                            // Pointers to wavefield arrays.  There are two so they can be flipflopped.
float* Vsquared;                        // Field of velocity squared
extern float C[];

#include "../serial/serial_stencil.h"

#if HAVE_CILKPLUS
#include <cilk/cilk.h>
#include "../cilkplus/base_trapezoid.h"
#include "../cilkplus/recursive_trapezoid.h"
#include "../cilkplus/cilk_stencil.h"
#else 
const int ds = 4;
#endif /* HAVE_CILKPLUS */

float C[ds+1] = {
    -1435.f / 504 * 3,
    1.6f,
    -0.2f,
    8.f / 315,
    -1.f / 560
};

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "tbb/tick_count.h"

// Stencil coefficients
int TimeSteps = 50;

float* YProbe[2];

static void AllocateArrays() {
    size_t Nxyz = Nx*Ny*Nz;
    A[0] = new float[Nxyz];
    A[1] = new float[Nxyz];
    Vsquared = new float[Nxyz];
    YProbe[0] = new float[Ny];
    YProbe[1] = new float[Ny];
}

static void InitializeArrays() {
    for( int z = 0; z < Nz; ++z )
        for( int y = 0; y < Ny; ++y )
            for( int x = 0; x < Nx; ++x ) {
                size_t i = ((z*Ny)+y)*Nx+x;
                float r = std::fabs((float)(x - Nx/2 + y - Ny/2 + z - Nz/2) / 30);
                r = std::max(1-r, 0.0f) + 1;
                A[1][i] = A[0][i] = r;
                Vsquared[i] = 0.001f;
            }
}

typedef void (*StencilRoutine)( int/*t0*/, int/*t1*/, 
                                int/*x0*/, int/*x1*/, 
                                int/*y0*/, int/*y1*/, 
                                int/*z0*/, int/*z1*/ );

static void TimeOneRoutine( StencilRoutine r, const char* what, float* yprobe ) {
    InitializeArrays();
    tbb::tick_count t0 = tbb::tick_count::now();
    (*r)(0, TimeSteps, ds, Nx-ds, ds, Ny-ds, ds, Nz-ds);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::printf("%10s %g\n", what, (t1-t0).seconds());
    // Record values along line along centers of x-z planes
    for( int y=0; y<Ny; ++y )
        yprobe[y] = A[0][((Nz/2*Ny)+y)*Nx+Nx/2];
}

static void Check( float* expected, float* actual, int n ) {
    for( int y=0; y<Ny; ++y ) {
        // The parallelization does *not* rearrange floating-point, so theoretically the results should be identical.
        // However, some compilers rearrange floating-point differently depending on context, so allow some divergence.
        float tol = 2E-5;
        float d = actual[y]-expected[y];
        if( fabs(d)>tol ) 
            std::printf("Error: point (%d,%d,%d) is %g for serial run, but %g for parallel run, difference=%g\n",
                        Nx/2, y, Nz/2, expected[y], actual[y], actual[y]-expected[y] );
    }
}

int main( int argc, char* argv[] ) {
    if( argc>1 ) Nx = std::strtol(argv[1],0,0);
    if( argc>2 ) Ny = std::strtol(argv[2],0,0);
    if( argc>3 ) Nz = std::strtol(argv[3],0,0);
    if( argc>4 ) TimeSteps = std::strtol(argv[4],0,0);
    AllocateArrays();
    std::printf("%10s %s\n", "Version", "Seconds" );
    TimeOneRoutine( serial_stencil, "serial", YProbe[0] );
#if HAVE_CILKPLUS
    TimeOneRoutine( cilk_stencil, "Cilk Plus", YProbe[1] );
    Check( YProbe[0], YProbe[1], Ny );
#endif /* HAVE_CILKPLUS */
    return 0;
}
