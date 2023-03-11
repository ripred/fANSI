/**
 * Alternate_Screen.ino
 * 
 */
#include <fANSI.h>

using namespace fANSI;

void setup() {
    Serial.begin(9600);

    altScreen();
    cls();

    printAt(20, 10, "This is the alternate screen.");
    printAt(20, 11, "waiting 10 seconds to switch back,");
    printAt(20, 13, "and then everything on the original screen will be restored..");
    cursOff();
    for (int i=10; i >= 0; --i) {
        printAt(28, 11, "%2d", i);
        delay(1000);
    }
    cursOn();
    cls();
    stdScreen();
    cursDown();

    Serial.println("\r\npress ctrl-c");
}

void loop() {
    // put your main code here, to run repeatedly:
}
