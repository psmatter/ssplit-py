#ifndef LIB_SSPLIT_H
#define LIB_SSPLIT_H

#include<memory>
#include<string>
//#include<sstream>
#include <list>
#include <vector>
#include <map>
#include<unordered_map>
#include <string_view>


typedef std::map<std::string, int, std::less<>> prefix_map_t;
typedef std::list<std::string> strlist_t;


#define PREFIX_PRE	"/usr/local/share/ssplit/nonbreaking_prefix."

// SentenceSplitter from ugerman@github.com modified for use as library
// includes regex.h and typedefs.h
// namespaces removed to ease handling. Compile with --std=C++17 
// The splitter takes a string_view as argument and returns one sentence
// per call until the data is processed. 
//
// The input has to be preprocessed to insert not less than a paragaph to
// the splitter.
//
// SentenceStream is depreceated. 
//
// RingBuffer offers a buffer structure to support a basic io handling as
// for a reader and a worker thread. 
// 
// 
// 
// psmatter@github.com, 2023

using namespace std;

class SentenceSplitter{
public:

  SentenceSplitter();

  // Return the prefix class of a prefix.
  // 0: not a prefix
  // 1: prefix
  // 2: prefix only in front of numbers

  int get_prefix_class(string_view piece) const;

  // auxiliary function to declare a prefix from a line in the prefix file
  void declarePrefix(string_view buffer);

  SentenceSplitter(std::stringstream &istream);


  //SentenceSplitter(char *);
  int load(const char * );
  void loadFromSerialized(const string_view buffer);

  // Find next sentence boundary, return StringPiece for next sentence,
  // advance rest to reflect the rest of the text.
  string_view 	operator()(string_view* rest) const;

  uint32_t	sentences(); 		//returns the number of sentences
  void		sentences(uint32_t); 	//sets the number, apparently 0

private:
  prefix_map_t prefix_type_;
  uint32_t     sentences_; // sentence counter
}; // end of class SentenceSplitter

namespace SentenceStreamer{
class SentenceStream{
private:
  char const* cursor_;
  char const* const stop_;
  string_view paragraph_;
  SentenceSplitter const& splitter_;
  std::string error_message_; // holds error message if UTF8 validation fails
  int status_; // holds prce2 error code
public:
  // @param text text to be split into sentences
  // @param splitter the actual sentence splitter
  // @param verify utf8?
  SentenceStream(string_view text,
                 SentenceSplitter const& splitter, bool verify_utf8=true);

  // @param data start of data
  // @param datasize size of data
  // @param splitter the actual sentence splitter
  // @param verify utf8?
  SentenceStream(char const* data, size_t datasize,
                 SentenceSplitter const& splitter,
                 bool verify_utf8=true);

  //  bool OK() const; // return true if UTF8 verification succeeded
  int status() const; // return status (pcre2 error code)
  std::string const& error_message() const;
  bool operator>>(std::string& snt);
  // bool operator>>(pcrecpp::StringPiece& snt);
  bool operator>>(string_view& snt);

};

// Auxiliary function to print a chunk of text as a single line,
// replacing line breaks by blanks. This is faster than doing a
// global replacement in a string first.
std::stringstream&
single_line(std::stringstream& out, // destination stream
            string_view span, // text span to be printed in a single line
            string_view end = "", // stuff to put at end of line
            bool validate_utf = false); // do we need to validate UTF8?

// Auxiliary function to stiore a chunk of text as a single line,
// replacing line breaks by blanks.
std::string&
single_line(std::string& snt, // destination stream
            string_view span, // text span to be printed in a single line
            string_view end = "", // stuff to put at end of line
            bool validate_utf = false); // do we need to validate UTF8?

}

#endif
