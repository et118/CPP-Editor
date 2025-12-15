#include <cmath>
#include <iostream>
#include <bits/this_thread_sleep.h>

#include "EdgeDimensions.h"
#include "LineBorderRenderer.h"
#include "RecursiveWindow.h"
#include "TestWindow.h"
#include "Window.h"
int main() {

    TestWindow window{};
    TestWindow window2{};
    TestWindow window3{};
    window2.setMaxTotalWidth(20);
    window2.setMinTotalWidth(10);
    RecursiveWindow recurse{};

    recurse.addWindow(&window);
    recurse.addWindow(&window2);
    recurse.addWindow(&window3);
    recurse.tick();
    float counter = 0;
    float counter2 = 0;
    while (true) {
        std::cout << "\033[2J";

        recurse.setTotalWidth(6 + static_cast<int>(std::round(65.0 * ((std::sin((counter * 3.14159265358979323846) / 180.0) + 1) / 2))));
        recurse.setTotalHeight(2 + static_cast<int>(std::round(40.0 * ((std::sin((counter2 * 3.14159265358979323846) / 180.0) + 1) / 2))));
        recurse.tick();
        Content content = recurse.render();
        for (size_t i = 0; i < content.getNumLines(); i++) {
            std::cout << content.getLine(i) << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        counter+=2;
        counter2 += 3;
        if (counter >= 360) counter = 0;
        if (counter2 >= 360) counter2 = 0;
    }

    return 0;
}
