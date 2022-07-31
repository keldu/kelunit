#include "./unit.h"

#include <iostream>


namespace std {
template<typename UnitT, int64_t UnitE>
inline ostream& operator<<(ostream& o, const kelun::unit_base<UnitT,UnitE>& ele){
	o<<UnitT::short_name;
	if constexpr ( UnitE != 1 ){
		o<<'^'<<'('<<UnitE<<')';
	}
	return o;
}
}

namespace kelun {
template<typename... T>
struct unit_print_impl {
	static_assert(is_always_false<T...>, "Template type not supported");
};

template<typename UnitT, int64_t UnitE, typename... UnitTL, int64_t... UnitEL>
struct unit_print_impl<unit_base<UnitT,UnitE>,unit_base<UnitTL,UnitEL>...> {
	static std::ostream& print(std::ostream& o){
		
		unit_base<UnitT,UnitE> element;

		std::ostream& o_ret = o << element;

		if constexpr (sizeof...(UnitTL) > 0){
			std::ostream& o_ret_next = o_ret << ' ' << '*' << ' ';
			return unit_print_impl<unit_base<UnitTL,UnitEL>...>::print(o_ret_next);
		}

		return o_ret<<']';
	}
};
}

namespace std {

template<typename StorageT, typename... T>
inline ostream& operator<<(ostream& o, const kelun::unit<StorageT,T...>& unit);

template<typename StorageT, typename... UnitT, int64_t... UnitE>
inline ostream& operator<<(ostream& o, const kelun::unit<StorageT,kelun::unit_base<UnitT,UnitE>...>& unit){
	o << unit.data();
	if constexpr (sizeof...(UnitT) > 0) {
		auto& o_ret = o << ' '<<'[';
		return kelun::unit_print_impl<kelun::unit_base<UnitT,UnitE>...>::print(o_ret);
	}
	return o;
}
}
