/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright © 2020–2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
 *                       Matthias Kretz <m.kretz@gsi.de>
 */

// expensive: * [1-9] * *
#include "bits/main.h"

template <class M, class M2>
  constexpr bool assign_should_work
    = std::is_same<M, M2>::value
	|| (std::is_same<typename M::abi_type,
			 std::experimental::simd_abi::fixed_size<M::size()>>::value
	      && std::is_same<typename M::abi_type, typename M2::abi_type>::value);

template <class M, class M2>
  constexpr bool assign_should_not_work = !assign_should_work<M, M2>;

template <class L, class R>
  std::enable_if_t<assign_should_work<L, R>>
  implicit_conversions_test()
  {
    L x = R(true);
    COMPARE(x, L(true));
    x = R(false);
    COMPARE(x, L(false));
    R y(false);
    y[0] = true;
    x = y;
    L ref(false);
    ref[0] = true;
    COMPARE(x, ref);
  }

template <class L, class R>
  std::enable_if_t<assign_should_not_work<L, R>>
  implicit_conversions_test()
  {
    VERIFY((is_substitution_failure<L&, R, assignment>) );
  }

template <typename V>
  void
  test()
  {
    using M = typename V::mask_type;
    using std::experimental::fixed_size_simd_mask;
    using std::experimental::native_simd_mask;
    using std::experimental::simd_mask;

    implicit_conversions_test<M, simd_mask<ldouble>>();
    implicit_conversions_test<M, simd_mask<double>>();
    implicit_conversions_test<M, simd_mask<float>>();
    implicit_conversions_test<M, simd_mask<ullong>>();
    implicit_conversions_test<M, simd_mask<llong>>();
    implicit_conversions_test<M, simd_mask<ulong>>();
    implicit_conversions_test<M, simd_mask<long>>();
    implicit_conversions_test<M, simd_mask<uint>>();
    implicit_conversions_test<M, simd_mask<int>>();
    implicit_conversions_test<M, simd_mask<ushort>>();
    implicit_conversions_test<M, simd_mask<short>>();
    implicit_conversions_test<M, simd_mask<uchar>>();
    implicit_conversions_test<M, simd_mask<schar>>();
    implicit_conversions_test<M, native_simd_mask<ldouble>>();
    implicit_conversions_test<M, native_simd_mask<double>>();
    implicit_conversions_test<M, native_simd_mask<float>>();
    implicit_conversions_test<M, native_simd_mask<ullong>>();
    implicit_conversions_test<M, native_simd_mask<llong>>();
    implicit_conversions_test<M, native_simd_mask<ulong>>();
    implicit_conversions_test<M, native_simd_mask<long>>();
    implicit_conversions_test<M, native_simd_mask<uint>>();
    implicit_conversions_test<M, native_simd_mask<int>>();
    implicit_conversions_test<M, native_simd_mask<ushort>>();
    implicit_conversions_test<M, native_simd_mask<short>>();
    implicit_conversions_test<M, native_simd_mask<uchar>>();
    implicit_conversions_test<M, native_simd_mask<schar>>();
    implicit_conversions_test<M, fixed_size_simd_mask<ldouble, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<double, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<float, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<ullong, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<llong, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<ulong, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<long, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<uint, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<int, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<ushort, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<short, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<uchar, M::size()>>();
    implicit_conversions_test<M, fixed_size_simd_mask<schar, M::size()>>();
  }
