
#include <gtest/gtest.h>
#include "bittools.h"
#include "stringtools.h"
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/adaptor/type_erased.hpp>
#include <boost/range/adaptor/tokenized.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/any_range.hpp>

using namespace std;

TEST(bittools, mask)
{
    EXPECT_EQ(1, get_bit_mask(0,1));

    EXPECT_EQ(0b11, get_bit_mask(0,2));

    EXPECT_EQ(0b110, get_bit_mask(1,2));
    EXPECT_EQ(0b1100, get_bit_mask(2,2));

    EXPECT_EQ(0b11111100000, get_bit_mask(5,6));
}


TEST(stringtools, snake_case)
{
    EXPECT_EQ("this_is_snake_case",to_snake_case("ThisIsSnakeCase"));
    EXPECT_EQ("this is snake case",to_snake_case("ThisIsSnakeCase",' '));
}

TEST(signed_numbers, conversion)
{
    using I = int8_t;
    using S = uint8_t;

    for(I&& a : boost::irange(numeric_limits<I>::min(),numeric_limits<I>::max()))
    {
        S b = (S)a;
        S c = ~(S)(-a) + 1;

        EXPECT_EQ(  b, c );
        I d = (I)b;
        EXPECT_EQ(a, d);
    }

    const int tBitStart = 0;
    const int tBitSize = 8;
    const int tRange = 1 << (tBitSize - 1);


    for(I&& a : boost::irange(-tRange, tRange))
    {
        S b = SignedInt<I,S,tBitStart,tBitSize>::Encode(a);

        I c = SignedInt<int,S,tBitStart,tBitSize>::Decode(b);
        EXPECT_EQ(a, c);
    }
}



namespace TestNamespace{

#include "enumtools.h"

    ENUM_TOOLS

    ENUMS(TestEnum,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Eleven
    )


    TEST(enumtools, to_string)
    {
        for(auto&& val : get_range<TestEnum>())
        {
            cout << to_string(val) << endl;
        }
        using te = TestEnum;
        EXPECT_EQ(te::One, TestEnum::One);
        EXPECT_EQ("one", to_string(TestEnum::One));
        // EXPECT_EQ("1",to_string(1));
    }

    ENUMS_2( ETest_2
        ,Periodic , 1
,BackgroundScan , 2
,Spontaneous , 3
,Initialized , 4
,Request , 5
,Activation , 6
,ActivationCon , 7
,Deactivation , 8

    )

TEST(Enums2, Declaration)
{
    for(auto&& i : get_range<ETest_2>())
    {
        cout << (int)i << " = " << to_string(i) << endl;
    }
}


    #define VALUE(a,b,c) a,b,c

ENUMS_3(ETest3Enum,
    VALUE(M_SP_NA_1,1, "Single-point information without time tag"),
    /**
     * 	 * 2 - Single-point information with time tag
     * 	 	 */
    VALUE(M_SP_TA_1,2, "Single-point information with time tag"),
    /**
     * 	 * 3 - Double-point information without time tag
     * 	 	 */
    VALUE(M_DP_NA_1,3, "Double-point information without time tag"),
    /**
     * 	 * 4 - Double-point information with time tag
     * 	 	 */
    VALUE(M_DP_TA_1,4, "Double-point information with time tag")

);

TEST(Enums3, Declaration)
{
    for(auto&& i : get_range<ETest3Enum>())
    {
        cout << (int)i << " = " << to_string(i) << endl;
    }
}

}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
