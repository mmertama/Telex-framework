#include <gempyre.h>
#include <gempyre_utils.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <functional>
#include <set>
#include <filesystem>
#include "apitests_resource.h"
#include <cassert>

#include <gtest/gtest.h>


using namespace std::chrono_literals;



std::string headlessParams() {
    switch(GempyreUtils::currentOS()) {
    case GempyreUtils::OS::WinOs: return  "--headless --disable-gpu --remote-debugging-port=9222";
    default:return "--headless --disable-gpu";
    }
}

std::string defaultChrome() {
    switch(GempyreUtils::currentOS()) {
    case GempyreUtils::OS::MacOs: return R"(/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome)";
    case GempyreUtils::OS::WinOs: return  R"("C:\Program Files (86)\Google\Chrome\Application\chrome.exe")";
    case GempyreUtils::OS::LinuxOs: return  R"(chromium-browser)";  //R"(google-chrome)";
    default: return "";
    }
}
/*
class ApiTest : testing::Test {
    protected:
    void SetUp() override {
    }
    Gempyre::Ui m_ui;
};

#define CONSTRUCT_UI Gempyre::Ui ui({{"/test.html", Unittestshtml}}, "test.html", browser);
*/
/*
class Waiter {
    Waiter() {}
};
*/

#define TEST_FAIL (assert(false))


TEST(UiTests, openPage_with_page_browser) {
    const auto htmlPage = TEST_HTML;
    ASSERT_TRUE(std::filesystem::exists(htmlPage));
    const auto browser = defaultChrome();
    Gempyre::Ui ui(htmlPage, defaultChrome(), "", 50000);
    ui.onOpen([&ui]() { ui.exit();});
    ui.onError([](const auto& element, const auto& info){
        std::cerr << element << " err:" << info; TEST_FAIL;});
    const auto raii_ex = GempyreUtils::waitExpire(4s, []() {TEST_FAIL;});
    ui.run();
}


TEST(UiTests, openPage_with_page) {
    const auto htmlPage = TEST_HTML;
    ASSERT_TRUE(std::filesystem::exists(htmlPage));
    Gempyre::Ui ui(htmlPage);
    ui.onOpen([&ui]() { ui.exit();});
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    const auto raii_ex = GempyreUtils::waitExpire(4s, []() {TEST_FAIL;});
    ui.run();
}


TEST(UiTests, openPage_with_browser) {
    const auto browser = defaultChrome();
    Gempyre::Ui ui({{"/foobar.html", Apitestshtml}}, "foobar.html", browser, "", 50000);
    ui.onOpen([&ui]() { ui.exit();});
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    const auto raii_ex = GempyreUtils::waitExpire(4s, []() {TEST_FAIL;});
    ui.run();
}

TEST(UiTests, openPage_defaults) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.onOpen([&ui]() { ui.exit();});
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    const auto raii_ex = GempyreUtils::waitExpire(4s, []() {TEST_FAIL;});
    ui.run();
}

TEST(UiTests, exit_on_time) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.startTimer(1000ms, true, [&ui, &ok]()  {
       ui.exit();
       ok = true;
    });
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, close) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui](){
       ok = true;
       ui.close();
    });
    ui.startTimer(2s, true, [&ui]()  {
       ui.exit();
    });
    ui.run();
    EXPECT_TRUE(ok);
}


TEST(UiTests, onExit) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(2s, true, [&ui]() {
       ui.close();
    });
    bool ok = false;
    ui.onExit([&ok, &ui](){
        ok = true;
        ui.exit();
    });
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, onReload) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(1000ms, true, [&ui]()  {
       ui.eval("window.location.reload(false);");
    });
    ui.startTimer(3000ms, true, [&ui]()  {
       ui.exit();
    });
    bool ok = false;
    ui.onReload([&ok, &ui](){
       ui.exit();
       ok = true;
    });
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, onOpen){
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui](){
      ok = true;
      ui.exit();
    });
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, run) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui](){
        ui.startTimer(1000ms, true, [&ui, &ok]()  {
           ui.exit();
           ok = true;
        });
    });
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, setLogging) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(3s, true, [&ui]()  {
       ui.exit();
    });
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    ui.setLogging(true); //how to test? TODO get log from UI
    ui.run();
}


TEST(UiTests, eval) {
        Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
        ui.eval("document.write('<h3 id=\\\"foo\\\">Bar</h3>')");
        bool ok = false;
        ui.onOpen([&ok, &ui]() {
            Gempyre::Element el(ui, "foo");
            const auto html = el.html();
            ASSERT_TRUE(html);
            ok = html.value() == "Bar";
            ui.exit();
        });
        ui.run();
        EXPECT_TRUE(ok);
}

