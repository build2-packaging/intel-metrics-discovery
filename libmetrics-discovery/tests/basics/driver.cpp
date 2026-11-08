#include <cstdio>

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

  // Adapter group. Opening it fails without a supported GPU, so print the
  // adapters if present and skip otherwise.
  //
  {
    IAdapterGroupLatest* g (nullptr);
    TCompletionCode r (OpenAdapterGroup (&g));

    if (r != CC_OK && r != CC_ALREADY_INITIALIZED)
    {
      std::printf ("OpenAdapterGroup: %d, skipping GPU info\n", r);
      return 0;
    }

    assert (g != nullptr);

    const TAdapterGroupParamsLatest* p (g->GetParams ());
    assert (p != nullptr);
    assert (p->Version.MajorNumber == MD_API_MAJOR_NUMBER_CURRENT);

    if (p->AdapterCount == 0)
    {
      std::printf ("OpenAdapterGroup: %d, 0 adapter(s), skipping GPU info\n",
                   r);
      assert (g->Close () == CC_OK);
      return 0;
    }

    for (uint32_t i (0); i != p->AdapterCount; ++i)
    {
      IAdapterLatest* a (g->GetAdapter (i));
      assert (a != nullptr);

      const TAdapterParamsLatest* ap (a->GetParams ());
      assert (ap != nullptr);
      assert (ap->ShortName != nullptr);

      std::printf ("%s (vendor 0x%04X device 0x%04X)\n",
                   ap->ShortName,
                   static_cast<unsigned int> (ap->VendorId),
                   static_cast<unsigned int> (ap->DeviceId));
    }

    assert (g->Close () == CC_OK);
  }
}
