/// \file
// Range v3 library
//
//  Copyright Casey Carter 2018-present
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_VIEW_ENUMERATE_HPP
#define RANGES_V3_VIEW_ENUMERATE_HPP

#include <range/v3/core.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/zip.hpp>

namespace ranges
{
    /// \addtogroup group-views
    /// @{
    namespace view
    {
        /// Lazily pairs each element in a source range with
        /// its corresponding index.
        struct enumerate_fn
        {
            template<typename Rng>
            auto CPP_fun(operator())(Rng &&rng) (const
                requires ViewableRange<Rng> &&
                    Integral<detail::iter_size_t<iterator_t<Rng>>>)
            {
                return zip(
                    iota(detail::iter_size_t<iterator_t<Rng>>{}),
                    all(static_cast<Rng &&>(rng)));
            }
            // For iota_view<Integral>, we can ignore the difference type and
            // use make_unsigned_t<Integral> as the index since we don't need
            // to represent negative values.
            template<typename Int, typename S>
            auto CPP_fun(operator())(iota_view<Int, S> rng) (const
                requires Integral<Int>)
            {
                return zip(iota(meta::_t<std::make_unsigned<Int>>{}), rng);
            }
        };

        /// \relates enumerate_fn
        /// \ingroup group-views
        RANGES_INLINE_VARIABLE(view<enumerate_fn>, enumerate)
    } // namespace view
    /// @}
} // namespace ranges

#endif
