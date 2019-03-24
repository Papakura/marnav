#include "query.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/nmea.hpp>

namespace marnav
{
namespace nmea
{

constexpr static sentence_id ID = sentence_id::NONE;
constexpr static const char * TAG = "**Q";
query::query(talker t, talker receiver):sentence(sentence_id::NONE,to_string(receiver)+"Q",t)
{
	receiver_ = receiver;
}
query::query(talker talker, std::string& tag, fields::const_iterator first, fields::const_iterator /*last*/)
: sentence(ID, tag, talker)
{
	receiver_ = nmea::make_talker(tag.substr(0,2));
	sentence_ = nmea::tag_to_id(*first);
}

void query::append_data_to(std::string & s) const
{
	append(s, nmea::to_string( sentence_));
}

}
}
