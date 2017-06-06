#pragma once

#include <array>
#include <cstddef>
#include <ostream>
#include <type_traits>

/**
 * \brief
 * The main namespace.
 */
namespace hawtk {
	/**
	 * \brief
	 * \c hawt::tvec is a mathematical n-dimensional vector.
	 * The class provides some basic vector operations that are needed for example
	 * to calculate \c widget positions and boundaries.
	 * \tparam T the value type of each element
	 * \tparam N the dimension of the vector
	 */
	template <typename T, std::size_t N>
	class tvec final {
	public:
		using value_type = T;
		using size_type = std::size_t;
		using reference = value_type&;
		using const_reference = const value_type&;

	private:
		/**
		 * Storage of the size \c n for the elements of the vector.
		 */
		std::array<value_type, N> _elements;

	public:
		/**
		 * Constructs a vector with each element set to \c T{0}.
		 */
		tvec() : tvec{value_type{0}} {}

		/**
		 * Constructs a vector with each element set to \c value.
		 * \param value value to initialize each element
		 */
		explicit tvec(const value_type& value) {
			for (auto& element : _elements) {
				element = value;
			}
		}

		/**
		 * Constructs a vector from the list of parameters where <tt>sizeof...(args)
		 * == N</tt> and each element of \c args must be of type \c T.
		 * \param args the list of values from which to construct the vector
		 * \tparam Args the types of the arguments
		 */
		template <typename... Args, typename = typename std::enable_if<sizeof...(Args) == N>::type>
		tvec(Args&&... args) : _elements{{args...}} {}

		/**
		 * Returns the dimension of the vector.
		 * \return the dimension
		 */
		size_type size() const noexcept {
			return N;
		}

		/**
		 * Returns a reference to the component at specified location \c pos. No
		 * bounds checking is performed.
		 * \param pos position the component
		 */
		reference operator[](size_type pos) {
			return _elements[pos];
		}

		/**
		 * Returns a reference to the component at specified location \c pos. No
		 * bounds checking is performed.
		 * \param pos position the component
		 */
		const_reference operator[](size_type pos) const {
			return _elements[pos];
		}

		/**
		 * Adds the vector \f$\vec{u}\f$ to the given vector
		 * \f$\vec{v}\f$.
		 * \param rhs the vector \f$\vec{u}\f$
		 * \return \c *this
		 */
		tvec& operator+=(const tvec& rhs) {
			for (size_type index{0}; index < N; ++index) {
				_elements[index] += rhs[index];
			}
			return *this;
		}

		/**
		 * Adds the scalar \c rhs to each component of the given vector \f$\vec{v}\f$.
		 * \param rhs the scalar
		 * \return \c *this
		 */
		tvec& operator+=(const value_type& rhs) {
			for (auto& element : _elements) {
				element += rhs;
			}
			return *this;
		}

		/**
		 * Subtracts the vector \f$\vec{u}\f$ from the given vector
		 * \f$\vec{v}\f$.
		 * \param rhs the vector \f$\vec{u}\f$
		 * \return \c *this
		 */
		tvec& operator-=(const tvec& rhs) {
			for (size_type index{0}; index < N; ++index) {
				_elements[index] -= rhs[index];
			}
			return *this;
		}

		/**
		 * Subtracts the scalar \c rhs from each component of the given vector \f$\vec{v}\f$.
		 * \param rhs the scalar
		 * \return \c *this
		 */
		tvec& operator-=(const value_type& rhs) {
			for (auto& element : _elements) {
				element -= rhs;
			}
			return *this;
		}

		/**
		 * Multiplies the given vector \f$\vec{v}\f$ component-wise by the vector \f$\vec{u}\f$.
		 * \param rhs the vector \f$vec{u}\f$
		 * \return \c *this
		 */
		tvec& operator*=(const tvec& rhs) {
			for (size_type index{0}; index < N; ++index) {
				_elements[index] *= rhs[index];
			}
			return *this;
		}

		/**
		 * Scales the given vector \f$\vec{v}\f$ by \c rhs.
		 * \param rhs the scalar
		 * \return \c *this
		 */
		tvec& operator*=(const value_type& rhs) {
			for (auto& element : _elements) {
				element *= rhs;
			}
			return *this;
		}

