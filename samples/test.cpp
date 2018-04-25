#include <algorithm>
#include <map>
#include <string>
#include <vector>

int main(int argc, char** argv) {
#if HAS_FEATURE
    for (int i = 0; i < 10; i++) {
        switch (i) {
            case 0:
            {
                if (true) {

                }
            }
        }
    }
#endif

    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(),
                   [](auto c) { return std::toupper(c); });

    struct S {
      char c[3];
      float f;
      short s;
      int i;
    };
}
