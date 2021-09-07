#ifndef INC_01_LEVENSTEIN_HPP
#define INC_01_LEVENSTEIN_HPP

#include <string>
using namespace std;

size_t matr_method(const string &str1, const string &str2);

size_t recur_method(const string &str1, const size_t len1, const string &str2, const size_t len2);

size_t rec_cache(const string &str1, const size_t len1, const string &str2, const size_t len2, size_t **matr);

size_t rec_cache_method(const string &str1, const size_t len1, const string &str2, const size_t len2);

size_t Domerau(const string &str1, const size_t len1, const string &str2, const size_t len2, size_t **matr);

size_t Domerau_method(const string &str1, const size_t len1, const string &str2, const size_t len2);

#endif
