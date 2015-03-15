#include <gtest/gtest.h>
#include <nmea/hdg.hpp>
#include <nmea/nmea.hpp>

namespace
{

class Test_hdg : public ::testing::Test
{
};

TEST_F(Test_hdg, contruction)
{
	nmea::hdg hdg;
}

TEST_F(Test_hdg, size)
{
	EXPECT_EQ(88u, sizeof(nmea::hdg));
}

TEST_F(Test_hdg, parse)
{
	auto s = nmea::make_sentence("$HCHDG,45.8,,,0.6,E*16");
	ASSERT_NE(nullptr, s);

	auto hdg = nmea::sentence_cast<nmea::hdg>(s);
	ASSERT_NE(nullptr, hdg);

	auto heading = hdg->get_heading();
	EXPECT_TRUE(heading.available());
	EXPECT_EQ(45.8, heading.value());
}

TEST_F(Test_hdg, empty_to_string)
{
	nmea::hdg hdg;

	EXPECT_STREQ("$HCHDG,,,,,*6C", nmea::to_string(hdg).c_str());
}

TEST_F(Test_hdg, set_temperature_to_string)
{
	nmea::hdg hdg;
	hdg.set_heading(45.8);

	EXPECT_STREQ("$HCHDG,45.8,,,,*7B", nmea::to_string(hdg).c_str());
}

}

