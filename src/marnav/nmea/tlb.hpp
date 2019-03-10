#ifndef MARNAV_NMEA_TLB_HPP
#define MARNAV_NMEA_TLB_HPP

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief TLB - Target Label
/// Common target labels for tracked targets. This sentence is used to specify labels for tracked
/// targets to a device that provides tracked target data (e.g. via the TTM – Tracked target
/// message). This will allow all devices displaying tracked target data to use a common set of
/// labels (e.g. targets reported by two radars and displayed on an ECDIS).
/// @code
///        1   2    3   4    5    6
///        |   |    |   |    |    |
/// $--TLB,x.x,c--c,x.x,c--c,...x,c--c*hh<CR><LF>
/// @endcode
// Field number:
/// 1. Target number 'a' reported by this device.
/// 2. Label assigned to target 'a' (2)
/// 3. Additional label pairs (1)
/// (1) This sentence allows several target number/label pairs to be sent in a single message, the maximum sentence
///     length limits the number of labels allowed in a message.
/// (2) Null fields indicate that no common label is specified, not that a null label should be used.
class tlb: public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::TLB;
	constexpr static const char *TAG = "TLB";
	using label = std::pair<int, std::string>;
	using labels = std::vector<label>;

	tlb();
	tlb(const tlb &) = default;
	tlb &operator=(const tlb &) = default;
	tlb(tlb &&) = default;
	tlb &operator=(tlb &&) = default;
	labels get_labels() const;

protected:
	tlb(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	labels labels_;

public:
	labels get_labels()
	{ return labels_; };
	bool add_label(const label &label);
};
}
}


#endif //MARNAV_TLB_HPP
