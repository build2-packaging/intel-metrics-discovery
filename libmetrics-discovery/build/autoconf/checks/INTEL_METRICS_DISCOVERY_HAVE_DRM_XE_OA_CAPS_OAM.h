// INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OAM

#undef INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OAM

/* Check for the DRM_XE_OA_CAPS_OAM macro in the system kernel xe uAPI header
 * <drm/xe_drm.h>. The macro was added together with the OAM SAG OA unit
 * type, the most recent xe observation (OA) uAPI that the xe kernel mode
 * driver interface requires (except for the OA unit GT ID and MERT OA unit
 * support, see INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OA_UNIT_GT_ID).
 *
 * Available on Linux since 6.17 (the header itself since 6.8). Not available
 * on Windows or Mac OS.
 */
#if defined(__linux__) && defined(__has_include)
#  if __has_include(<drm/xe_drm.h>)
#    include <drm/xe_drm.h>
#    ifdef DRM_XE_OA_CAPS_OAM
#      define INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OAM 1
#    endif
#  endif
#endif
