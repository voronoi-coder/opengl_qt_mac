//
// Created by zhaojunhe on 2018/12/7.
//

#include <libs/shelf-pack/shelf-pack.hpp>
#include <iostream>

using namespace mapbox;

int main() {
    ShelfPack sprite(64, 64);

    for (int i = 0; i < 5; ++i) {
        Bin *bin = sprite.packOne(-1, 10, 10);
        if (bin) {
            std::cout << *bin << std::endl;
        } else {
            std::cout << "out of space" << std::endl;
        }
    }

    sprite.clear();
    sprite.resize(128, 128);
}

