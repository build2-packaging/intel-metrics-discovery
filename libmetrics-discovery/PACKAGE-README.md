# libmetrics-discovery - Intel Metrics Discovery API (MDAPI) C++ library

This is a `build2` package for the
[`metrics-discovery`](https://github.com/intel/metrics-discovery) C++
library. It provides the Intel Metrics Discovery Application Programming
Interface (MDAPI) library, a user mode library that provides access to GPU
performance data.


## Usage

To start using `libmetrics-discovery` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libmetrics-discovery ^1.16.197
```

Then import the library in your `buildfile`:

```
import libs = libmetrics-discovery%lib{igdmd}
```


## Importable targets

This package provides the following importable targets:

```
lib{igdmd}
```

The MDAPI library. Its interface is the `metrics_discovery_api.h` header
(`#include <metrics_discovery_api.h>`) of the `libmetrics-discovery-headers`
package, an interface dependency of this library. The library exports the
factory functions (`OpenAdapterGroup()`, `OpenMetricsDevice()`,
`CloseMetricsDevice()`, and `OpenMetricsDeviceFromFile()`), which the header
only declares as function pointer types (`OpenAdapterGroup_fn`, etc), since
applications normally resolve them by name after loading the library at
runtime. As in upstream, the shared library of a release is named
`libigdmd.so.<version>` with the `libigdmd.so.<major>` SONAME
(`libigdmd.so.1`).

Only Linux is supported, as in upstream. The library requires the system
`libdrm` library. The DRM uAPI headers that upstream bundles come from the
`libdrm-uapi-helper` package, except for the xe kernel mode driver uAPI header,
for which the library uses the system kernel uAPI header (`<drm/xe_drm.h>`).
As a result, the support for the xe kernel mode driver depends on the
version of the system kernel uAPI headers that the library is built with:

* Linux 7.0 or later: complete support.

* Linux 6.17 to 6.19: no OA unit GT IDs (the library derives the GT IDs
  itself, as it does with kernels that do not report them) and no MERT OA
  units.

* Older than Linux 6.17 (including no `<drm/xe_drm.h>`, which is older than
  Linux 6.8): no xe support, the library only supports the i915 kernel mode
  driver and reports xe devices as unsupported.


## Configuration variables

This package provides no configuration variables.
