#include <utility>

namespace kelun {

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
unit<StorageT,unit_base<UnitTypes, Exponents>...>::unit(const value_type& value_):
	value{value_}{}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
unit<StorageT,unit_base<UnitTypes, Exponents>...>::unit(value_type&& value_):value{std::move(value_)}{}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
unit<StorageT,unit_base<UnitTypes, Exponents>...>& unit<StorageT,unit_base<UnitTypes, Exponents>...>::operator=(const typename unit<StorageT,unit_base<UnitTypes, Exponents>...>::value_type& value_){
	value = value_;
	return *this;
}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
unit<StorageT,unit_base<UnitTypes, Exponents>...>& unit<StorageT,unit_base<UnitTypes, Exponents>...>::operator=(typename unit<StorageT,unit_base<UnitTypes, Exponents>...>::value_type&& value_){
	value = std::move(value_);
	return *this;
}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
unit<StorageT,unit_base<UnitTypes, Exponents>...> unit<StorageT,unit_base<UnitTypes, Exponents>...>::operator+(const unit<StorageT,unit_base<UnitTypes, Exponents>...>& rhs){
	return value + rhs.value;
}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
unit<StorageT,unit_base<UnitTypes, Exponents>...> unit<StorageT,unit_base<UnitTypes, Exponents>...>::operator-(const unit<StorageT,unit_base<UnitTypes, Exponents>...>& rhs){
	return value - rhs.value;
}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
template<typename... Trhs>
typename unit_multiplication<unit<StorageT,unit_base<UnitTypes,Exponents>...>, unit<StorageT, Trhs...>>::type
unit<StorageT,unit_base<UnitTypes, Exponents>...>::operator*(const unit<StorageT,Trhs...>& rhs){
	return value * rhs.data();
}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
template<typename... Trhs>
typename unit_multiplication<unit<StorageT,unit_base<UnitTypes,Exponents>...>, typename unit_invert<StorageT,Trhs...>::type>::type 
unit<StorageT,unit_base<UnitTypes,Exponents>...>::operator/(const unit<StorageT, Trhs...>& rhs){
	typename unit_invert<StorageT, Trhs...>::type rhs_inverted{static_cast<StorageT>(1)/rhs.data()};
	return value * rhs_inverted.data();
}

template<typename StorageT, typename... UnitTypes, int64_t... Exponents>
typename unit<StorageT,unit_base<UnitTypes, Exponents>...>::value_type unit<StorageT,unit_base<UnitTypes, Exponents>...>::data() const {
	return value;
}
}
