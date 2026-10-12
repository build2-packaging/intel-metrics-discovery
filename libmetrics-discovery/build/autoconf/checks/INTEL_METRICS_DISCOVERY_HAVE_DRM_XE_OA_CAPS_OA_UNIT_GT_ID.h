// INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OA_UNIT_GT_ID

#undef INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OA_UNIT_GT_ID

/* Check for the DRM_XE_OA_CAPS_OA_UNIT_GT_ID macro in the system kernel xe
 * uAPI header <drm/xe_drm.h>. The macro was added together with the gt_id
 * data member of the drm_xe_oa_unit struct and the MERT OA unit type, which
 * the xe kernel mode driver interface uses if available.
 *
 * Available on Linux since 7.0. Not available on Windows or Mac OS.
 */
#if defined(__linux__) && defined(__has_include)
#  if __has_include(<drm/xe_drm.h>)
#    include <drm/xe_drm.h>
#    ifdef DRM_XE_OA_CAPS_OA_UNIT_GT_ID
#      define INTEL_METRICS_DISCOVERY_HAVE_DRM_XE_OA_CAPS_OA_UNIT_GT_ID 1
#    endif
#  endif
#endif
