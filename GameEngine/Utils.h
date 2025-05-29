//
// Created by vasu4 on 11/4/2024.
//

#ifndef UTILS_H
#define UTILS_H

#include<vector>
#include <sstream>

using namespace std;

static int nextPlayerId = 0;

class Utils {
public:
    static std::vector<std::string> split(const std::string &str, char delimiter) {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            if (!token.empty()) result.emplace_back(token); // Skip empty tokens
        }

        return result;
    }

    static int getNextPlayerId() {
        nextPlayerId++;
        return int(nextPlayerId);
    }
};


#endif //UTILS_H
