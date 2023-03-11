#include <Arduino.h>
#include <fANSI.h>
using namespace fANSI;
static int const Width  = 80;
static int const Height = 40;

enum { MAX_LABELS = 5 };

static uint32_t makehash(char const * const s) {
    uint8_t const *str = (uint8_t const *) s;
    unsigned long hash = 4787;
    int c;

    while ((c = *str++)) hash = ((hash << 5) + hash) + c;

    return hash;
}

struct hash_t {
    char     name[32] {0};
    uint32_t hash {0};
    int      x{0}, y{0};

    hash_t() : x(0), y(0) {
        hash = makehash(name);
    }

    hash_t(char const * const label, int const X, int const Y) : x(X), y(Y) {
        set_name(label, X, Y);
    }

    void set_name(char const * const label, int const X, int const Y) {
        strncpy(name, label, sizeof(name));
        x = X;
        y = Y;
        hash = makehash(name);
    }

    void update(int32_t value) const {
        char buff[32];
        sprintf(buff, "%d", value);
        buff[sizeof(buff) - 1] = 0;
        printAt(x + strlen(name) + 2, y + 1, buff);
    }

    void update(double value) const {
        char buff[32];
        dtostrf(value, 8, 2, buff);
        buff[sizeof(buff) - 1] = 0;
        printAt(x + strlen(name) + 2, y + 1, buff);
    }

    void update(char *value) const {
        char buff[255];
        strncpy(buff, value, sizeof(buff));
        buff[sizeof(buff) - 1] = 0;
        printAt(x + strlen(name) + 2, y + 1, buff);
    }
};

struct color_theme_t {
    int bfg {Black}, bbg {White+Bright}, fg {White}, bg{ Black};

    color_theme_t() : bfg(Black), bbg(White), fg(White), bg(Black) { }
    color_theme_t(int BFG, int BBG, int FG, int BG) : bfg(BFG), bbg(BBG), fg(FG), bg(BG) { }
};

struct window_t {
    color_theme_t theme;
    char          name[32] {0};
    hash_t        labels[MAX_LABELS];
    int           x {0}, y {0}, w {0}, h{0}, count {0};
    bool          updated {false};
    
    window_t() {

    }

    window_t(char const * const label, int X, int Y, int W, int H) : x(X), y(Y), w(W), h(H), count(0) {
        strncpy(name, label, sizeof(name));
    }

    void set_theme(color_theme_t const &t) {
        theme = t;
    }

    void draw_form() {
        if (updated) return;
        updated = true;

        border(x, y, w, h, theme.bfg, theme.bbg, theme.fg, theme.bg);
        setColor(theme.bfg, Fore, ':');
        setColor(theme.bbg, Back, ':');
        printAt(x + w/2 - strlen(name)/2, y, name);

        setColor(theme.fg, Fore, ':');
        setColor(theme.bg, Back, ':');
        for (int i=0; i < count; ++i) {
            printAt(x + 2, y + 2 + i, labels[i].name);
        }
        cursOff();
    }

    int get_field_index(char const * const label) {
        uint32_t const hash = makehash(label);
        for (int i=0; i < count; ++i) {
            if (hash == labels[i].hash) {
                return i;
            }
        }

        return -1;
    }

    bool add_field(char const * const label) {
        int index = get_field_index(label);
        if (index >= 0) return true;

        if (count >= MAX_LABELS) { return false; }

        uint32_t const hash = makehash(label);

        for (int i=0; i < count; ++i) {
            if (hash == labels[i].hash) {
                return true;
            }
        }

        strncpy(labels[count].name, label, sizeof(labels[count].name));
        labels[count].hash = hash;
        count++;
        
        return true;
    }

    void update(char const * const label, int32_t value) {
        draw_form();
        int j = get_field_index(label);
        if (j < 0) return;

        char buff[32];
        sprintf(buff, "%d", value);
        buff[sizeof(buff) - 1] = 0;
        setColor(theme.fg, Fore, ':');
        setColor(theme.bg, Back, ':');
        printAt(x + strlen(labels[j].name) + 2, y + 2 + j, buff);
        cursOff();
    }

    void update(char const * const label, double value) {
        draw_form();
        int j = get_field_index(label);
        if (j < 0) return;

        char buff[32];
        dtostrf(value, 6, 2, buff);
        buff[sizeof(buff) - 1] = 0;
        setColor(theme.fg, Fore, ':');
        setColor(theme.bg, Back, ':');
        printAt(x + strlen(labels[j].name) + 2, y + 2 + j, buff);
        cursOff();
    }

    void update(char const * const label, char *value) {
        draw_form();
        int j = get_field_index(label);
        if (j < 0) return;

        char buff[255];
        strncpy(buff, value, sizeof(buff));
        buff[sizeof(buff) - 1] = 0;
        setColor(theme.fg, Fore, ':');
        setColor(theme.bg, Back, ':');
        printAt(x + strlen(labels[j].name) + 2, y + 2 + j, buff);
        cursOff();
    }

};

void update_rand_up_down(double &value) {
    value += double((random(3) - 1) * 0.010);
}

window_t pid("PID", 5, 3, 20, 7);
double pGain, iGain, dGain;

window_t meter("meter", 15, 11, 30, 10);
double voltage, current;

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(34));

    color_theme_t  normal( Black, White + Bright, Green + Bright, Black );

    pid.set_theme(normal);
    pid.add_field("P:");
    pid.add_field("I:");
    pid.add_field("D:");
    pGain = 3000.0;
    iGain = 10.0;
    dGain = 60.0;
    
    color_theme_t  sunset( Cyan + Bright, Blue, Yellow + Bright, Black );

    meter.set_theme(sunset);
    meter.add_field("Voltage:");
    meter.add_field("Current:");
    voltage = 2.5;
    current = 0.200;

    cls();
    cursOff();
}

void loop() {
    update_rand_up_down(pGain);
    update_rand_up_down(iGain);
    update_rand_up_down(dGain);

    pid.update("P:", pGain);
    pid.update("I:", iGain);
    pid.update("D:", dGain);

    update_rand_up_down(voltage);
    update_rand_up_down(current);

    meter.update("Voltage:", voltage);
    meter.update("Current:", current);
}
