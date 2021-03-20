#include "gempyre_graphics.h"
#include "gempyre_utils.h"
#include "snowflakes_resource.h"
#include <iostream>
#include <cmath>
#include "koch.h"

using namespace std::chrono_literals;

class Flake {
public:
    Flake(int iterarations) : m_vertices(Koch::koch_points(m_size, iterarations)) {
        std::cout << "snow flake with " << m_vertices.size() << " vertices on " << iterarations << " iterations." << std::endl;
    }
    void draw(Gempyre::FrameComposer& f) const {
        f.save();
        f.translate(m_x - m_size / 2, m_y - m_size / 2);
        f.beginPath();
        auto it = m_vertices.begin();
        f.moveTo(it->x, it->y);
        ++it;
        for(; it != m_vertices.end(); ++it)
            f.lineTo(it->x, it->y);
        f.stroke();
        f.restore();
    }
    void setPos(int x, int y) {
        m_x = x;
        m_y = y;
    }
private:
    int m_x = 0;
    int m_y = 0;
    int m_size = 100;
    const std::vector<Koch::point> m_vertices;
};

int main(int /*argc*/, char** /*argv*/) {
    Gempyre::setDebug();
    Gempyre::Ui ui({{"/snowflakes.html", Snowflakeshtml}}, "snowflakes.html");
    Gempyre::CanvasElement canvas(ui, "canvas");
    Gempyre::Element flakes_count(ui, "flakes_count");

    Gempyre::Element::Rect rect;

    const auto draw_a_flake = [&canvas, &rect](int iterations) {
        Flake f(iterations);
        const auto r = canvas.rect();
        f.setPos(r->width / 2, r->height / 2);
        Gempyre::FrameComposer fc;
        fc.clearRect(rect);
        f.draw(fc);
        canvas.draw(fc);
    };

    flakes_count.subscribe("change", [&draw_a_flake](const Gempyre::Event& ev) {
        const auto v = GempyreUtils::to<int>(ev.properties.at("value"));
        draw_a_flake(v);
    }, {"value"});

    ui.onOpen([&flakes_count, &draw_a_flake, &canvas, &rect]() {
        rect = *canvas.rect();
        const auto v = GempyreUtils::to<int>(flakes_count.values()->at("value"));
        draw_a_flake(v);
    });

    ui.run();
}
