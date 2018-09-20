//John Stanco 9.18.18


#include <iostream>
#include <string>
#include "/usr/local/include/unittest.h"


bool alwaysTrue() { return true; }
bool isZero( int val ) { return val == 0; }

int main() {

  ASSERT_FALSE( alwaysTrue() );
  ASSERT_FALSE( isZero( 0 ) );

  return 0;
}
