#pragma once

#include "./unit_reduction.h"

namespace kelun {
template<typename UnitType, int64_t Exponent>
struct unit_base {};

template<typename StorageT, typename... T>
class unit;

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
class unit<StorageT, unit_base<UnitTypes, Exponents>...> {
public:
	using value_type = StorageT;

	unit() = default;

	unit(const unit<StorageT,unit_base<UnitTypes, Exponents>...>&) = default;
	unit(unit<StorageT,unit_base<UnitTypes,Exponents>...>&&) = default;

	unit<StorageT,unit_base<UnitTypes,Exponents>...>& operator=(const unit<StorageT,unit_base<UnitTypes,Exponents>...>&) = default;
	unit<StorageT,unit_base<UnitTypes,Exponents>...>& operator=(unit<StorageT,unit_base<UnitTypes,Exponents>...>&&) = default;

	unit(const value_type&);
	unit(value_type&&);

	unit<StorageT,unit_base<UnitTypes,Exponents>...>& operator=(const value_type&);
	unit<StorageT,unit_base<UnitTypes,Exponents>...>& operator=(value_type&&);

	unit<StorageT,unit_base<UnitTypes,Exponents>...> operator+(const unit<StorageT,unit_base<UnitTypes,Exponents>...>& rhs);
	unit<StorageT,unit_base<UnitTypes,Exponents>...> operator-(const unit<StorageT,unit_base<UnitTypes,Exponents>...>& rhs);

	template<typename... Trhs>
	typename unit_multiplication<unit<StorageT,unit_base<UnitTypes,Exponents>...>, unit<StorageT,Trhs...>>::type operator*(const unit<StorageT, Trhs...>& rhs);
	
	template<typename... Trhs>
	typename unit_multiplication<unit<StorageT, unit_base<UnitTypes,Exponents>...>, typename unit_invert<StorageT,Trhs...>::type>::type operator/(const unit<StorageT, Trhs...>& rhs);

	value_type data() const;
private:
	value_type value;
};

template<typename S>
using scalar = unit<S>;
}

#include "unit.tmpl.h"
