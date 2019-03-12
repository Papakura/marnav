#include <gtest/gtest.h>
#include <marnav/nmea/txt.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{
	using namespace marnav;

	class Test_nmea_txt : public ::testing::Test
	{
	};

	TEST_F(Test_nmea_txt, contruction)
	{
		EXPECT_NO_THROW(nmea::txt txt);
	}

	TEST_F(Test_nmea_txt, properties)
	{
		nmea_sentence_traits<nmea::txt>();
	}

	TEST_F(Test_nmea_txt, parse)
	{
		auto s = nmea::make_sentence("$GPTXT,01,01,25,DR MODE-ANTENNA FAULT^21*38");
		ASSERT_NE(nullptr, s);

		auto txt = nmea::sentence_cast<nmea::txt>(s);
		ASSERT_NE(nullptr, txt);
	}

	TEST_F(Test_nmea_txt, format)
	{
		std::string text = "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
		auto s = nmea::make_txts(nmea::talker_id::radar,25, text);
		ASSERT_EQ(2, s.size());
		for(auto& sentence : s)
		{
			auto out = nmea::to_string(*sentence.get());
			std::cout << out << std::endl;
		}
	}
}
