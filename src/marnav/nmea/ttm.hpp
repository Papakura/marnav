#ifndef MARNAV__NMEA__TTM__HPP
#define MARNAV__NMEA__TTM__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief TTM - Tracked Target Message
///
/// @code
///                                         11     13
///        1  2   3   4 5   6   7 8   9   10|    12| 14        15
///        |  |   |   | |   |   | |   |   | |    | | |         |
/// $--TTM,xx,x.x,x.x,a,x.x,x.x,a,x.x,x.x,a,c--c,a,a,hhmmss.ss,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Target Number (00-99)
/// 2.  Target Distance
/// 3.  Bearing from own ship
/// 4.  Bearing reference
///     - T = True
///     - R = Relative
/// 5.  Target Speed
/// 6.  Target Course
/// 7.  Target Course reference
///     - T = True
///     - R = Relative
/// 8.  Distance of closest-point-of-approach
/// 9.  Time until closest-point-of-approach "-" means increasing
/// 10. Speed/ distance units K/N/S
/// 11. Target name
/// 12. Target Status
/// 13. Reference Target
/// 14. Time of data (UTC)
/// 15. Type of acquisition
///         A = Automatic
///         M = manual
//          R = reported
/// @note Field 14 and 15 are not supported right now due to lack of
///       documentation. The sentence just ignores them. The other fields
///       are being processed.
///
class ttm : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::TTM;
	constexpr static const char * TAG = "TTM";

	ttm();
	ttm(const ttm &) = default;
	ttm & operator=(const ttm &) = default;
	ttm(ttm &&) = default;
	ttm & operator=(ttm &&) = default;

protected:
	ttm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<uint32_t> target_number_;
	utils::optional<double> target_distance_;
	utils::optional<double> bearing_from_ownship_;
	utils::optional<reference> bearing_from_ownship_ref_;
	utils::optional<double> target_speed_;
	utils::optional<double> target_course_;
	utils::optional<reference> target_course_ref_;
	utils::optional<double> distance_cpa_; ///< Distance to closest point of approach
	utils::optional<double> tcpa_;
	utils::optional<char> speed_distance_units_;
	utils::optional<std::string> target_name_;
	utils::optional<target_status> target_status_;
	utils::optional<char> reference_target_;
	utils::optional<nmea::time> time_;
	utils::optional<target_acquisition> acquisition_type_;
public:
	decltype(target_number_) get_target_number() const { return target_number_; }
	decltype(target_distance_) get_target_distance() const { return target_distance_; }
	decltype(bearing_from_ownship_) get_bearing_from_ownship() const
	{
		return bearing_from_ownship_;
	}
	decltype(bearing_from_ownship_ref_) get_bearing_from_ownship_ref() const
	{
		return bearing_from_ownship_ref_;
	}
	decltype(target_speed_) get_target_speed() const { return target_speed_; }
	decltype(target_course_) get_target_course() const { return target_course_; }
	decltype(target_course_ref_) get_target_course_ref() const { return target_course_ref_; }
	decltype(distance_cpa_) get_distance_cpa() const { return distance_cpa_; }
	decltype(tcpa_) get_tcpa() const { return tcpa_; }
	decltype(speed_distance_units_) get_speed_distance_units() const
	{ return speed_distance_units_; }
	decltype(target_name_) get_target_name() const { return target_name_; }
	decltype(target_status_) get_target_status() const { return target_status_; }
	decltype(reference_target_) get_reference_target() const { return reference_target_; }
	decltype(time_) get_time() const
	{ return time_; }
	decltype(acquisition_type_) get_acquisition() const
	{ return acquisition_type_; }

	void set_target_number(uint32_t t) noexcept { target_number_ = t; }
	void set_target_distance(double t) noexcept { target_distance_ = t; }
	void set_bearing_from_ownship(double t, reference r) noexcept
	{
		bearing_from_ownship_ = t;
		bearing_from_ownship_ref_ = r;
	}
	void set_target_speed(double t) noexcept { target_speed_ = t; }
	void set_target_course(double t, reference r) noexcept
	{
		target_course_ = t;
		target_course_ref_ = r;
	}
	void set_distance_cpa(double t) noexcept { distance_cpa_ = t; }
	void set_tcpa(double t) noexcept { tcpa_ = t; }
	void set_speed_distance_units(char t) noexcept
	{ speed_distance_units_ = t; }
	void set_target_name(const std::string & t) { target_name_ = t; }
	void set_target_status(target_status t) noexcept
	{ target_status_ = t; }
	void set_reference_target(char t) noexcept { reference_target_ = t; }
	void set_time(const nmea::time &t) noexcept
	{ time_ = t; }
	void set_acquisition(const target_acquisition &t) noexcept
	{ acquisition_type_ = t; }
};
}
}

#endif
