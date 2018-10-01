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
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("siryokukennsa.jpg", 1920, 1080);
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

    constexpr double time = 5;


    std::mt19937 rnd(std::random_device{}());

    std::uniform_real_distribution<> l0_dist{0.1, 0.9};
    std::uniform_real_distribution<> dl_dist{-0.25, 0.25};

    double l0;
    double dl;

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
    Glib::signal_timeout().connect([&] {
        auto now = std::chrono::steady_clock::now();
        using namespace std::chrono_literals;
        switch (state) {
        case 0:
            area.set_opacity(0);
            if (now - start > 2s) {
                state = 1;
                answer = 0;
                start = std::chrono::steady_clock::now();
                do {
                    l0 = l0_dist(rnd);
                    dl = dl_dist(rnd);
                    double end = l0 + dl;
                    if (0 <= l0 && l0 <= 1 && 0 <= end && end <= 1) {
                        break;
                    }
                } while (true);
            }
            break;
        case 1:

            if (now - start > 1s * time || answer != 0) {
                constexpr const char* answers[] = {"no-answer", "left", "middle", "right"};
                std::cout << "#id " << id
                          << " #time " << (std::chrono::duration_cast<sec>(now - start).count())
                          << " #start-lightness " << l0
                          << " #answered-lightness " << area.get_opacity()
                          << " #difference " << (area.get_opacity() - l0)
                          << " #answer " << answer << " (" << answers[answer] << ")"
                          << std::endl;
                state = 0;
                answer = 0;
                id++;
                start = std::chrono::steady_clock::now();
            } else {
                area.set_opacity(l0 + dl * std::chrono::duration_cast<sec>(now - start).count() / time);
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