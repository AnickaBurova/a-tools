#pragma once

#include <cstdint>
#include <string>
#include <vector>


// template< typename tEnumType >
// size_t get_range_size(){return 0;}
//
// template< typename tAnyType>
// std::vector<tAnyType> get_range(){throw "";};
//
// template<>
// size_t get_range_size<bool>(){return 2;}
//
// template<>
// std::vector<bool> get_range<bool>()
// {
// 	return {false,true};
// };

std::string to_string(bool value)
{
	return value ? "true" : "false";
}


/**
 * Helper class to easily apply bit masks.
 * Usage:
 * 		CBitBuilder<0x80>(truetoapplythemask).GetValue();
 * 		CBitBuilder<0x80>(false).Set<0x40>(true).Set<0x20>(true).GetValue();
 *
 */
template< int TInitBits >
class CBitBuilder
{
	int mValue;

public:
    /**
	* Using this constructor, will turn TInitBits on, if passed value is true.
    */
	inline CBitBuilder( bool on ) : mValue( on ? TInitBits : 0 ){};

    /**
	* Using this constructor, will mask the passed value and TInitBits.
     */
	inline CBitBuilder( int value ) : mValue( value & TInitBits ){}

    /**
     * Turn TBits on if passed value is true.
     */
	template< int TBits >
	inline CBitBuilder & Set( bool on )
	{
		mValue |= on ? TBits : 0;

		return *this;
	}

    /**
     * Mask the passed value with TBits.
     */
	template< int TBits >
	inline CBitBuilder & Set( int value )
	{
		mValue |= value & TBits;

		return *this;
	}

	/**
	 * Write signed value, and place the sign bit in TSignBit place.
	 */
	template< int TSignBit >
	inline CBitBuilder & SetSigned( int value )
	{
		mValue |= (( TSignBit << 1 ) - 1 ) & value;

		return *this;
	}

	/**
	 * Switch on value and apply b0 or b1. Only two values to apply.
	 */
	template< class TEnum, TEnum e0, int b0, TEnum e1, int b1 >
	inline CBitBuilder & SetEnum( TEnum value )
	{
		switch ( value )
		{
		case e0:
			mValue |= b0;
			break;

		case e1:
			mValue |= b1;
			break;

		default:
			break;
		}

		return *this;
	}

	/**
	 * Get the value calculated by applying bits to it.
	 * @return calculated value.
	 */
	int GetValue() const { return mValue; }
};

template< typename tType = unsigned >
constexpr auto get_bit_mask(uint32_t start, uint32_t size)
{
    return ((1 << size)-1) << start;
}

template < int tByteSize >
struct SignedOfSize;

template <  > struct SignedOfSize<1> {using Type = int8_t;};
template <  > struct SignedOfSize<2> {using Type = int16_t;};
template <  > struct SignedOfSize<4> {using Type = int32_t;};

template < typename tSignedType, typename tStoreType, int tBitStart, int tBitSize >
struct SignedInt
{
	using tS = typename SignedOfSize<sizeof(tStoreType)>::Type;
	static const int tBitToTop = sizeof(tStoreType) * 8 - tBitStart - tBitSize;
	static_assert(tBitToTop >= 0, "Encoded values won't fit in to tStoreType");
	// static_assert(sizeof(tSignedType) == sizeof(tStoreType), "Size of Signed type and Store type must be equal.");
	static tStoreType Encode(tSignedType input)
	{
		tStoreType a = ((tStoreType)input << (tBitToTop + tBitStart));
		return a >> tBitToTop;
	}

	static tSignedType Decode(tStoreType input)
	{
		tStoreType a = input << tBitToTop;
		return (tSignedType)((tS)a >> (tBitToTop + tBitStart));
	}
};
