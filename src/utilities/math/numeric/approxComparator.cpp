//#include <utilities/math/numeric/approxComparator.h>

#include "approxComparator.h"

namespace math {
namespace numeric {

template <> float approx_comparator<float>::pos_error_bound=1.0e-7; // -22
template <> float approx_comparator<float>::neg_error_bound=-1.0e-7; // -22
template <> float approx_comparator<float>::lg_rel_error=1.0+1.0e-6; // -15
template <> float approx_comparator<float>::sm_rel_error=1.0-1.0e-6; // -15

template <> double approx_comparator<double>::pos_error_bound=1.0e-14; // -22
template <> double approx_comparator<double>::neg_error_bound=-1.0e-14; // -22
template <> double approx_comparator<double>::lg_rel_error=1.0+1.0e-12; // -15
template <> double approx_comparator<double>::sm_rel_error=1.0-1.0e-12; // -15

template <> long double approx_comparator<long double>::pos_error_bound=1.0e-20; // -22
template <> long double approx_comparator<long double>::neg_error_bound=-1.0e-20; // -22
template <> long double approx_comparator<long double>::lg_rel_error=1.0+1.0e-17; // -15
template <> long double approx_comparator<long double>::sm_rel_error=1.0-1.0e-17; // -15

/*
template <> __float128 approx_comparator<__float128>::pos_error_bound=1.0e-23; // -22
template <> __float128 approx_comparator<__float128>::neg_error_bound=-1.0e-23; // -22
template <> __float128 approx_comparator<__float128>::lg_rel_error=1.0+1.0e-20; // -15
template <> __float128 approx_comparator<__float128>::sm_rel_error=1.0-1.0e-20; // -15
*/

}
}
