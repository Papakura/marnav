#include <gtest/gtest.h>
#include <marnav/nmea/query.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

	using namespace marnav;

	class Test_nmea_query : public ::testing::Test
	{
	};

	TEST_F(Test_nmea_query, parse)
	{
		auto s = nmea::make_sentence("$GPRAQ,TLB*23");
		ASSERT_NE(nullptr, s);
		auto qry = nmea::sentence_cast<nmea::query>(s);
		ASSERT_NE(nullptr, qry);
		ASSERT_EQ(nmea::talker_id::radar,qry->get_receiver());
		ASSERT_EQ(nmea::sentence_id::TLB,qry->get_query());
	}

	TEST_F(Test_nmea_query, format)
	{
		nmea::query qry(nmea::talker::global_positioning_system,nmea::talker_id::radar);
		qry.set_query(nmea::sentence_id::TLB);
		auto s = nmea::to_string(qry);
		ASSERT_EQ("$GPRAQ,TLB*23",s);
	}
}