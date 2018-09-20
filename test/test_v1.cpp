//John Stanco 9.18.18


#include <iostream>
#include <string>

#define ASSERT_TEST(condition, result)\
assertImpl(condition, #condition, __FILE__, __LINE__, result)



bool isZero( int val ) {
  return val == 0;
}


struct test_result {
  bool passed;
  unsigned long line;
  std::string file;
  std::string code;
};


void Test( bool eval, const char* file, unsigned long line, test_result& result ) {

  result.passed = eval;
  if( !result.passed ) {
    result.line = line;
    result.file = file;
  }

}


void assertImpl(  bool eval,
                  const char* code,
                  const char* file,
                  unsigned long line,
                  test_result& result ) {
  result.passed = eval;
  result.line = line;
  result.file = file;
  result.code = code;
}


int main() {
  long const max_test = 100;
  test_result results[max_test];
  Test( !isZero( 0 ), __FILE__, __LINE__, results[0] );

  for( int i = 1; i < max_test; ++i ) {
    Test( !isZero( i ), __FILE__, __LINE__, results[i] );
  }

  for( size_t i = 0; i < max_test; ++i ) {
    if( !results[i].passed ) {
      std::cout << "Test "
                << results[i].code << " failed in file "
                << results[i].file << " on line "
                << results[i].line << std::endl;
    }
  }
}
