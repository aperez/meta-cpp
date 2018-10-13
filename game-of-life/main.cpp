#include "common/list.hpp"

#include "gol.hpp"
#include "printer.hpp"

using namespace meta::gol;

int main() {

    using gol_board = make_board<
        meta::list<dc,lc,dc,dc,dc,dc,dc>,
        meta::list<dc,dc,lc,dc,dc,dc,dc>,
        meta::list<lc,lc,lc,dc,dc,dc,dc>,
        meta::list<dc,dc,dc,dc,dc,dc,dc>,
        meta::list<dc,dc,dc,dc,dc,dc,dc>,
        meta::list<dc,dc,dc,dc,dc,dc,dc>,
        meta::list<dc,dc,dc,dc,dc,dc,dc>
        >;

    std::cout << "Board:" << std::endl;
    printer<gol_board>::print();

    std::cout << "\nAfter 1 step:" << std::endl;
    printer<step<gol_board, meta::num_one>>::print();

    std::cout << "\nAfter 2 steps:" << std::endl;
    printer<step<gol_board, meta::num<2>>>::print();

    std::cout << "\nAfter 10 steps:" << std::endl;
    printer<step<gol_board, meta::num<10>>>::print();

    std::cout << "\nAfter 30 steps:" << std::endl;
    printer<step<gol_board, meta::num<30>>>::print();

    return 0;
}
