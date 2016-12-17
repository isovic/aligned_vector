#ifdef ALIGNED_VECTOR_TEST_MAIN_

#define DEBUG_VERBOSE_

#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include "aligned_vector.hpp"

template<class T, size_t A>
std::string print_vec(is::aligned_vector<T, A> &vec) {
  std::stringstream ss;
  for (size_t i=0; i<vec.size(); i++) {
    if (i > 0) { ss << " "; }
    ss << vec[i];
  }
  return ss.str();
}

void aligned_vector_test() {
  ////////////////////////////////////////////////////////////////////////////////////
  // Fill a char array with some chars, and align to 16 byte chunks.
  ////////////////////////////////////////////////////////////////////////////////////
  is::aligned_vector<char, 16> aln_vec1;
  std::cout << "aln_vec1\t" << aln_vec1.verbose() << std::endl;
  for (int32_t i=65; i<97; i++) {
    aln_vec1.push_back((char) i);
    std::cout << "aln_vec1\t" << aln_vec1.verbose() << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Data:" << std::endl << print_vec(aln_vec1) << std::endl;
  std::cout << std::endl;

  ////////////////////////////////////////////////////////////////////////////////////
  // Fill a char array with some chars, and align to 1024 byte chunks.
  // 1024 bytes are used in this example because on normal ranges (1byte - 128bytes)
  // alignment happens much more often by chance.
  ////////////////////////////////////////////////////////////////////////////////////
  is::aligned_vector<char, 1024> aln_vec1_a;
  std::cout << "aln_vec1_a\t" << aln_vec1_a.verbose() << std::endl;
  for (int32_t i=65; i<97; i++) {
    aln_vec1_a.push_back((char) i);
    std::cout << "aln_vec1_a\t" << aln_vec1_a.verbose() << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Data:" << std::endl << print_vec(aln_vec1_a) << std::endl;
  std::cout << std::endl;

  ////////////////////////////////////////////////////////////////////////////////////
  // Allocate memory 10000 times in a row, and check whether it is aligned.
  ////////////////////////////////////////////////////////////////////////////////////
  size_t A = 128;
  is::aligned_vector<int16_t, 128> aln_vec2;
  for (int32_t i=0; i<10000; i++) {
    aln_vec2.resize(i);
    if ((((size_t) aln_vec2.data()) % A) != 0) {
      std::cout << "[i = " << i << "] ASSERTION FAILURE!!" << std::endl;
      assert((((size_t) aln_vec2.data()) % 64) == 0);
    }
  }
  std::cout << "aln_vec2 passed all alignment tests!" << std::endl;
  std::cout << std::endl;

  ////////////////////////////////////////////////////////////////////////////////////
  // Fill a vector and align it to a 128 byte chunk.
  ////////////////////////////////////////////////////////////////////////////////////
  is::aligned_vector<int16_t, 128> aln_vec3;
  for (int32_t i=0; i<10000; i++) {
    aln_vec3.push_back(i);
  }
  std::cout << std::endl;
  // std::cout << "Data:" << std::endl << print_vec(aln_vec3) << std::endl;
  std::cout << "aln_vec3\t" << aln_vec3.verbose() << std::endl;
  for (int32_t i=0; i<10000; i++) {
    if (aln_vec3[i] != i) {
      std::cout << "Assertion failed at: i = " << i << ", aln_vec3[i] = " << aln_vec3[i] << std::endl;
    }
    assert(aln_vec3[i] == i);
  }

  std::cout << std::endl;
  std::cout << "Success!" << std::endl;
}

int main() {
  aligned_vector_test();

  return 0;
}

#endif
