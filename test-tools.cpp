
#include <gtest/gtest.h>
#include "bittools.h"
#include "stringtools.h"
#include "enumtools.h"

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


namespace TestNamespace{

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
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
