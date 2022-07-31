#pragma once

#include "../unit.h"

namespace kelun {
namespace unit_type {
struct second{
	static constexpr std::string_view name = "second";
	static constexpr std::string_view short_name = "s";
};
}

template<typename S>
using second = unit<S,unit_base<unit_type::second,1>>;
}
