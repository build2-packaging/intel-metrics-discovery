# intel-metrics-discovery - Intel Metrics Discovery API (MDAPI) C++ library

This is a `build2` package repository for
[`metrics-discovery`](https://github.com/intel/metrics-discovery),
the Intel Metrics Discovery Application Programming Interface (MDAPI), a user
mode library that provides access to GPU performance data.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libmetrics-discovery` or `libmetrics-discovery-headers` in your `build2`-based
project, then instead see the accompanying
[`libmetrics-discovery/PACKAGE-README.md`](libmetrics-discovery/PACKAGE-README.md) or
[`libmetrics-discovery-headers/PACKAGE-README.md`](libmetrics-discovery-headers/PACKAGE-README.md)
file.

The development setup for `intel-metrics-discovery` uses the standard
`bdep`-based workflow. The library is only supported on Linux. For example:

```
git clone --recurse-submodules https://github.com/build2-packaging/intel-metrics-discovery.git
cd intel-metrics-discovery

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```
