// Cilk implementation of Cholesky decomposition and its supporting BLAS routines
// Some of the routines support only a subset of the full BLAS functionality.

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cilk/cilk.h>
#include "common/blas_leaf.h"

// Cutoff for base cases of recursions.  Corresponds roughly to number of multiply-adds to compute a base case. 
#if 0
const int CUT = 1;        // Value for debugging
#else
const int CUT = 1000000;  // Value for performance.  
#endif

#include "gemm_cilk.h"
#include "trsm_cilk.h"
#include "syrk_cilk.h"
#include "potrf_cilk.h"