TEST(UiTests, debug) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(1000ms, true, [&ui]()  {
       ui.exit();
    });
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    ui.debug("Test - Debug");
    ui.run();
}

TEST(Apitests, alert) {
 /*
  * Requires user interaction, skip
  *
  * Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(1000ms, true, [&ui]()  {
       ui.exit();
    });
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    ui.alert("Test - Alert");
    ui.run();*/
}


TEST(UiTests, open) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(1000ms, true, [&ui]()  {
       ui.exit();
    });
    ui.onError([](const auto& element, const auto& info){std::cerr << element << " err:" << info; TEST_FAIL;});
    ui.open("http://www.google.com");
    ui.run();
}

TEST(UiTests, startTimer) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(1000ms, true, [&ui](Gempyre::Ui::TimerId id)  {
       (void)id;
       ui.exit();
    });
    ui.run();
}

TEST(UiTests, startTimerNoId) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.startTimer(1000ms, true, [&ui]()  {
       ui.exit();
    });
    ui.run();
}

TEST(UiTests, stopTimer) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = true;
    auto id = ui.startTimer(1000ms, true, [&ui, &ok]()  {
       ok = false;
       ui.exit();
    });
    ui.startTimer(3000ms, true, [&ui]() {
          ui.exit();
       });
    ui.stopTimer(id);
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, root) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    EXPECT_EQ(ui.root().id(), ""); //root has no id
}

TEST(UiTests, addressOf) {
    const auto htmlPage = TEST_HTML;
    ASSERT_TRUE(std::filesystem::exists(htmlPage));
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.onOpen([&ui, htmlPage](){
        EXPECT_TRUE(ui.addressOf(htmlPage).length() > 0); //TODO better test would be write this as html and open it
        ui.exit();
    });
}

TEST(UiTests, byClass) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.onOpen([&ui]() {
        const auto classes = ui.byClass("test-class");
        ASSERT_TRUE(classes);
        EXPECT_EQ(classes->size(), 4); //4 test-classes
        ui.exit();
    });
    ui.run();
}

TEST(UiTests, byName) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui](){
        const auto names = ui.byName("test-name");
        ok = names.has_value() && names->size() == 5; //5 test-classes
        ui.exit();
    });
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, ping) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui](){
        const auto ping = ui.ping();
        ok = ping.has_value() && ping->first.count() > 0 && ping->second.count() > 0 && ping->first.count() < 10000 && ping->second.count() < 10000;
        ui.exit();
    });
    ui.run();
    EXPECT_TRUE(ok);
}

TEST(UiTests, resource) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    const auto r = ui.resource("/apitests.html");
    ASSERT_TRUE(r);
    const std::string html = GempyreUtils::join(*r);
    const auto p1 = html.find("html");
    const auto p2 = html.find("html");
    ASSERT_EQ(p1, p2);
}

TEST(UiTests, addFile) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    const std::string test = "The quick brown fox jumps over the lazy dog";
    const auto tempFile = GempyreUtils::writeToTemp(test);
    const auto ok = ui.addFile("test_data", tempFile);
    ASSERT_TRUE(ok);
    GempyreUtils::removeFile(tempFile);
    const auto r = ui.resource("test_data");
    const std::string text = GempyreUtils::join(*r);
    const auto p1 = text.find("quick");
    EXPECT_NE(p1, std::string::npos);
    EXPECT_EQ(text.length(), test.length());
}

TEST(UiTests, devicePixelRatio) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    ui.onOpen([&ui](){
        const auto dr = ui.devicePixelRatio();
        ASSERT_TRUE(dr);
        EXPECT_TRUE(*dr > 0);
    });
    ui.run();
}

TEST(Elementtests, ElementCreate) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    Gempyre::Element parent(ui, "test-1");
    Gempyre::Element(ui, "boing", "div", parent);
    bool ok = false;
    ui.onOpen([&ok, &ui, &parent]() {
        const auto cop = parent.children();
        ok = cop.has_value() && std::find_if(cop->begin(), cop->end(), [](const auto el ){return el.id() == "boing";}) != cop->end();
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, ElementCreateLater) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element parent(ui, "test-1");
        Gempyre::Element(ui, "boing", "div", parent);
        const auto cop = parent.children();
        ok = cop.has_value() && std::find_if(cop->begin(), cop->end(), [](const auto el ){return el.id() == "boing";}) != cop->end();
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, idTest) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    Gempyre::Element foo(ui, "test-1");
    ASSERT_EQ(foo.id(), "test-1");
}


