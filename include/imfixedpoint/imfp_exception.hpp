#ifndef IMFP_EXCEPTION_HPP
#define IMFP_EXCEPTION_HPP

#include <exception>

namespace imfp
{
    /// Invalid sign bits.
	/**
	 * All the sign bits should be the same value.
	 */
	class invalid_sign_bits_exception: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "All sign bits should be the same value.";
		}
	};

	/// Invalid zero bits.
	/**
	 * All the zero bits should be 0.
	 */
    class invalid_zero_bits_exception: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "All zero bits should be 0.";
        }
    };
}

#endif // IMFP_EXCEPTION_HPP
