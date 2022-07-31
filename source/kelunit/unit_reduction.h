#pragma once

#include <cstdint>
#include <type_traits>

namespace kelun {
template<typename... T>
constexpr bool is_always_false = false;

template<typename UnitType, int64_t Exponent>
struct unit_base;

template<typename StorageT, typename... T>
class unit;

namespace impl {

template<typename T, typename U>
class unit_matching;

template<typename... T>
class unit_redux_list {
	static_assert(sizeof...(T) == 0, "Template type not supported");

	using reduced_typed = unit_redux_list<>;
};

template<typename T0, int64_t E0, typename... TL, int64_t... EL>
struct unit_redux_list<unit_base<T0,E0>, unit_base<TL,EL>...> {
	using reduced_type = typename unit_matching<unit_redux_list<unit_base<T0,E0>, unit_base<TL,EL>...>, unit_redux_list<>>::type;
};

template<typename T, typename U, typename V>
class unit_matching_reduce {
public:
	static_assert(is_always_false<T, U, V>, "Template type not supported");
};

template<typename T, int64_t E, typename T0, int64_t E0, typename... TL, int64_t... EL, typename... TR, int64_t... ER>
class unit_matching_reduce<unit_base<T,E>, unit_redux_list<unit_base<T0,E0>,unit_base<TL,EL>...>, unit_redux_list<unit_base<TR,ER>...>> {
public:
	static constexpr bool is_same = std::is_same_v<T,T0>;

	using match_reduce_type = typename std::conditional<is_same, unit_base<T,E+E0>, unit_base<T,E>>::type;
	using match_reduce_unit_redux_list = typename std::conditional<is_same, unit_redux_list<unit_base<TR,ER>...>, unit_redux_list<unit_base<TR,ER>..., unit_base<T0,E0>>>::type;

	using value_type = typename unit_matching_reduce<match_reduce_type, unit_redux_list<unit_base<TL,EL>...>, match_reduce_unit_redux_list>::value_type;
	using unit_redux_list_type = typename unit_matching_reduce<match_reduce_type, unit_redux_list<unit_base<TL,EL>...>, match_reduce_unit_redux_list>::unit_redux_list_type;

	static constexpr int64_t value_num = unit_matching_reduce<match_reduce_type, unit_redux_list<unit_base<TL,EL>...>, match_reduce_unit_redux_list>::value_num;
};

template<typename T, int64_t E, typename... TR, int64_t... ER>
class unit_matching_reduce<unit_base<T,E>, unit_redux_list<>, unit_redux_list<unit_base<TR,ER>...>> {
public:
	using value_type = unit_base<T,E>;
	using unit_redux_list_type = unit_redux_list<unit_base<TR,ER>...>;

	static constexpr int64_t value_num = E;
};

template<typename T, typename U>
class unit_matching {
	static_assert(is_always_false<T, U>, "Template type not supported");
};

template<typename... T, int64_t... E>
class unit_matching<unit_redux_list<>,unit_redux_list<unit_base<T,E>...>> {
public:
	using type = unit_redux_list<unit_base<T,E>...>;

};

template<typename T0, int64_t E0, typename... TL, int64_t... EL, typename... TR, int64_t... ER>
class unit_matching<unit_redux_list<unit_base<T0,E0>,unit_base<TL,EL>...>, unit_redux_list<unit_base<TR,ER>...>> {
public:
	using reduced_value_type = typename unit_matching_reduce<unit_base<T0,E0>, unit_redux_list<unit_base<TL,EL>...>, unit_redux_list<>>::value_type;
	using reduced_unit_redux_list_type = typename unit_matching_reduce<unit_base<T0,E0>, unit_redux_list<unit_base<TL,EL>...>, unit_redux_list<>>::unit_redux_list_type;

	static constexpr int64_t reduced_value_num = unit_matching_reduce<unit_base<T0,E0>, unit_redux_list<unit_base<TL,EL>...>, unit_redux_list<>>::value_num;
	using reduced_result_unit_redux_list = typename std::conditional<reduced_value_num == 0, unit_redux_list<unit_base<TR,ER>...>, unit_redux_list<unit_base<TR,ER>...,reduced_value_type>>::type;

	using type = typename unit_matching<reduced_unit_redux_list_type, reduced_result_unit_redux_list>::type;
};

template<typename List, typename StorageT>
class unit_matching_add_storage {
public:
	static_assert(is_always_false<List,StorageT>, "Template type not supported");
};

template<typename StorageT, typename... UnitTypes, int64_t... UnitExponents>
class unit_matching_add_storage<unit_redux_list<unit_base<UnitTypes,UnitExponents>...>, StorageT> {
public:
	using type = unit<StorageT, unit_base<UnitTypes,UnitExponents>...>;
};

}

template<typename StorageT, typename... T>
class unit_reduction {
	static_assert(is_always_false<StorageT,T...>, "Template type not supported");
};

template<typename StorageT, typename... UnitT, int64_t... UnitE>
class unit_reduction<StorageT, unit_base<UnitT, UnitE>...> {
public:
	using list_type = typename impl::unit_matching<impl::unit_redux_list<unit_base<UnitT, UnitE>...>, impl::unit_redux_list<>>::type;
	using type = typename impl::unit_matching_add_storage<list_type, StorageT>::type;
};

template<typename StorageT, typename... T>
class unit_invert {
	static_assert(is_always_false<StorageT, T...>, "Template type not supported");
};

template<typename StorageT, typename... UnitT, int64_t... UnitE>
class unit_invert<StorageT, unit_base<UnitT, UnitE>...> {
public:
	using type = unit<StorageT, unit_base<UnitT, -UnitE>...>;
};

template<typename T, typename U>
class unit_multiplication{
	static_assert(is_always_false<T, U>, "Template type not supported");
};

template<typename StorageT, typename... UnitT, int64_t... UnitE, typename... UnitRhsT, int64_t... UnitRhsE>
class unit_multiplication<unit<StorageT, unit_base<UnitT,UnitE>...>, unit<StorageT, unit_base<UnitRhsT, UnitRhsE>...>> {
public:
	using type = typename unit_reduction<StorageT, unit_base<UnitT,UnitE>..., unit_base<UnitRhsT, UnitRhsE>...>::type;
};
}
