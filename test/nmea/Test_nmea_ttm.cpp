#include <gtest/gtest.h>
#include <marnav/nmea/ttm.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_ttm : public ::testing::Test
{
};

TEST_F(Test_nmea_ttm, contruction)
{
	EXPECT_NO_THROW(nmea::ttm ttm);
}

TEST_F(Test_nmea_ttm, properties)
{
	nmea_sentence_traits<nmea::ttm>();
}

TEST_F(Test_nmea_ttm, parse)
{
	auto s = nmea::make_sentence("$GPTTM,,,,,,,,,,,,,,,*76");
	ASSERT_NE(nullptr, s);

	auto ttm = nmea::sentence_cast<nmea::ttm>(s);
	ASSERT_NE(nullptr, ttm);
}

TEST_F(Test_nmea_ttm, parse_full)
{
	auto s = nmea::make_sentence("$RATTM,11,11.4,13.6,T,7.0,20.0,T,0.0,0.0,N,,Q,,154125.82,A,*17");
	ASSERT_NE(nullptr, s);

	auto ttm = nmea::sentence_cast<nmea::ttm>(s);
	ASSERT_NE(nullptr, ttm);
}

TEST_F(Test_nmea_ttm, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::ttm>(nmea::talker_id::none, {12, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::ttm>(nmea::talker_id::none, {16, "@"}));
}

TEST_F(Test_nmea_ttm, empty_to_string)
{
	nmea::ttm ttm;

	EXPECT_STREQ("$GPTTM,,,,,,,,,,,,,,,*76", nmea::to_string(ttm).c_str());
}

TEST_F(Test_nmea_ttm, full_to_string)
{
	nmea::ttm ttm;
	ttm.set_talker(nmea::talker::radar);
	ttm.set_target_number(11);
	ttm.set_target_distance(11.4);
	ttm.set_bearing_from_ownship(13.6, nmea::reference::TRUE);
	ttm.set_target_speed(7.0);
	ttm.set_target_course(20.0, nmea::reference::TRUE);
	ttm.set_distance_cpa(0.0);
	ttm.set_tcpa(0.0);
	ttm.set_speed_distance_units('N');
	ttm.set_target_name("");
	ttm.set_target_status(nmea::target_status::query);
	ttm.set_reference_target(0x00);
	ttm.set_time(nmea::time::parse("154125.82"));
	ttm.set_acquisition(nmea::target_acquisition::Automatic);
	EXPECT_STREQ("$RATTM,11,11.4,13.6,T,7,20,T,0,0,N,,Q,,154125.82,A*3B", nmea::to_string(ttm).c_str());
}
}
