/** \file imfp_exception.hpp
    \brief Run-time exceptions.
*/

#ifndef IMFP_EXCEPTION_HPP
#define IMFP_EXCEPTION_HPP

#include <exception>

namespace imfp
{
	namespace representation {
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
    
	namespace conversion {
		/// DoF mismatch.
		/**
		 * Degree of freedom of source and target must be the same.
		 */
		class dof_mismatch_exception: public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Degree of freedom of source and target must be the same.";
			}
		};

		/// Insufficient DoF.
		/**
		 * Degree of freedom is not engough for the conversion.
		 */
		class insufficient_dof_exception: public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Degree of freedom is not engough for the conversion.";
			}
		};
	}
}

#endif // IMFP_EXCEPTION_HPP