		/**
		 * Devides the given vector \f$\vec{v}\f$ component-wise by the vector \f$\vec{u}\f$.
		 * \param rhs the vector \f$\vec{u}\f$
		 * \return \c *this
		 */
		tvec& operator/=(const tvec& rhs) {
			for (size_type index{0}; index < N; ++index) {
				_elements[index] /= rhs[index];
			}
			return *this;
		}

		/**
		 * Devides the given vector \f$\vec{v}\f$ by \c rhs.
		 * \param rhs the scalar
		 * \return \c *this
		 */
		tvec& operator/=(const value_type& rhs) {
			for (auto& element : _elements) {
				element /= rhs;
			}
			return *this;
		}

		/**
		 * Negates the given vector \f$\vec{v}\f$. This function takes only place in
		 * overload resolution if <tt>std::is_unsigned<T>::value == false</tt>
		 */
		template <typename U = value_type>
		typename std::enable_if_t<!std::is_unsigned<U>::value, tvec&> operator-() {
			return *this *= value_type{-1};
		}
	};

	/**
	 * Adds the value of type \c U to the vector \f$\vec{v}\f$ where \c U is
	 * either <tt>tvec<T, N></tt> or \c T.
	 * \param lhs the vector \f$\vec{v}\f$
	 * \param rhs either the vector \f$u\f$ or the scalar \f$s\f$
	 */
	template <typename T, std::size_t N, typename U>
	inline tvec<T, N> operator+(const tvec<T, N>& lhs, const U& rhs) {
		tvec<T, N> result{lhs};
		result += rhs;
		return result;
	}

	/**
	 * Subtracts the value of type \c U from the vector \f$\vec{v}\f$ where \c U
	 * is either <tt>tvec<T, N></tt> or \c T.
	 * \param lhs the vector \f$\vec{v}\f$
	 * \param rhs either the vector \f$u\f$ or the scalar \f$s\f$
	 */
	template <typename T, std::size_t N, typename U>
	inline tvec<T, N> operator-(const tvec<T, N>& lhs, const U& rhs) {
		tvec<T, N> result{lhs};
		result -= rhs;
		return result;
	}

	/**
	 * Multiplies the vector \f$\vec{v}\f$ by the value of type \c U where \c U
	 * is either <tt>tvec<T, N></tt> or \c T.
	 * \param lhs the vector \f$\vec{v}\f$
	 * \param rhs either the vector \f$u\f$ or the scalar \f$s\f$
	 */
	template <typename T, std::size_t N, typename U>
	inline tvec<T, N> operator*(const tvec<T, N>& lhs, const U& rhs) {
		tvec<T, N> result{lhs};
		result *= rhs;
		return result;
	}

	/**
	 * Devides the vector \f$\vec{v}\f$ by the value of type \c U where \c U
	 * is either <tt>tvec<T, N></tt> or \c T.
	 * \param lhs the vector \f$\vec{v}\f$
	 * \param rhs either the vector \f$u\f$ or the scalar \f$s\f$
	 */
	template <typename T, std::size_t N, typename U>
	inline tvec<T, N> operator/(const tvec<T, N>& lhs, const U& rhs) {
		tvec<T, N> result{lhs};
		result /= rhs;
		return result;
	}

	/**
	 * Writes a comma separated list with each component of the vector
	 * \f$\vec{v}\f$ to the \c std::ostream.
	 * \param lhs the \c std::ostream
	 * \param rhs the vector \f$\vec{v}\f$
	 */
	template <typename T, std::size_t N>
	inline std::ostream& operator<<(std::ostream& lhs, const tvec<T, N>& rhs) {
		lhs << "tvec{";
		for (typename tvec<T, N>::size_type index{0}; index < rhs.size(); ++index) {
			lhs << rhs[index];
			if (index < rhs.size() - 1) {
				lhs << ", ";
			}
		}
		lhs << "}";
		return lhs;
	}

	/**
	 * Alias for a two-dimensional floating point vector.
	 */
	using vec2 = tvec<float, 2>;
	/**
	 * Alias for an two-dimensional unsigned integer vector.
	 */
	using uvec2 = tvec<unsigned int, 2>;
	/**
	 * Alias for a four-component color value.
	 */
	using color = tvec<float, 4>;
}
