#ifndef MARNAV_NMEA_QUERY_HPP
#define MARNAV_NMEA_QUERY_HPP

#include <marnav/nmea/sentence.hpp>
namespace marnav
{
namespace nmea
{
/**
 * The query address field consists of five characters and is used for the purpose of requesting
 * transmission of a specific sentence on a separate bus from an identified talker.
 * The first two characters are the talker identifier of the device requesting data, the next two
 * characters are the talker identifier of the device being addressed and the final character is
 * the query character “Q”.
 */
class query : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::NONE;

	/// constructor
	/// \param talk the sender
	/// \param receiver the receiver
	query(talker talk,talker receiver);

	query(const query &) = default;
	query & operator=(const query &) = default;
	query(query &&) = default;
	query & operator=(query &&) = default;
	query(talker talk, std::string& tag, fields::const_iterator first, fields::const_iterator last);
protected:
	virtual void append_data_to(std::string &) const override;
private:
	talker_id receiver_;
	sentence_id sentence_;
public:

	/// Returns the receiver of the query
	/// \return talker_id
	decltype(receiver_) get_receiver(){return receiver_;};

	/// Returns the sentence being queried
	/// \return  sentence_id
	decltype(sentence_) get_query(){return sentence_;};

	/// Set the sentence to be queried
	/// \param s sentence_id
	void set_query(nmea::sentence_id s) {sentence_ = s;};

	void set_receiver(nmea::talker_id talker){receiver_ = talker;};

};

}
}

#endif //MARNAV_NMEA_QUERY_HPP
