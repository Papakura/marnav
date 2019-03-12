#include "txt.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id txt::ID;
constexpr const char *txt::TAG;

txt::txt() : sentence(ID, TAG, talker_id::none)
{
}

txt::txt(talker talk, fields::const_iterator first, fields::const_iterator last) : sentence(ID, TAG, talk)
{
if (std::distance(first, last) != 4)
	throw std::invalid_argument{"invalid number of fields in txt"};
    read(*(first), total_sentences_);
    read(*(first+1), sentence_);
    read(*(first+2), message_id_);
    read(*(first+3), message_);
}

void txt::append_data_to(std::string & s) const
{
    append(s, to_string(total_sentences_));
    append(s, to_string(sentence_));
    append(s, to_string(message_id_));
    append(s, message_);

}

std::vector<std::unique_ptr<nmea::sentence>> make_txts(talker_id talker, int id, std::string &message)
{
	std::vector<std::unique_ptr<nmea::sentence>> sentences;
	int num = message.length()/70;
	int remainder = message.length()% 70;
	for(int sequence = 1; sequence <=num; sequence++)
	{
		auto s = utils::make_unique<nmea::txt>();
		s->set_talker(talker);
		s->set_id(id);
		s->set_sentence(sequence, num + (remainder > 0?1:0));
		auto text = message.substr(sequence-1,70);
		s->set_message(text);
		sentences.push_back(std::move(s));
	}
	if(remainder > 0)
	{
		auto s = utils::make_unique<nmea::txt>();
		s->set_talker(talker);
		s->set_id(id);
		s->set_sentence(num + 1, num + 1);
		auto text = message.substr(num,remainder);
		s->set_message(text);
		sentences.push_back(std::move(s));
	}

	return sentences;
}
}
}

