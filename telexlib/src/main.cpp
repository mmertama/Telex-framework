

#include "telex.h"

int main(int arcs, char** argv) {

    Telex::Ui ui;
    auto button = ui.getElement("startbutton");
    button.setHTML("Click Fibonacci!");
    auto text = ui.getElement("content");
    button.addEvent("onclick", [text](){
        text.setHTML("Hello");
    });
    ui.waitExit();
    return 0;
}

