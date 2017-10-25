#pragma once

#define CREATE_ALIAS(type)\
    template <typename... args> using type = typename _##type<args...>::result
