// John Stanco 9.18.18

#include "unittest.h"

#include <iostream>

namespace UnitTest {

  TestFramework::TestFramework() : failures{ FailureList{} }, n_results{ 0 }, n_passed{ 0 }, n_failed{ 0 } {}


  TestFramework::~TestFramework() {
    if( n_results > 0 ) { reportResults(); }
    for( auto failure : failures ) { delete failure; }
  }


  TestFramework& TestFramework::Instance() {
    static TestFramework instance;
    return instance;
  }

  void TestFramework::addFailure( TestFailure *failure ) {
    failures.push_back( failure );
    ++n_failed;
    ++n_results;
  }


  void TestFramework::addSuccess() {
    ++n_passed;
    ++n_results;
  }


  void TestFramework::reportFailures() {
    for( auto failure : failures ) {
      std::cout << "--------------------- TEST FAILED ----------------------\n";
      std::cout << "test: " << failure->name() << "\t| "
                //<< "\nfunction: " << failure->function()
                << " expected " << ( failure->eval()? "FALSE" : "TRUE" )
                << ", returned " << ( failure->eval()? "TRUE" : "FALSE" )
                << "\nfile: " << failure->file()
                << "\nline: " << failure->line()  << "\n";
    }
    std::cout << "--------------------------------------------------------\n\n";
  }


  bool TestFramework::reportOptional() {
    bool loop = true;
    bool print = false;
    char Y_or_N;
    size_t i = 0;
    size_t loopMax = 5;

    while( n_failed > 0 && loop && i++ < loopMax ) {
      std::cout << "Print details? (Y/N)\n";
      std::cin >> Y_or_N;
      if( Y_or_N == 'Y' || Y_or_N == 'y' ) {
        loop = false;
        print = true;
      } else if ( Y_or_N == 'N' || Y_or_N == 'n' ) {
        loop = false;
        print = false;
      }
    }
    return print;
  }


  void TestFramework::reportResults() {
    std::cout << "\n--------------------------------------------------------\n";
    std::cout << "tests:\t" << n_results
              << "\npassed:\t" << n_passed
              << "\nfailed:\t" << n_failed << "\n";

    //if( reportOptional() ) { reportFailures(); }
    reportFailures();
  }

  TestFailure::TestFailure( bool eval, const char* testName, const char* file, size_t line ) :
  _testName{ testName },
  _file{ file },
  _line{ line },
  _eval{ eval } {}


  std::string TestFailure::name() const { return _testName; }


  std::string TestFailure::file() const { return _file; }


  size_t TestFailure::line() const { return _line; }


  bool TestFailure::eval() const { return _eval; }


  void assertTrue( bool eval, const char* code, const char* file, size_t line ) {
    if( !eval ) {
      // deleted in UnitTestFramework destructor
      auto failure = new TestFailure{ eval, code, file, line };
      TestFramework::Instance().addFailure( failure );
    } else {
      TestFramework::Instance().addSuccess();
    }
  }


  void assertFalse( bool eval, const char* code, const char* file, size_t line ) {
    if( eval ) {
      // deleted in UnitTestFramework destructor
      auto failure = new TestFailure{ eval, code, file, line };
      TestFramework::Instance().addFailure( failure );
    } else {
      TestFramework::Instance().addSuccess();
    }
  }
}
