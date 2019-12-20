/** \file conversion.hpp
    \brief Fixed-point format conversion.
*/

#ifndef IMFP_CONVERSION_HPP
#define IMFP_CONVERSION_HPP

#include <imfixedpoint/number.hpp>
#include <imfixedpoint/imfp_exception.hpp>

namespace imfp
{
    /// Invariant conversion.
    /**
     * Convert a fixed-point number between different representations without changing the degree of freedom.\n
     * S.I.F.Z<B> <=> S.(I+k).(F-k).Z<B-k>\n
     * S.I.F.Z<B> <=> (S-k).I.F.(Z+k)<B>
     * \param from source fixed-point number
     * \return target fixed-point number
     */
	template<unsigned nBitTo, unsigned nSgnTo = 1, unsigned nIntTo = 0, unsigned nFracTo = (nBitTo - nSgnTo - nIntTo), unsigned nZeroTo = (nBitTo - nSgnTo - nIntTo - nFracTo), int nBaseTo = 0, unsigned nBitFrom, unsigned nSgnFrom, unsigned nIntFrom, unsigned nFracFrom, unsigned nZeroFrom, int nBaseFrom>
	sfp<nBitTo, nSgnTo, nIntTo, nFracTo, nZeroTo, nBaseTo> convert(const sfp<nBitFrom, nSgnFrom, nIntFrom, nFracFrom, nZeroFrom, nBaseFrom> from) {
        // check DoF to match base
        static constexpr int base_diff = static_cast<int>(nBaseTo) - static_cast<int>(nBaseFrom);
        static constexpr int nIntT = nIntFrom - base_diff; // target int bit num
        static constexpr int nFracT = nFracFrom + base_diff; // target frac bit num
        if constexpr ((nIntT < 0) || (nFracT < 0)) {
            throw conversion::insufficient_dof_exception();
        }
        if constexpr ((nIntT != nIntTo) || (nFracT != nFracTo)){
            throw conversion::dof_mismatch_exception();
        }
        
        // decimal point shift
        static constexpr int zero_diff = static_cast<int>(nZeroTo) - static_cast<int>(nZeroFrom);
        if constexpr (zero_diff > 0) {
            return sfp<nBitTo, nSgnTo, nIntTo, nFracTo, nZeroTo, nBaseTo>{with_raw_value(from.raw_value() << zero_diff)};
        } else if constexpr (zero_diff < 0) {
            return sfp<nBitTo, nSgnTo, nIntTo, nFracTo, nZeroTo, nBaseTo>{with_raw_value(from.raw_value() >> -zero_diff)};
        } else {
            return sfp<nBitTo, nSgnTo, nIntTo, nFracTo, nZeroTo, nBaseTo>{with_raw_value(from.raw_value())};
        }
	}
    
} // namespace imfp

#endif // IMFP_CONVERSION_HPP
