# libmetrics-discovery-headers - Intel Metrics Discovery API (MDAPI) C++ header

This is a `build2` package for the
[`metrics-discovery`](https://github.com/intel/metrics-discovery) C++
library. It provides the header of the Intel Metrics Discovery Application
Programming Interface (MDAPI), a user mode library that provides access to
GPU performance data.


## Usage

To start using `libmetrics-discovery-headers` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libmetrics-discovery-headers ^1.16.197
```

Then import the library in your `buildfile`:

```
import libs = libmetrics-discovery-headers%lib{metrics-discovery-headers}
```


## Importable targets

This package provides the following importable targets:

```
lib{metrics-discovery-headers}
```

The MDAPI header, included without a subdirectory prefix, as installed by
upstream (`#include <metrics_discovery_api.h>`). The header requires C++ (it
declares the API in the `MetricsDiscovery` namespace).

This package is headers only and supports all platforms. Applications load
the MDAPI library at runtime (`libigdmd.so.1` on Linux, `igdmd64.dll` on
64-bit Windows, where it comes with the Intel graphics driver), resolve its
factory functions by name (`OpenAdapterGroup()`, etc), and use the
interfaces that these functions return. The header declares the types of
these functions (`OpenAdapterGroup_fn`, etc). On Linux the library itself is
provided by the `libmetrics-discovery` package.


## Configuration variables

This package provides no configuration variables.
