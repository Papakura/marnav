#include "tlb.hpp"
#include <marnav/nmea/io.hpp>
namespace marnav
{
namespace nmea
{
constexpr sentence_id tlb::ID;

constexpr const char *tlb::TAG;

std::string to_string(tlb::label value)
{
	return std::string{};
}
tlb::tlb()
	: sentence(ID, TAG, talker_id::radar)
{

}

tlb::tlb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in tfi"};

}

void tlb::append_data_to(std::string &s) const
{
	for (auto const &t : labels_)
		append(s, to_string(t));

}

bool tlb::add_label(const tlb::label &label)
{
	return false;
}

}
}