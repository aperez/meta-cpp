#pragma once

#include "common/printer.hpp"

#include "gol.hpp"

namespace meta {
namespace gol {

template <typename row_list>
struct _printer {
    static constexpr auto& print(std::ostream& os = std::cout) {
        meta::printer<peek<row_list>>::print(os);
        newline_printer::print(os);
        return _printer<pop<row_list>>::print(os);
    }
};

template <>
struct _printer<list<>> {
    static constexpr auto& print(std::ostream& os = std::cout) {
        return os;
    }
};

template <typename b>
using printer = _printer<typename b::list>;

}
}
