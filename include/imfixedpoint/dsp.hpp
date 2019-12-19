/** \file dsp.hpp
    \brief DSP functions.
*/

#ifndef IMFP_DSP_HPP
#define IMFP_DSP_HPP

#include <type_traits>
#include <imfixedpoint/number.hpp>
#include <imfixedpoint/conversion.hpp>

namespace imfp
{
    namespace {
        template<unsigned nBit, unsigned nSgn, unsigned nInt, unsigned nFrac, unsigned nZero, int nBase>
        int64_t saturate(int64_t n) {
            using type = sfp<nBit, nSgn, nInt, nFrac, nZero, nBase>;
            const int64_t max = (type::max).raw_value();
            const int64_t min = (type::min).raw_value();
            return n > max ? max : (n < min ? min : n);
        }
    }

    template<unsigned nBitT, unsigned nSgnT = 1, unsigned nIntT = 0, unsigned nFracT = (nBitT - nSgnT - nIntT), unsigned nZeroT = (nBitT - nSgnT - nIntT - nFracT), int nBaseT = 0, unsigned nBitS1, unsigned nSgnS1, unsigned nIntS1, unsigned nFracS1, unsigned nZeroS1, int nBaseS1, unsigned nBitS2, unsigned nSgnS2, unsigned nIntS2, unsigned nFracS2, unsigned nZeroS2, int nBaseS2>
    sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT> add_saturate(const sfp<nBitS1, nSgnS1, nIntS1, nFracS1, nZeroS1, nBaseS1> s1, const sfp<nBitS2, nSgnS2, nIntS2, nFracS2, nZeroS2, nBaseS2> s2) {
        using type = sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>;
        
        const type s1c = convert<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>(s1);
        const type s2c = convert<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>(s2);
        const int64_t raw = s1c.raw_value() + s2c.raw_value();
        return with_raw_value(saturate<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>(raw));
    }

    template<unsigned nBitT, unsigned nSgnT = 1, unsigned nIntT = 0, unsigned nFracT = (nBitT - nSgnT - nIntT), unsigned nZeroT = (nBitT - nSgnT - nIntT - nFracT), int nBaseT = 0, unsigned nBitS1, unsigned nSgnS1, unsigned nIntS1, unsigned nFracS1, unsigned nZeroS1, int nBaseS1, unsigned nBitS2, unsigned nSgnS2, unsigned nIntS2, unsigned nFracS2, unsigned nZeroS2, int nBaseS2>
    sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT> add_overflow(const sfp<nBitS1, nSgnS1, nIntS1, nFracS1, nZeroS1, nBaseS1> s1, const sfp<nBitS2, nSgnS2, nIntS2, nFracS2, nZeroS2, nBaseS2> s2) {
        using type = sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>;
        
        const type s1c = convert<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>(s1);
        const type s2c = convert<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT>(s2);
        return with_raw_value(s1c.raw_value() + s2c.raw_value());
    }
} // namespace imfp

#endif // IMFP_DSP_HPP