TEST(Elementtests, subscribe) {
    Gempyre::setDebug();
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    Gempyre::Element el(ui, "test-1");
    bool is_open = false;
    ui.onOpen([&is_open]() {
        is_open = true;
    });
    el.subscribe("test_event", [&](const Gempyre::Event& eel) {
        ok = eel.element.id() == el.id();
        ASSERT_TRUE(ok);
        ASSERT_TRUE(is_open);
        ui.exit();
    });
    ui.startTimer(2s, true, [&]()  {
          el.setAttribute("style", "color:green");
       });
    ui.startTimer(3s, true, [&]()  {
          ui.exit();
          ASSERT_TRUE(is_open);
       });
    ui.run();
    ASSERT_TRUE(is_open);
    ASSERT_TRUE(ok);
}

TEST(Elementtests, setHTML) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    Gempyre::Element el(ui, "test-1");
    el.setHTML("Test-dyn");
    bool ok = false;
    ui.onOpen([&ok, &ui, &el]() {
        const auto html = el.html();
        ok = html.has_value() && html.value() == "Test-dyn";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, setAttribute) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    Gempyre::Element el(ui, "test-1");
    el.setAttribute("value", "Test-attr-dyn");
    bool ok = false;
    ui.onOpen([&ok, &ui, &el]() {
        const auto attrs = el.attributes();
        ok = attrs.has_value()
                && attrs->find("value") != attrs->end()
                && attrs.value().find("value")->second == "Test-attr-dyn";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, attributes) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "test-1");
        const auto attrs = el.attributes();
        ok = attrs.has_value()
                && attrs->find("value") != attrs->end()
                && attrs->find("value")->second == "Test-attr";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, children) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "test-1");
        const auto chlds = el.children();
        ok = chlds.has_value()
                && chlds->size() > 2
                && (*chlds)[2].id() == "test-child-2";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, values) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "checkbox-1");
        const auto values = el.values();
        ok = values.has_value()
                && values->find("checked") != values->end()
                && values->find("checked")->second == "true";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, html) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "test-1");
        const auto html = el.html();
        ok = html.has_value() && html.value().find("Test-1") != std::string::npos;
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, remove) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "test-1");
        const auto chlds = el.children();
        ok = chlds.has_value()
                && chlds->size() > 3
                && (*chlds)[3].id() == "test-child-3";
        ASSERT_TRUE(ok);
        Gempyre::Element c(ui,"test-child-3");
        c.remove();
        const auto cop = el.children();
        ok = cop.has_value() && std::find_if(cop->begin(), cop->end(), [](const auto el ){return el.id() == "test-child-3";}) == cop->end();
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, removeAttribute) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "hidden");
        auto attrs0 = el.attributes();
        ASSERT_NE(attrs0->find("hidden"), attrs0->end());
        el.removeAttribute("hidden");
        const auto attrs = el.attributes();
        ok = attrs->find("hidden") == attrs->end();
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, removeStyle) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "styled");
        const auto style0 = el.styles({"color"}).value();
        if(style0.find("color") == style0.end() || style0.at("color") != "rgb(255, 0, 0)") {
            const auto color0 = style0.at("color");
            ui.exit();
            return;
        }
        el.removeStyle("color");
        const auto style = el.styles({"color"});
        const auto color = style->at("color");
        ok = color != "red";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, setStyle) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "test-1");
        el.setStyle("color", "blue");
        const auto style = el.styles({"color"});
        ok = style->at("color") == "rgb(0, 0, 255)";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, styles) {
    Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
    bool ok = false;
    ui.onOpen([&ok, &ui]() {
        Gempyre::Element el(ui, "styled");
        const auto style0 = el.styles({"color", "font-size"}).value();
        const auto it = style0.find("color");
        ok = it != style0.end() && style0.at("color") == "rgb(255, 0, 0)" && style0.at("font-size") == "32px";
        ui.exit();
    });
    ui.run();
    ASSERT_TRUE(ok);
}

TEST(Elementtests, type) {
      Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
      ui.onOpen([&ui]() {
          Gempyre::Element el(ui, "test-1");
          const auto t = el.type();
          ASSERT_TRUE(t);
          ASSERT_EQ(*t, "dev");
      });
      ui.run();
}

TEST(Elementtests, rect) {
      Gempyre::Ui ui(Apitests_resourceh, "apitests.html");
      ui.onOpen([&ui]() {
          Gempyre::Element el(ui, "test-1");
          const auto r = el.rect();
          ASSERT_TRUE(r);
          EXPECT_TRUE(r->width > 0 && r->height > 0);
      });
      ui.run();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

