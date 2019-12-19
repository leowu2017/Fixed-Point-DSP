/** \file number.hpp
    \brief Fixed-point number difinition.
*/

#ifndef IMFP_NUMBER_HPP
#define IMFP_NUMBER_HPP

#include <cmath>
#include <imfixedpoint/imfp_exception.hpp>

namespace imfp
{
    namespace {
        using sfp_float_t = double;
        
        struct double_val {
            double mVal;
            double_val(double val) {
                mVal = val;
            }
        };
        
        struct raw_val {
            int64_t mVal;
            raw_val(int64_t val): mVal(val) {}
        };
    
        template<unsigned begin, unsigned end>
        constexpr int64_t generate_mask() {
            return ((static_cast<int64_t>(1) << (end - begin)) - 1) << begin;
        }
    }

    /// Helper to assign floating-point value.
    /**
     * \fn double_val with_value(sfp_float_t val)
     * \param val floating-point value
    */
    double_val with_value(sfp_float_t val) {
        return val;
    }

    /// Helper to assign fixed-point raw value.
    /**
     * \fn raw_val with_raw_value(int64_t val)
     * \param val fixed-point raw value
    */
    raw_val with_raw_value(int64_t val) {
        return val;
    }

    template<unsigned nBit, unsigned nSgn = 1, unsigned nInt = 0, unsigned nFrac = (nBit - nSgn - nInt), unsigned nZero = (nBit - nSgn - nInt - nFrac), int nBase = 0>
    class sfp {
        // stored value
        int64_t mVal{0};
        
        void check_valid_template() const {
            static_assert(nSgn >= 1, "nSgn should >= 1");
            static_assert(nSgn + nInt + nFrac + nZero == nBit, "nSgn + nInt + nFrac + nZero != nBit");
            static_assert(nBit <= 64, "nBit should <= 64");
        }
        
        static constexpr int64_t sign_mask = generate_mask<nBit - nSgn, nBit>();
        static constexpr int64_t sign_extened_mask = generate_mask<nBit, 64>();
        static constexpr int64_t zero_mask = generate_mask<0, nZero>();
        static constexpr int64_t zero_complement_mask = ~zero_mask;
        
        /* helper functions */
        bool invalid_sign_bits(int64_t val) const {
            int64_t m = val & sign_mask;
            return m != 0 && m != sign_mask;
        }
        
        bool invalid_zero_bits(int64_t val) const {
            return (val & zero_mask) != 0;
        }
        
        bool is_negative(int64_t val) const {
            return val & sign_mask;
        }
        
        /* set value */
        void setFloat(sfp_float_t val) {
            static constexpr double r = static_cast<int64_t>(1) << (nFrac + nZero - nBase);
            mVal = static_cast<int64_t>(std::round(val * r)) & zero_complement_mask;
        }
        
        void setRaw(int64_t val) {
            // Check if every sign bits have the same value.
            if constexpr (nSgn > 1) {
                if (invalid_sign_bits(val)) {
                    throw representation::invalid_sign_bits_exception();
                }
            }
            
            if constexpr (nZero > 0) {
                if (invalid_zero_bits(val)) {
                    throw representation::invalid_zero_bits_exception();
                }
            }

            if (is_negative(val)) {
                val |= sign_extened_mask;
            }
            
            mVal = val;
        }
        
    public:
        /// Type
        using type = sfp<nBit, nSgn, nInt, nFrac, nZero, nBase>;
        /// Max value
        static const type max;// = with_raw_value(generate_mask<nZero, (nInt + nFrac + nZero)>());
        /// Min value
        static const type min;// = with_raw_value(generate_mask<(nBit - nSgn), 64>());
        
        /// Constructor
        /**
         * Default value is 0;
         */
        sfp() {
            check_valid_template();
        }
        
        /// Copy constructor
        sfp(sfp const &i) {
            mVal = i.mVal;
        }
        
        /// Floating-point constructor
        /**
         * Initialize with a floating-point value.
         * \sa with_value()
         */
        sfp(double_val v) {
            check_valid_template();
            
            setFloat(v.mVal);
        }
        
        /// Fixed-point constructor
        /**
         * Initialize with a fixed-point raw value.
         * \sa with_raw_value()
         */
        sfp(raw_val v) {
            check_valid_template();
            
            setRaw(v.mVal);
        }
        
        /// Set the value.
        /**
         * Round the floating-point value to the nearest fixed-point value.
         * \param val floating-point value
         */
        void set_value(const sfp_float_t val) {
            setFloat(val);
        }
        
        /// Get the value.
        /**
         * Get the floating-point value.
         * \return floating-point value
         */
        sfp_float_t value() const {
            static constexpr double r = 1. / (static_cast<int64_t>(1) << (nFrac + nZero - nBase));
            
            return mVal * r;
        }
        
        /// Set the raw value.
        /**
         * Set the fixed-point raw value.
         * \param val fixed-point raw value
         */
        void set_raw_value(int64_t val) {
            setRaw(val);
        }
        
        /// Get the raw value.
        /**
         * Get the fixed-point raw value.
         * \return fixed-point raw value
         */
        int64_t raw_value() const {
            return mVal;
        }

        /// Overload operator=
        /**
         * \sa with_value()
         */
        sfp& operator=(const double_val v) {
            setFloat(v.mVal);
            
            return *this;
        }

        /// Overload operator=
        /**
         * \sa with_raw_value()
         */
        sfp& operator=(const raw_val v) {
            setRaw(v.mVal);
            
            return *this;
        }
        
        template<unsigned nBitT, unsigned nSgnT, unsigned nIntT, unsigned nFracT, unsigned nZeroT, int nBaseT>
        bool operator<(sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT> const &v) const {
            return value() < v.value();
        }
        
        template<unsigned nBitT, unsigned nSgnT, unsigned nIntT, unsigned nFracT, unsigned nZeroT, int nBaseT>
        bool operator<=(sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT> const &v) const {
            return value() <= v.value();
        }
        
        template<unsigned nBitT, unsigned nSgnT, unsigned nIntT, unsigned nFracT, unsigned nZeroT, int nBaseT>
        bool operator>(sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT> const &v) const {
            return value() > v.value();
        }
        
        template<unsigned nBitT, unsigned nSgnT, unsigned nIntT, unsigned nFracT, unsigned nZeroT, int nBaseT>
        bool operator>=(sfp<nBitT, nSgnT, nIntT, nFracT, nZeroT, nBaseT> const &v) const {
            return value() >= v.value();
        }
    };

    // initialize max
    template<unsigned nBit, unsigned nSgn, unsigned nInt, unsigned nFrac, unsigned nZero, int nBase>
    const sfp<nBit, nSgn, nInt, nFrac, nZero, nBase> sfp<nBit, nSgn, nInt, nFrac, nZero, nBase>::max = with_raw_value(generate_mask<nZero, (nInt + nFrac + nZero)>());

    // initialize min
    template<unsigned nBit, unsigned nSgn, unsigned nInt, unsigned nFrac, unsigned nZero, int nBase>
    const sfp<nBit, nSgn, nInt, nFrac, nZero, nBase> sfp<nBit, nSgn, nInt, nFrac, nZero, nBase>::min = with_raw_value(generate_mask<(nBit - nSgn), 64>());


} // namespace imfp

#endif // IMFP_NUMBER_HPP
