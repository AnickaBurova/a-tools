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
constexpr auto get_bit_mask(int start, int size)
{
    return ((1 << size)-1) << start;
	// tType mask = 0;
	// while(size --> 0)
	// {
	// 	mask <<= 1;
	// 	mask |= 1;
	// }
	// return mask << start;
}

template< typename tMaskType, typename tIntType >
tMaskType get_signed_to_mask(tIntType value )
{
    return value < 0 ? ~(tMaskType)(-value) + 1 : value;
}

template < typename tIntType, int tBitSign, typename tMaskType >
tIntType get_signed_from_mask(tMaskType mask)
{
    return ((1 << tBitSign) & mask) ? (tIntType)mask | ~get_bit_mask(0,tBitSign) : mask;
 // 	return ((1 << tBitSign) & mask) ? -~(mask - 1) : mask;
}
