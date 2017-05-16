#if HAVE_CILKPLUS

#include <limits>
#include <cstdlib>
#include <cstdio>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

#include "../common/kmeans.h"
#include "elementwise_reducer.h"

namespace cilk_example {

#include "kmeans_cilk.h"

} // namespace cilk_example

#endif /* HAVE_CILKPLUS */
