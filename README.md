# vir::stdx::simd

This project aims to provide a simple fallback for users of 
std::experimental::simd (Parallelism TS 2). Not every user can rely on GCC 11+ 
and its standard library to be present on all target systems. Therefore, the 
header `vir/simd.h` provides a fallback implementation of the TS specification 
that only implements the `scalar` and `fixed_size<N>` ABI tags. Thus, your code 
can still compile and run correctly, even if it is missing the performance 
gains a proper implementation provides.

## Usage

```c++
#include <vir/simd.h>

namespace stdx = vir::stdx;

using floatv = stdx::native_simd<float>;
// ...
```

The `vir/simd.h` header will include `<experimental/simd>` if it is available, 
so you don't have to add any buildsystem support. It should just work.

## Options

* `VIR_SIMD_TS_DROPIN`: Define the macro `VIR_SIMD_TS_DROPIN` before including 
`<vir/simd.h>` to define everything in the namespace specified in the 
Parallelism TS 2 (namely `std::experimental::parallelism_v2`).

* `VIR_DISABLE_STDX_SIMD`: Do not include `<experimental/simd>` even if it is 
available. This allows compiling your code with the `<vir/simd.h>` 
implementation unconditionally. This is useful for testing.

## Debugging

Compile with `-D _GLIBCXX_DEBUG_UB` to get runtime checks for undefined 
behavior in the `simd` implementation(s). Otherwise, `-fsanitize=undefined` 
without the macro definition will also find the problems, but without 
additional error message.
