#include <gtest/gtest.h>
#include <marnav/nmea/tlb.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/io.hpp>

namespace
{
using namespace marnav;

class Test_nmea_tlb : public ::testing::Test
{
};

TEST_F(Test_nmea_tlb, contruction)
{
    EXPECT_NO_THROW(nmea::tlb tlb);
}

TEST_F(Test_nmea_tlb, properties)
{
    nmea_sentence_traits<nmea::tlb>();
}

TEST_F(Test_nmea_tlb, parse)
{
    auto s = nmea::make_sentence("$RATLB,1,TARGET1*58");
    ASSERT_NE(nullptr, s);

    auto tlb = nmea::sentence_cast<nmea::tlb>(s);
    ASSERT_NE(nullptr, tlb);
    ASSERT_EQ(1, tlb->get_labels().size());
}

TEST_F(Test_nmea_tlb, format)
{
    nmea::tlb tlb;
    tlb.add_label(nmea::make_label(1,"TARGET1"));
    std::string output = nmea::to_string(tlb);
    ASSERT_EQ("$RATLB,1,TARGET1*58",output);
}

TEST_F(Test_nmea_tlb, format_multiple)
{
    nmea::tlb tlb;
    for(int number = 0; number < 100 ; number++)
    {
        std::string name = "TARGET" + nmea::to_string(number);
        if(tlb.add_label(nmea::make_label(number,name)) != true)
            break;
    }

    std::string output = nmea::to_string(tlb);
    ASSERT_EQ(9,tlb.get_labels().size());
}
}
