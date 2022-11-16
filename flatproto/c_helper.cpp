#include <stdlib.h>

#include <limits>

#include "c_helper.h"
template<typename T>
T GetRandomNumber() {
    return random() % std::numeric_limits<T>::max();
}


std::string ToLower(const std::string& str) {
    std::string ans = str;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] >= 'A' && ans[i] <= 'Z') {
            ans[i] = ans[i] - 'A' + 'a';
        }
    }
    return ans;
}