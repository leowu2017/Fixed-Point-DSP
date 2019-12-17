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
     * \param to target fixed-point number
     * \param from source fixed-point number
     */
	template<unsigned nBitTo, unsigned nSgnTo, unsigned nIntTo, unsigned nFracTo, unsigned nZeroTo, int nBaseTo, unsigned nBitFrom, unsigned nSgnFrom, unsigned nIntFrom, unsigned nFracFrom, unsigned nZeroFrom, int nBaseFrom>
	void convert(sfp<nBitTo, nSgnTo, nIntTo, nFracTo, nZeroTo, nBaseTo>& to, sfp<nBitFrom, nSgnFrom, nIntFrom, nFracFrom, nZeroFrom, nBaseFrom> from) {
        // check DoF to match base
        constexpr int base_diff = static_cast<int>(nBaseTo) - static_cast<int>(nBaseFrom);
        constexpr int nIntT = nIntFrom - base_diff; // target int bit num
        constexpr int nFracT = nFracFrom + base_diff; // target frac bit num
        if constexpr ((nIntT < 0) || (nFracT < 0)) {
            throw conversion::insufficient_dof_exception();
        }
        if constexpr ((nIntT != nIntTo) || (nFracT != nFracTo)){
            throw conversion::dof_mismatch_exception();
        }
        
        // decimal point shift
        constexpr int zero_diff = static_cast<int>(nZeroTo) - static_cast<int>(nZeroFrom);
        if constexpr (zero_diff >= 0) {
            to.set_raw_value(from.raw_value() << zero_diff);
        } else {
            to.set_raw_value(from.raw_value() >> -zero_diff);
        }
	}
    
} // namespace imfp

#endif // IMFP_CONVERSION_HPP
