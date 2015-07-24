#pragma once

#include <map>
#include <string>
#include <vector>
#include "stringtools.h"
#include "long_macro_expansion.h"


#define ___ENUM_STRING_PAIR(value) {__et::value,to_snake_case(#value,' ')},
#define ___TO_STR(value) to_snake_case(#value,' '),
#define ___INC_RES(a) res++;
#define ___ENUM_VALUE(value) __et::value,

#define ENUM_TOOLS  \
template< typename tEnumType >\
size_t get_range_size(){return 0;}\
\
template< typename tEnumType>\
std::vector<tEnumType> get_range(){throw "";};



#define ENUM_DECLARE(enum_type,...) \
    enum class enum_type { __VA_ARGS__ }; \
    template<>\
    size_t (get_range_size<enum_type>)()\
    {\
        struct counter{ static constexpr size_t count(){ size_t res = 0;___EXECUTE(___INC_RES,__VA_ARGS__);return res;}};\
        constexpr size_t size = counter::count();\
        return size; \
    } \
    template<>\
    std::vector<enum_type> get_range<enum_type>()\
    {\
        using __et = enum_type;\
        return std::vector<enum_type>{\
            ___EXECUTE(___ENUM_VALUE,__VA_ARGS__)\
        };\
    }

#define ENUM_TO_STRING(enum_type,...) \
    std::string to_string(enum_type value) \
    {\
        using __et = enum_type; \
        static std::string _vals[] = { \
            ___EXECUTE(___TO_STR,__VA_ARGS__) \
        }; \
        static auto count = sizeof(_vals) / sizeof(_vals[0]);\
        if((int)value < 0 || (int)value >= count)return std::to_string((int)value);\
 \
        return _vals[(int)value];\
    }

#define ENUM_TO_STRING_EX(enum_type,...) \
    std::string to_string(enum_type value) \
    {\
        using __et = enum_type; \
        static std::map<__et,std::string> _vals{ \
            ___EXECUTE(___ENUM_STRING_PAIR,__VA_ARGS__) \
        }; \
        auto _res = _vals.find(value); \
 \
        return _res != _vals.end() ? _res->second : std::to_string((int)value); \
    }

#define ENUM1(enum_type,w1,...)  w1(enum_type,__VA_ARGS__)
#define ENUM2(enum_type,w1,w2,...)   ENUM1(enum_type,w1,__VA_ARGS__) w2(enum_type,__VA_ARGS__)
#define ENUM3(enum_type,w1,w2,w3,...)   ENUM2(enum_type,w1,w2,__VA_ARGS__) w3(enum_type,__VA_ARGS__)

#define ENUMS(enum_type,...) ENUM2(enum_type,ENUM_DECLARE,ENUM_TO_STRING,__VA_ARGS__)
