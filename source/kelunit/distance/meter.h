#pragma once

#include "../unit.h"

#include <string_view>

namespace kelun {
namespace unit_type {
struct meter{
	static constexpr std::string_view name = "meter";
	static constexpr std::string_view short_name = "m";
};
}

template<typename S>
using meter = unit<S,unit_base<unit_type::meter,1>>;

template<typename S>
using square_meter = unit<S,unit_base<unit_type::meter,2>>;
}
