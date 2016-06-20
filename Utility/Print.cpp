//
//  Print.cpp
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/14.
//
//

#include "Print.hpp"

std::ostream& operator<<(std::ostream& os, libspiral::Index index) {
    os << "(" << index.x << "," << index.y << ")";
    return os;
}