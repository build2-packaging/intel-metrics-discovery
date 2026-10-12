#include <metrics_discovery_api.h>

#undef NDEBUG
#include <cassert>

using namespace MetricsDiscovery;

// The library entry points (declared in upstream's private md_exports.h),
// which applications normally resolve by name after loading the library at
// runtime.
//
extern "C"
{
  TCompletionCode
  OpenAdapterGroup (IAdapterGroupLatest**);

  TCompletionCode
  OpenMetricsDeviceFromFile (const char*, void*, IMetricsDeviceLatest**);
}

int main ()
{
  // Invalid parameters.
  //
  {
    assert (OpenAdapterGroup (nullptr) == CC_ERROR_INVALID_PARAMETER);
    assert (OpenMetricsDeviceFromFile ("driver.md", nullptr, nullptr) ==
            CC_ERROR_INVALID_PARAMETER);
  }

  // Adapter group. Opening it fails without a supported GPU, so only check
  // the group if it could be opened.
  //
  {
    IAdapterGroupLatest* g (nullptr);
    TCompletionCode r (OpenAdapterGroup (&g));

    if (r == CC_OK || r == CC_ALREADY_INITIALIZED)
    {
      assert (g != nullptr);

      const TAdapterGroupParamsLatest* p (g->GetParams ());
      assert (p != nullptr);
      assert (p->Version.MajorNumber == MD_API_MAJOR_NUMBER_CURRENT);

      assert (g->Close () == CC_OK);
    }
    else
      assert (r > CC_OK && r < CC_LAST_1_0);
  }
}
