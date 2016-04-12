#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

std::vector<std::pair<float,float>> coordenates = {{3, 2}, {0, 1}, {0, 2}, {0, 3}, {1, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 2}, {2, 3}, {3, 1}};


float distance (int &a, int &b) {
    std::pair<float, float> coord_a, coord_b;
    coord_a = coordenates[a];
    coord_b = coordenates[b];

    return std::sqrt(std::pow(coord_a.first - coord_b.first, 2) + std::pow (coord_a.second - coord_b.second, 2));
}


int main(int argc, char *argv[])
{
    std::string ip;
    while (std::getline(std::cin, ip)){
        float dist = 0;
        int a, b;
        for(size_t i = 0; i < ip.size()-1; i++) {
            if (ip[i] == '.') {
                a = 10;
            } else {
                a = ip[i] - '0';
            }
            if (ip[i+1] == '.') {
                b = 10;
            } else {
                b = ip[i+1] - '0';
            }
            dist += distance(a, b);
        }
        std::cout << "Distance: " << dist << std::endl;
     }
    return 0;
}




