#ifndef MARNAV_NMEA_NAK_HPP
#define MARNAV_NMEA_NAK_HPP

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
/**
 * In general, the NAK sentence is used when a reply to a query sentence cannot be provided,
 * or when a command sentence is not accepted. The NAK sentence reply should be generated
 * within 1 s.
 * Use of NAK should be specified by the equipment standard.
 *
 *        1  2   3    4   5
 *        |  |   |    |   |
 * $--NAK,cc,ccc,c--c,x.x,c--c*hh<CR><LF>
 * 1) Talker identifier from the sentence formatter that caused the NAK generation. This field should not be null.
 * 2) Affected sentence formatter is either:
 *     – the “approved sentence formatter of data” being requested in a query that cannot be processed or
 *       accepted, or
 *     – the sentence formatter of the control or configuration sentence that cannot be processed or accepted.
 *    This field should not be null.
 * 3) The Unique Identifier is used for system level identification of a device, 15 characters maximum. This is the
 *    Unique Identifier for the device producing the NAK sentence, when available.
 * 4) Reason codes:
 *	0 = Query functionality not supported
 *	1 = Sentence formatter not supported
 *	2 = Sentence formatter supported, but not enabled
 *	3 = Sentence formatter supported and enabled, but temporarily unavailable (e.g. data field problem, unit
 *		in initialize state, or in diagnostic state, etc.)
 *	4 = Sentence formatter supported, but query for this sentence formatter is not supported.
 *	5 = Access denied, for sentence formatter requested
 *	6 = Sentence not accepted due to bad checksum
 *	7 = Sentence not accepted due to listener processing issue
 *	8 to 9: reserved for future use
 *	10 = Cannot perform the requested operation.
 *	11 = Cannot fulfil request or command because of a problem with a data field in the sentence.
 *	12 to 48: reserved for future use
 *	49 = other reason as described in data field 5.
 *	Values greater than 50 may be defined by equipment standards.
 *	This field should not be null.
 * 5) Negative acknowledgement’s descriptive text
*/
class nak : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::NAK;
	constexpr static const char * TAG = "NAK";

	nak(talker t, talker id, sentence_id s, reason_code code);
	nak(const nak &) = default;
	nak & operator=(const nak &) = default;
	nak(nak &&) = default;
	nak & operator=(nak &&) = default;

protected:
	nak(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;
private:
	talker talker_;
	sentence_id sentence_;
	std::string identifier_;
	reason_code code_;
	std::string description_;
public:
	decltype(talker_) get_talker() {return talker_;}
	decltype(sentence_) get_formatter() {return sentence_;}
	decltype(identifier_) get_identifier(){return identifier_;}
	decltype(code_) get_code(){return code_;}
	decltype(description_) get_description(){return description_;}
	void set_talker(talker t){ talker_ = t;}
	void set_formatter(sentence_id s){ sentence_ = s;}
	void set_identifier(std::string& id){identifier_ = id;}
	void set_code(reason_code code){code_ = code;}
	void set_description(std::string& description){description_ = description;}
};
}
}


#endif //MARNAV_NMEA_NAK_HPP
