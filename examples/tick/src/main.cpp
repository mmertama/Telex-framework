#include <gempyre.h>
#include <gempyre_utils.h>
#include "tick_resource.h"

using namespace std::chrono_literals;

int main(int /*argc*/, char** /*argv*/) {
    Gempyre::setDebug();
    Gempyre::Ui ui({{"/index.html", Tickhtml}}, "index.html");
    Gempyre::Element counter0(ui, "counter0");
    Gempyre::Element counter1(ui, "counter1");
    Gempyre::Element header(ui, "header");
    int count0 = 0;
    int count1 = 0;
    ui.startTimer(10000ms, true, [header]() mutable {
        header.setHTML("time force");
    });
    ui.startTimer(1000ms, false, [&count0, &counter0]() mutable {
        counter0.setHTML(std::to_string(++count0));
    });
    ui.startTimer(100ms, false, [&count1, &counter1, &ui](Gempyre::Ui::TimerId id) mutable {
        counter1.setHTML(std::to_string(++count1));
        if(count1 == 100)
            ui.stopTimer(id);
    });
    const auto [ver, min, maj] = Gempyre::version();
    Gempyre::Element(ui, "ver").setHTML(GempyreUtils::join(std::vector<std::string>{std::to_string(ver), std::to_string(min), std::to_string(maj)}, "."));
    ui.run();
    return 0;
}
