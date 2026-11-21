/*
    Idle-Breakout-Editor
    Copyright (C) 2026 Jorttle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <iostream>
#include "IdleSave.hpp"

int main(int argc, char* argv[]) {
    std::cout << "Idle Breakout Editor Copyright (C) 2026 Jorttle\n"
    "This program comes with ABSOLUTELY NO WARRANTY\n"
    "This is free software, and you are welcome to redistribute it under certain conditions. See https://www.gnu.org/licenses for more information.\n"
    "***************************************" << std::endl;
    /* Deal with arguments passed into main */
    if(argc > 2) {
        std::cout << "That's too many arguments!" << std::endl;
        return 1;
    }
    bool ignoreRestrictions = false;
    if(argc > 1 && (std::string(argv[1]) == "-i" || std::string(argv[1]) == "--ignore-restrictions")) { ignoreRestrictions = true; }
    else if (argc > 1) {
        std::cout << "I don't understand those arguments. Continuing as if no arguments were passed..." << std::endl;
    }
    IdleSave Save = IdleSave("Temporary Export String", ignoreRestrictions);

    return 0;
}
