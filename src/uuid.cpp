#include "../include/uuid.hpp"
#include "../include/random.hpp"
#include <sstream>
#include <iomanip>

namespace pt {
    
    std::string uuid() {
        std::ostringstream oss;
        for (int i = 0; i < 16; i++) {
            if (i == 4 || i == 6 || i == 8 || i == 10) {
                oss << '-';
            }
            int byte = random(0, 255);
            oss << std::hex << std::setw(2) << std::setfill('0') << byte;
        }
        return oss.str();
    }

}