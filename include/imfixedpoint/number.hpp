#ifndef IMFP_NUMBER_HPP
#define IMFP_NUMBER_HPP

#include <cmath>

namespace imfp
{
    namespace {
        using sfp_float_t = double;
    }

	template<unsigned nBit, unsigned nSgn = 1, unsigned nInt = 0, unsigned nFrac = (nBit - nSgn - nInt), unsigned nZero = (nBit - nSgn - nInt - nFrac), int nBase = 0>
	class sfp {
        int64_t mVal{0};
		
        void check_valid_template() {
            static_assert(nSgn >= 1, "nSgn should >= 1");
            static_assert(nSgn + nInt + nFrac + nZero == nBit, "nSgn + nInt + nFrac + nZero != nBit");
            static_assert(nBit <= 64, "nBit should <= 64");
        }
        
	public:
        /// Constructor
        /**
         Check if the template parameters are correct.
         */
		sfp() {
			check_valid_template();
		}
        
        /// Get value
        /**
		 * Get the floating-point value.
		 * \return floating-point value
         */
        sfp_float_t value() {
            static const double r = 1. / (static_cast<int64_t>(1) << (nFrac + nZero - nBase));
            
            return mVal * r;
        }
        
        /// Set value
        /**
		 * Round the floating-point value to the nearest fixed-point value.
		 * \param val floating-point value
         */
        sfp& operator=(const sfp_float_t val) {
            static const double r = static_cast<int64_t>(1) << (nFrac + nZero - nBase);
            mVal = static_cast<int64_t>(std::round(val * r));
            
            return *this;
        }
	};
} // namespace imfp

#endif // IMFP_NUMBER_HPP
