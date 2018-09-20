// John Stanco 9.18.18

#include <string>
#include <list>

#ifndef UNITTEST_H
#define UNITTEST_H

#define ASSERT_TRUE( exp ) UnitTest::assertTrue( exp, #exp, __FILE__, __LINE__ )
#define ASSERT_FALSE( exp) UnitTest::assertFalse( exp, #exp, __FILE__, __LINE__ )

namespace UnitTest {

  class TestFailure;

  class TestFramework {
    TestFramework();

    // Only store failed results
    typedef std::list<TestFailure*> FailureList;
    FailureList failures;
    size_t n_results;
    size_t n_passed;
    size_t n_failed;

    void reportFailures();
  public:
    TestFramework( const TestFramework &rhs ) = delete;
    TestFramework& operator=( const TestFramework &rhs ) = delete;
    ~TestFramework();
    static TestFramework& Instance();
    void addFailure( TestFailure *failure );
    void addSuccess();
    void reportResults();
    bool reportOptional();
  };


  class TestFailure {
    std::string _testName;
    std::string _file;
    size_t _line;
    bool _eval;
  public:
    TestFailure( bool eval, const char* testName, const char* file, size_t line );
    std::string name() const;
    std::string file() const;
    size_t line() const;
    bool eval() const;
  };


  void assertTrue( bool eval, const char* code, const char* file, size_t line );
  void assertFalse( bool eval, const char* code, const char* file, size_t line );
}


#endif /* UNITTEST_H */
