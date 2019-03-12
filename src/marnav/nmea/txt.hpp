#ifndef MARNAV_NMEA_TXT_HPP
#define MARNAV_NMEA_TXT_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

///
/// @brief TXT Text transmission
/// For the transmission of short text messages. Longer text messages may be transmitted by
/// using multiple sentences.
///@code
///        1  2  3  4
///        |  |  |  |
/// $--TXT,xx,xx,xx,c--c*hh<CR><LF>
///@endcode
/// Field number
/// 1) Total number of sentences
/// 2) Sentence number
/// 3) Text identifier
/// 4) Text message

class txt : public sentence
{
    friend class detail::factory;

public:
    constexpr static sentence_id ID = sentence_id::TXT;
    constexpr static const char * TAG = "TXT";

    txt();
    txt(const txt &) = default;
    txt & operator=(const txt &) = default;
    txt(txt &&) = default;
    txt & operator=(txt &&) = default;
protected:
    txt(talker talk, fields::const_iterator first, fields::const_iterator last);
    virtual void append_data_to(std::string &) const override;
private:
    std::string message_;
    int sentence_;
    int total_sentences_;
    int message_id_;
public:
	/*!
	 * set the message text
	 * @param message
	 */
    void set_message(const std::string& message) {message_ = message;}
    /*!
     * set the message identifier
     * @param id
     */
    void set_id(int id) {message_id_ = id;}
    /*!
     * set the sentence sequence number/ total
     * @param number
     * @param total
     */
    void set_sentence(int number, int total){sentence_ = number; total_sentences_ = total;}
	/*!
	 * get the message text
	 * @return The part message contained in this sentence
	 */
    decltype(message_) get_message(){return message_;}
    /*!
     * get the message identifier
     * @return
     */
    decltype(message_id_) get_id(){return message_id_;}
};

/*!
 * create a set of sentence for a single message
 * @param talker the talker for the sentences
 * @param id the message identifier
 * @param message the message text
 * @return a set of sentences containing the message
 */
std::vector<std::unique_ptr<nmea::sentence>> make_txts(talker_id talker, int id, std::string &message);
}
}



#endif //MARNAV_TXT_HPP
