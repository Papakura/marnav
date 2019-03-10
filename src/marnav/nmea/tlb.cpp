#include "tlb.hpp"
#include <marnav/nmea/io.hpp>
namespace marnav
{
namespace nmea
{
constexpr sentence_id tlb::ID;

constexpr const char *tlb::TAG;

label make_label(int number, const char *label)
{
	return std::make_pair(number,label);
}

label make_label(int number, std::string &label)
{
	return std::make_pair(number,label);
}

std::string to_string(label value)
{
	return to_string(value.first) + "," + value.second;
}
tlb::tlb() : sentence(ID, TAG, talker_id::radar), size_{0}
{

}

tlb::tlb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk),size_{0}
{
	while(first != last)
	{
		int number;
		std::string name;
		read(*first,number);
		read(*(first+1), name);
		labels_.push_back(make_label(number, name));
		first += 2;
	}
}

void tlb::append_data_to(std::string &s) const
{
	for (auto const &t : labels_)
		append(s, to_string(t));

}

bool tlb::add_label(const label &label)
{
	if(size_ == 72)
	{
		return false;
	}
	labels_.push_back(label);
	size_ += label.second.length() + to_string(label.first).length();
	return true;
}
}
}