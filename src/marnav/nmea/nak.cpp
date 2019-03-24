#include "nak.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/nmea.hpp>

namespace marnav
{
namespace nmea
{

constexpr sentence_id nak::ID;
constexpr const char *nak::TAG;

nak::nak(talker t, talker id, sentence_id s, reason_code code):sentence(nak::ID,TAG,t)
{
	talker_ 	= id;
	sentence_ 	= s;
	code_ 		= code;
}

nak::nak(talker talk, fields::const_iterator first, fields::const_iterator last)
: sentence(nak::ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in nak"};
	talker_   = make_talker(*(first + 0));
	sentence_ = tag_to_id(*(first + 1));
	read(*(first + 2),identifier_);
	read(*(first + 3),code_);
	read(*(first + 4),description_);

}

void nak::append_data_to(std::string &s) const
{
	append(s, to_string(talker_));
	append(s, to_string( sentence_));
	append(s, identifier_);
	append(s, to_string(code_));
	append(s, description_);
}



}
}
