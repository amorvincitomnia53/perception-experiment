#include <chrono>
#include <gtkmm.h>
#include <iostream>
#include <random>

int main()
{


    auto app = Gtk::Application::create();
    Gtk::Window window = Gtk::Window{};
    window.fullscreen();
    Gtk::DrawingArea area;

    window.add(area);
    area.show();
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("github.png", 1920, 1080);
    image->saturate_and_pixelate(image, 0.0, false);
    area.signal_draw().connect([&](const Cairo::RefPtr<Cairo::Context>& cr) {
        Gdk::Cairo::set_source_pixbuf(cr, image, (area.get_width() - image->get_width()) / 2);

        // Draw the image at 110, 90, except for the outermost 10 pixels.
        cr->rectangle(0, 0, area.get_width(), area.get_height());
        cr->fill();

        return true;
    });


    int state = 0;

    auto start = std::chrono::steady_clock::now();


    std::mt19937 rnd(std::random_device{}());

    std::uniform_real_distribution<> l0_dist{0.25, 0.75};
    std::uniform_real_distribution<> dl_dist{-0.5, 0.5};
    std::uniform_real_distribution<> dt_dist{0.0, 5.0};

    double l0;
    double dl;
    double dt;

    int answer = 0;

    int id = 0;
    window.signal_key_press_event().connect([&](GdkEventKey* e) {
        switch (e->keyval) {
        case GDK_KEY_Left:
            answer = 1;
            break;
        case GDK_KEY_Down:
            answer = 2;
            break;
        case GDK_KEY_Right:
            answer = 3;
            break;
        case GDK_KEY_Escape:
            window.close();
            break;
        }
        return false;
    },
        false);
    using sec = std::chrono::duration<double, std::ratio<1>>;
    bool first_time = true;
    Glib::signal_timeout().connect([&] {
        auto now = std::chrono::steady_clock::now();
        using namespace std::chrono_literals;
        switch (state) {
        case 0:
            if (first_time) {
                dt = dt_dist(rnd);
                do {
                    l0 = l0_dist(rnd);
                    dl = dl_dist(rnd);
                    double end = l0 + dl;
                    if (0 <= l0 && l0 <= 1 && 0 <= end && end <= 1) {
                        break;
                    }
                } while (true);
                start = std::chrono::steady_clock::now();
                area.set_opacity(l0);
                first_time = false;
            }
            if (now - start > 3s) {
                state = 1;
                first_time = true;
            }
            break;
        case 1:
            if (first_time) {
                start = std::chrono::steady_clock::now();
                first_time = false;
                area.set_opacity(0);
            }
            if (now - start > 1s * dt) {
                state = 2;
                first_time = true;
            }
            break;
        case 2:
            if (first_time) {
                start = std::chrono::steady_clock::now();
                first_time = false;
                area.set_opacity(l0 + dl);
                answer = 0;
            }
            if (now - start > 3s || answer != 0) {
                state = 3;
                first_time = true;
            }
            break;
        case 3:
            if (first_time) {
                start = std::chrono::steady_clock::now();
                first_time = false;
                area.set_opacity(0);
            }
            //            std::cout<<"!"<<std::chrono::duration_cast<sec>(now-start).count()<<std::endl;
            if (now - start > 2s) {

                constexpr const char* answers[] = {"no-answer", "left", "middle", "right"};
                std::cout << "#id " << id
                          << " #time " << dt
                          << " #start-lightness " << l0
                          << " #end-lightness " << l0 + dl
                          << " #difference " << dl
                          << " #answer " << answer << " (" << answers[answer] << ")"
                          << std::endl;

                id++;
                state = 0;
                first_time = true;
            }
            break;
        }
        return true;
    },
        10);


    auto cursor = Gdk::Cursor::create(Gdk::CursorType::BLANK_CURSOR);
    window.signal_realize().connect([&]() {
        window.get_window()->set_cursor(cursor);
    });
    window.show();
    window.override_background_color(Gdk::RGBA("#000000"));
    app->run(window);
    return 0;
}