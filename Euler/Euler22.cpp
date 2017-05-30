#include "Euler22.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <vector>
#include <array>
#include <string>
#include <cstdio>
#include <tchar.h>
#include <Windows.h>

int nameScores() {
	FILE *fp;
	if (fopen_s(&fp, "names.txt", "r") != 0)
		return 0;
	std::array<char, 10 * 1024> buf;
	std::string s;
	while (const auto count = fread_s(buf.data(), 10 * 1024, sizeof(char), 10 * 1024, fp)) {
		s.append(buf.data(), count);
	}
	fclose(fp);
	std::vector<std::string> names;
	std::array<char, 31> name; //Put a name in here before
	auto i = 0U;
	for (const auto c : s) {
		if (c == '"')
			continue;
		if (c == ',') {
			name[i] = '\000';
			names.emplace_back(name.data());
			i = 0;
			continue;
		}
		name[i++] = c;
	}
	// Last one doesn't have a comma
	name[i] = '\000';
	names.emplace_back(name.data());

	std::sort(std::begin(names), std::end(names));
	auto sum = 0UL;
	for (auto pos = 0; pos < names.size();pos++) {
		// This will vectorise if done as a c-loop
		auto name_sum = 0U;
		const auto& current_name = names[pos];
		for (int j = 0; j < current_name.size(); j++) {
			name_sum += current_name[j] - 64;
		}
		sum += (pos+1) * name_sum;
	}
	return sum;

#if 0
   boost::iostreams::stream_buffer<boost::iostreams::mapped_file_source> file("names.txt");
   std::istream in(&file);
   std::istream_iterator<std::string> iter(in);
   boost::char_separator<char> sep(",");
   boost::tokenizer<boost::char_separator<char>> tokeniser(*iter,sep);
  int sum = 0;
   std::vector<std::string> names;
   boost::push_back(names,make_iterator_range(tokeniser.begin(),tokeniser.end()) | boost::adaptors::transformed([](std::string str){
      boost::replace_all(str,"\"","");
      return str;
   }));
   boost::sort(names);
 

   auto rng = boost::adaptors::index(names,1);
   auto it = boost::begin(rng);
   auto end = boost::end(rng);
   for(; it != end; ++it){
      int total = 0;
      const int length = (*it).size();
      for(char c : (*it)) {
         total += c - 64;
      }
      sum += total * it.index();
   }
   return sum;
#endif 

}