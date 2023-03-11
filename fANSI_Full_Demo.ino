#include <Arduino.h>
#include <fANSI.h>
using namespace fANSI;

void testAttrs();
void testCursorAndErasing();
void test4bfgbg();
void test6bfgbg();
void test24bfgbg();
void test6bGrayfgbg();
void testBorder();
void testAnsi();

void setup() {
    Serial.begin(9600);
    testAnsi();
}

void loop() {
    // put your main code here, to run repeatedly:

}

/////////////////////////////////////////////////////////////////////////
// helper functions
void showTestTitle(char const * const title) {
    resetAll();
    clearEOL();
    stream.write(title, strlen(title));
    stream.write('\n');
}

#define    boldTest    boldAttr " Bold             Rendition" RESETALL "\n"
#define   faintTest   faintAttr " Faint            Rendition" RESETALL "\n"
#define   underTest   underAttr " Underline        Rendition" RESETALL "\n"
#define neitherTest neitherAttr " Neither          Rendition" RESETALL "\n"
#define reverseTest reverseAttr " Reverse Video    Rendition" RESETALL "\n"
#define  strikeTest  strikeAttr " Crossed Out      Rendition" RESETALL "\n"

void testAttrs() {
    static char const * const tests[] = 
        { boldTest, faintTest, underTest, faintTest, neitherTest, reverseTest, strikeTest };

    for (auto test : tests) {
        stream.write(test, strlen(test));
    }
    stream.write('\n');
}

void testCursorAndErasing() {
    resetAll();
    cursOn();
    cls();
    cursPos(0, 0);
    stream.println("0,0 test panels and live data updates");
    delay(1000);
}

void test4bfgbg() {
    showTestTitle("test 4-bit foreground and backgrounds");

    for (int j=0; j < 16; ++j) {
        for (int k=0; k < 16; ++k) {
            fg4b(k);
            bg4b(j);
            stream.write(' ');
            stream.write(digits[k]);
            stream.write(digits[j]);
            stream.write(' ');
        }
        stream.print(RESETALL);
        clearEOL();
        stream.print("\n");
    }
    stream.println(RESETALL);
    stream.print("\r\n");
}

void test6bfgbg() {
    showTestTitle("test 6-bit foregrounds and backgrounds");

    for (int r=0; r < 6; r++) {
        for (int g=0; g < 6; g++) {
            for (int b=0; b < 6; b++) {
                fg6b(r, g, b);
                bg6b(g, b, r);
                stream.write(' ');
                stream.write(digits[r]);
                stream.write(digits[g]);
                stream.write(digits[b]);
                stream.write(' ');
            }
            for (int b=0; b < 6; b++) {
                fg6b(g, b, r);
                bg6b(b, r, g);
                stream.write(' ');
                stream.write(digits[g]);
                stream.write(digits[b]);
                stream.write(digits[r]);
                stream.write(' ');
            }
            for (int b=0; b < 6; b++) {
                fg6b(b, r, g);
                bg6b(r, g, b);
                stream.write(' ');
                stream.write(digits[b]);
                stream.write(digits[r]);
                stream.write(digits[g]);
                stream.write(' ');
            }
            stream.print(RESETALL);
            clearEOL();
            stream.print("\n");
        }
    }
    stream.println(RESETALL);
    stream.print("\r\n");
}

void test24bfgbg() {
    showTestTitle("test 24-bit RGB foregrounds and backgrounds");
    
    for (int i=0; i < 255; i += 48) {
        for (int j=0; j < 255; j+= 48) {
            for (int k=0; k < 255; k += 48) {
                char buff[128] = "";
                fg24b(i, j, k);
                bg24b(j, k, i);
                sprintf(buff, "%02X%02X%02X", i, k, j);
                stream.print(buff);
            }
            for (int k=0; k < 255; k += 32) {
                char buff[128] = "";
                fg24b(j, k, i);
                bg24b(k, i, j);
                sprintf(buff, "%02X%02X%02X", i, k, j);
                stream.print(buff);
            }
            for (int k=0; k < 255; k += 32) {
                char buff[128] = "";
                fg24b(k, i, j);
                bg24b(i, j, k);
                sprintf(buff, "%02X%02X%02X", i, k, j);
                stream.print(buff);
            }
            stream.print(RESETALL);
            clearEOL();
            stream.print("\n");
        }
    }
    stream.println(RESETALL);
    stream.print("\r\n");
}

void test6bGrayfgbg() {
    showTestTitle("test 24 shades of Gray foregrounds and backgrounds");

    for (int j=0; j < 23; ++j) {
        for (int k=0; k < 23; ++k) {
            char buff[128] = "";
            fgGray6b(k);
            bgGray6b(j);
            sprintf(buff, "%02X%02X", k, j);
            stream.print(buff);
        }
        stream.print(RESETALL);
        clearEOL();
        stream.print("\n");
    }
    stream.println(RESETALL);
    stream.print("\n");
}

void testBorder() {
    static int const left = 10, top = 8, width = 40, height = 5;
    border(left, top, width, height, Black + Bright, Magenta + Bright, White, Black);
    char const msg[] = " ==  Voltmeter  == ";

    fg4b(Magenta + Bright);
    bg4b(Yellow + Bright);
    printAt(left + 1 + width/2 - (sizeof(msg)/2), top, msg);

    int value = 50;
    int seconds = 10;
    uint32_t start = millis();
    fg4b(White + Bright);
    bg4b(Black);
    cursOff();
    //randomSeed(analogRead(A2) + analogRead(A3));
    while (millis() < start + seconds * 1000) {
        printAt(left + width/2, top + 2, "%2d", value);
        value += random(3) - 1;  // produces: -1, 0, +1
        delay(50);
    }
    cursOn();

    cursPos(0, top + height);
    stream.write('\n');
}

void testAnsi() {
    resetAll();
    cursOn();
    resetAll();
    testCursorAndErasing();
    delay(1000);

    cursOff();

    testBorder();
    delay(1000);

    // Standard and high-intensity colors
    test4bfgbg();

    // 216 colors
    test6bfgbg();

    // 24 shades of gray
    test6bGrayfgbg();

    // 16M colors
    test24bfgbg();

    stream.println(RESETALL);

    stream.write('\n');

    testAttrs();

    cursOn();

    resetAll();
    stream.write('\n');
}

