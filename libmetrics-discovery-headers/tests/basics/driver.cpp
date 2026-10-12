#include <cstdint>
#include <type_traits>

#include <metrics_discovery_api.h>

#undef NDEBUG
#include <cassert>

using namespace MetricsDiscovery;

// Stand-in for the OpenAdapterGroup() function that applications resolve by
// name after loading the library at runtime.
//
static TCompletionCode MD_STDCALL
open_adapter_group (IAdapterGroupLatest** g)
{
  if (g == nullptr)
    return CC_ERROR_INVALID_PARAMETER;

  *g = nullptr;
  return CC_ERROR_NOT_SUPPORTED;
}

int main ()
{
  using namespace std;

  // API version.
  //
  {
    TApiVersionLatest v {MD_API_MAJOR_NUMBER_CURRENT,
                         MD_API_MINOR_NUMBER_CURRENT,
                         MD_API_BUILD_NUMBER_CURRENT};

    TApiVersionLatest o {MD_API_MAJOR_NUMBER_1, MD_API_MINOR_NUMBER_13, 0};

    assert (v.MajorNumber == 1);
    assert (MD_API_VERSION_COMBINE_MAJOR_MINOR (v) >
            MD_API_VERSION_COMBINE_MAJOR_MINOR (o));
    assert (MD_API_VERSION_COMBINE_MAJOR_MINOR (o) ==
            (uint64_t (1) << 32 | 13));
  }

  // Completion codes.
  //
  {
    assert (CC_OK == 0);
    assert (CC_ERROR_INVALID_PARAMETER > CC_OK &&
            CC_ERROR_INVALID_PARAMETER < CC_LAST_1_0);
  }

  // Factory function types.
  //
  {
    static_assert (
      is_same<OpenAdapterGroup_fn,
              TCompletionCode (MD_STDCALL*) (IAdapterGroupLatest**)>::value,
      "unexpected OpenAdapterGroup_fn type");

    OpenAdapterGroup_fn f (&open_adapter_group);

    IAdapterGroupLatest* g (reinterpret_cast<IAdapterGroupLatest*> (&f));
    assert (f (&g) == CC_ERROR_NOT_SUPPORTED && g == nullptr);
    assert (f (nullptr) == CC_ERROR_INVALID_PARAMETER);
  }
}
