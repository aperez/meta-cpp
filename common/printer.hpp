#pragma once

#include <iostream>

#include "list.hpp"
#include "string.hpp"

namespace meta {

template <typename typelist>
struct printer {
    static constexpr auto& print(std::ostream& os = std::cout) {
        os << peek<typelist>::value;
        return printer<pop<typelist>>::print(os);
    };
};

template <>
struct printer<list<>> {
    static constexpr auto& print(std::ostream& os = std::cout) {
        return os;
    };
};

template <typename... types>
struct printer<list<nil, types...>> :
        public printer<list<chr<' '>, types...>> {};

using newline_printer = printer<list<chr<'\n'>>>;

}
