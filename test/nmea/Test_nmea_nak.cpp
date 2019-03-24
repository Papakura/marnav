#include <gtest/gtest.h>
#include <marnav/nmea/nak.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/talker_id.hpp>
namespace
{

using namespace marnav;

class Test_nmea_nak : public ::testing::Test
{
};

TEST_F(Test_nmea_nak, properties)
{
	nmea_sentence_traits<nmea::nak>();
}

TEST_F(Test_nmea_nak, parse)
{
	auto s = nmea::make_sentence("$GPNAK,RA,TLB,Unique,1,Sentence formatter not supported*4E");
	ASSERT_NE(nullptr, s);

	auto nak = nmea::sentence_cast<nmea::nak>(s);
	ASSERT_NE(nullptr, nak);

	nmea::reason_code code = nak->get_code();
	ASSERT_EQ(nmea::reason_code::sentence_not_supported, code);
	ASSERT_EQ(nmea::talker::radar, nak->get_talker());
	ASSERT_EQ(nmea::sentence_id::TLB, nak->get_formatter());
	ASSERT_EQ("Unique", nak->get_identifier());
	ASSERT_EQ("Sentence formatter not supported", nak->get_description());

}

TEST_F(Test_nmea_nak, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::nak>(nmea::talker_id::none, {4, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::nak>(nmea::talker_id::none, {6, "@"}));
}

TEST_F(Test_nmea_nak, empty_to_string)
{
	nmea::nak nak(	nmea::talker::global_positioning_system,
					nmea::talker_id::radar,
					nmea::sentence_id::TLB,
					nmea::reason_code::sentence_not_supported);

	EXPECT_STREQ("$GPNAK,RA,TLB,,1,*07", nmea::to_string(nak).c_str());
}

}

