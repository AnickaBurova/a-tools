#pragma once

#include <istream>
#include <iostream>
#include <vector>

template< class tValueType >
inline tValueType read_value( std::istream& reader )
{
	tValueType value;

	reader.read((char*)&value,sizeof(value));

	return value;
}

template < typename tValueType >
inline void write_value(std::ostream& writer, const tValueType& value)

{
	writer.write((char*)&value,sizeof(tValueType));
}

template < typename tHead, typename ...tTail >
tHead read_value_from_stream(std::istream& reader)
{
    return read_value<tHead>(reader);
}

template < typename ...tTail >
std::tuple<tTail...> read_from_stream(std::istream& reader,std::tuple<tTail...>&&)
{
    return std::tuple<tTail...>(read_value<tTail>(reader)...);
}
template < typename ...tTail >
std::tuple<tTail...> read_from_stream(std::istream& reader)
{
    return std::tuple<tTail...>(read_value<tTail>(reader)...);
}

namespace
{
	template < int tIndex, int tSize, typename ...tTail >
	struct ___WriteToStream
	{
	    static void write(std::ostream& writer, const std::tuple<tTail...>& value)
	    {
	        write_value(writer,std::get<tIndex>(value));
	        ___WriteToStream<tIndex+1,tSize-1,tTail...>::write(writer,value);
	    }
	};

	template < int tIndex, typename ...tTail >
	struct ___WriteToStream<tIndex,1,tTail...>
	{
	    static void write(std::ostream& writer, const std::tuple<tTail...>& value)
	    {
	        write_value(writer,std::get<tIndex>(value));
	    }
	};
}

template < typename ...tTail >
void write_to_stream(std::ostream& writer, const std::tuple<tTail...>& value)
{
    ___WriteToStream<0,sizeof...(tTail),tTail...>::write(writer,value);
}

struct int32_rev_t
{
    int value;
    int32_rev_t():value{}{}

    int32_rev_t(int val)
        :value{val}
    { }

    operator int()const
    {
        return value;
    }

    int32_rev_t& operator=(int val)
    {
        value = val;
        return *this;
    }

    template < typename tIntType >
    int32_rev_t& operator|=(const tIntType& val)
    {
        value |= val;
        return *this;
    }
};

struct uint32_rev_t
{
    uint32_t value;
    uint32_rev_t():value{}{}

    uint32_rev_t(uint32_t val)
        :value{val}
    { }

    operator uint32_t()const
    {
        return value;
    }

    uint32_rev_t& operator=(uint32_t val)
    {
        value = val;
        return *this;
    }

    template < typename tIntType >
    uint32_rev_t& operator|=(const tIntType& val)
    {
        value |= val;
        return *this;
    }
};

template <  >
inline int32_rev_t read_value<int32_rev_t>( std::istream& reader )
{
	int32_rev_t value;

	reader.read((char*)&value.value + 3,1);
	reader.read((char*)&value.value + 2,1);
	reader.read((char*)&value.value + 1,1);
	reader.read((char*)&value.value + 0,1);

	return value;
}

template <  >
inline void write_value<int32_rev_t>(std::ostream& writer, const int32_rev_t& value)
{
	writer.write((char*)&value.value + 3,1);
	writer.write((char*)&value.value + 2,1);
	writer.write((char*)&value.value + 1,1);
	writer.write((char*)&value.value + 0,1);
}

template <  >
inline uint32_rev_t read_value<uint32_rev_t>( std::istream& reader )
{
	uint32_rev_t value;

	reader.read((char*)&value.value + 3,1);
	reader.read((char*)&value.value + 2,1);
	reader.read((char*)&value.value + 1,1);
	reader.read((char*)&value.value + 0,1);

	return value;
}

template <  >
inline void write_value<uint32_rev_t>(std::ostream& writer, const uint32_rev_t& value)
{
	writer.write((char*)&value.value + 3,1);
	writer.write((char*)&value.value + 2,1);
	writer.write((char*)&value.value + 1,1);
	writer.write((char*)&value.value + 0,1);
}

struct int24_t
{
    int32_t value;
    int24_t():value{}{}

    int24_t(int32_t val)
        :value{val}
    { }

    operator int32_t()const
    {
        return value;
    }

    int24_t& operator=(int32_t val)
    {
        value = val;
        return *this;
    }

    template < typename tIntType >
    int24_t& operator|=(const tIntType& val)
    {
        value |= val;
        return *this;
    }
};

template <  >
inline int24_t read_value<int24_t>( std::istream& reader )
{
	int24_t value;

	*((char*)&value + 3) = 0;
	reader.read((char*)&value.value + 0,3);

	return value;
}

template <  >
inline void write_value<int24_t>(std::ostream& writer, const int24_t& value)
{
	writer.write((char*)&value.value + 0,3);
}

struct uint24_t
{
    uint32_t value;
    uint24_t():value{}{}

    uint24_t(uint32_t val)
        :value{val}
    { }

    operator uint32_t()const
    {
        return value;
    }

    uint24_t& operator=(uint32_t val)
    {
        value = val;
        return *this;
    }

    template < typename tIntType >
    uint24_t& operator|=(const tIntType& val)
    {
        value |= val;
        return *this;
    }
};

template <  >
inline uint24_t read_value<uint24_t>( std::istream& reader )
{
	uint24_t value;

	*((char*)&value + 3) = 0;
	reader.read((char*)&value.value + 0,3);

	return value;
}

template <  >
inline void write_value<uint24_t>(std::ostream& writer, const uint24_t& value)
{
	writer.write((char*)&value.value + 0,3);
}
