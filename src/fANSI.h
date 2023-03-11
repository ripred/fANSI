/**
 * fANSI.h
 * 
 */
#ifndef FANSI_INCL
#define FANSI_INCL

namespace fANSI {

    Stream & stream { Serial };

    enum ground_t : bool { Fore = false, Back = true };
    enum   bits_t : uint8_t { Four=4, Six=6, Eight=8 };

    struct bit4_t {
        uint8_t f : Four,
                b : Four;
    };

    struct bit6_t {
        uint8_t r : Six,
                g : Six,
                b : Six,
           unused : Six;
    };
    
    struct bit8_t {
        uint8_t r : Eight,
                g : Eight,
                b : Eight;
    };
    
    enum { Black=0, Red, Green, Yellow, Blue, Magenta, Cyan, White, Bright };
    enum { BEL=0x07, BS=0x08, HT=0x09, LF=0x0A, FF=0x0C, CR=0x0D, ESC=0x1B };

    static char str[256] = "";
    static char const digits[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D', 'E','F' };

    // format the string in the global buffer 'str' using the 
    // supplied format string and optional parameters
    int format(char const * const fmt, ...) {
        int length = -1;
        va_list argList;
        va_start(argList, fmt);
        length = vsnprintf(str, sizeof(str), fmt, argList);
        va_end( argList );
        return length;
    }
    
    //////////////////////////////////////////////////////////
    // CSI Ansi code prefix:
    #define CSI "\x1b["
    void csi() {
        stream.write(CSI, sizeof(CSI));
    }

    //////////////////////////////////////////////////////////
    // Resets all colors and attributes to normal
    #define RESETALL CSI "0m"
    void resetAll() {
        stream.write(RESETALL, sizeof(RESETALL));
    }

    //////////////////////////////////////////////////////////
    // switch to alternate screen buffer
    #define ALTSCRN CSI "?1047h"
    #define SAVECURS    CSI "s"
    #define RESTORECURS CSI "u"
    void altScreen() {
        stream.write(SAVECURS, sizeof(SAVECURS));
        stream.write(ALTSCRN, sizeof(ALTSCRN));
    }

    //////////////////////////////////////////////////////////
    // switch to standard screen buffer
    #define STDSCRN CSI "?1047l"
    void stdScreen() {
        stream.write(STDSCRN, sizeof(STDSCRN));
        stream.write(RESTORECURS, sizeof(RESTORECURS));
    }

    //////////////////////////////////////////////////////////
    // Non-color attributes

    #define    boldAttr CSI "1m"    // Bold
    #define   faintAttr CSI "2m"    // Faint
    #define   underAttr CSI "4m"    // Underline
    #define neitherAttr CSI "22m"   // neither
    #define reverseAttr CSI "7m"    // Reverse Video
    #define  strikeAttr CSI "9m"    // Strike-through

    //////////////////////////////////////////////////////////
    // Cursor and erasing Controls

    //////////////////////////////////////////////////////////
    // Turn the cursor Off:
    #define CURSOFF CSI "?25l"
    void cursOff() {
        stream.write(CURSOFF, sizeof(CURSOFF));
    }

    //////////////////////////////////////////////////////////
    // Turn the cursor On:
    #define CURSON CSI "?25h"
    void cursOn() {
        stream.write(CURSON, sizeof(CURSON));
    }

    void cursEx(int const n, char const cmd) {
        char buff[32] = "";
        sprintf(buff, CSI "%d%c", n, cmd);
        stream.write(buff, strlen(buff));
    }

    //////////////////////////////////////////////////////////
    // Move the cursor Up:
    void cursUp(int n=1) {
        cursEx(n, 'A');
    }

    //////////////////////////////////////////////////////////
    // Move the cursor Down:
    void cursDown(int n=1) {
        cursEx(n, 'B');
    }

    //////////////////////////////////////////////////////////
    // Move the cursor Right:
    void cursRight(int n=1) {
        cursEx(n, 'C');
    }

    //////////////////////////////////////////////////////////
    // Move the cursor Left:
    void cursLeft(int n=1) {
        cursEx(n, 'D');
    }

    //////////////////////////////////////////////////////////
    // Move the cursor to the next line:
    void cursNextLine(int n=1) {
        cursEx(n, 'E');
    }

    //////////////////////////////////////////////////////////
    // Move the previous line:
    void cursPrevLine(int n=1) {
        cursEx(n, 'F');
    }

    //////////////////////////////////////////////////////////
    // Clear the display from cursor to end of the display:
    #define CLEAREOD CSI "J"
    void clearEOD() {
        stream.write(CLEAREOD, sizeof(CLEAREOD));
    }

    //////////////////////////////////////////////////////////
    // Clear the display from cursor to end of the line:
    #define CLEAREOL CSI "K"
    void clearEOL() {
        stream.write(CLEAREOL, sizeof(CLEAREOL));
    }

    //////////////////////////////////////////////////////////
    // Position the cursor to a column and row:
    char *cursPos(int col, int row) {
        format(CSI "%d;%df", row, col);
        stream.write(str, strlen(str));
        return str;
    }

    void cls() {
        cursPos(0, 0);
        clearEOD();
    }

    //////////////////////////////////////////////////////////
    // multipalette
    // 
    // ESC[38;5;⟨n⟩m Select foreground color      where n is a number from the table below
    // ESC[48;5;⟨n⟩m Select background color
    //   0-  7:  standard colors (as in ESC [ 30–37 m)
    //   8- 15:  high intensity colors (as in ESC [ 90–97 m)
    //  16-231:  6 × 6 × 6 cube (216 colors): 16 + 36 × r + 6 × g + b (0 ≤ r, g, b ≤ 5)
    // 232-255:  grayscale from dark to light in 24 steps
    
    void setColor(int const n, bool const back, char const sep) {
        stream.write(0x1b);
        stream.write('[');
        stream.write(back ? '4' : '3');
        stream.write('8');
        stream.write(sep);
        stream.write('5');
        stream.write(sep);
        stream.print(n, DEC);
        stream.write('m');
    }
    
    //////////////////////////////////////////////////////////
    // 4-bit Foreground and Background Colors
    // n = 0 to 15
    void fg4b(int n) {
        setColor(n, Fore, ':');
    }

    void bg4b(int n) {
        setColor(n, Back, ':');
    }

    //////////////////////////////////////////////////////////
    // 6-bit Foreground and Background Colors
    // 0 ≤ r, g, b ≤ 5
    void fg6b(int const r, int const g, int const b) {
        setColor(16 + (36 * r) + (6 * g) + b, Fore, ':');
    }

    void bg6b(int const r, int const g, int const b) {
        setColor(16 + (36 * r) + (6 * g) + b, Back, ':');
    }

    //////////////////////////////////////////////////////////
    // 24-bit Foreground and Background Colors
    // r,g,b = 0 to 255
    char *fg24b(int r, int g, int b) {
//      return CSI "38;2;%d;%d;%dm"r, g, b);
        format(CSI "38;2;%d;%d;%dm", r, g, b);
        stream.print(str);
        return str;
    }
    
    char *bg24b(int r, int g, int b) {
//      return CSI + "48;2;"+r+";"+g+";"+b+"m";
        format(CSI "48;2;%d;%d;%dm", r, g, b);
        stream.print(str);
        return str;
    }

    //////////////////////////////////////////////////////////
    // 7-bit Grayscale Foreground and Background Colors
    // n = 0 to 23
    void fgGray6b(int n) {
        setColor(232 + n, Fore, ':');
    }

    void bgGray6b(int n) {
        setColor(232 + n, Back, ':');
    }

    //////////////////////////////////////////////////////////
    // Merge two color strings into single (foreground or background) color average of the two:
//    char *mergeColors24(char *clr1, char *clr2, bool fore) {
//        String[] parts1 = clr1.split(";");
//        String[] parts2 = clr2.split(";");
//
//        float r1 = Float.valueOf(parts1[2]);
//        float g1 = Float.valueOf(parts1[3]);
//        float b1 = Float.valueOf(parts1[4].substring(0, parts1[4].length() - 1));
//
//        float r2 = Float.valueOf(parts2[2]);
//        float g2 = Float.valueOf(parts2[3]);
//        float b2 = Float.valueOf(parts2[4].substring(0, parts2[4].length() - 1));
//
//        int r = (int)((((r1 / 256.0f) + (r2 / 256.0f)) / 2.0) * 256.0);
//        int g = (int)((((g1 / 256.0f) + (g2 / 256.0f)) / 2.0) * 256.0);
//        int b = (int)((((b1 / 256.0f) + (b2 / 256.0f)) / 2.0) * 256.0);
//
//        return fore ? fg24b(r, g, b) : bg24b(r, g, b);
//    }


    void border(int x, int y, int w, int h, uint8_t bfg, uint8_t bbg, uint8_t nfg, uint8_t nbg) {
        cursOff();
//        fg4b(nfg);
//        bg4b(nbg);
//        cls();
        fg4b(bfg);
        bg4b(bbg);

        cursPos(x, y);
        for (int k=0; k < w; k++) {
            stream.write(' ');
        }

        for (int j=0; j < h; j++) {
            cursPos(x, y + j);
            stream.write(' ');
            cursPos(x + w, y + j);
            stream.write(' ');
        }

        cursPos(x, y + h - 1);
        for (int k=0; k < w; k++) {
            stream.write(' ');
        }
        cursOn();
    }

   
    void printAt(int x, int y, char const * const fmt, ...) {
        char buff[512] = "";
        va_list argList;
        va_start(argList, fmt);
        vsnprintf(buff, sizeof(buff), fmt, argList);
        va_end( argList );
        cursPos(x, y);
        stream.write(buff, strlen(buff));
    }

    struct meter_t {
        int8_t  maxv, minv, curv, lastv, x, y, fg, bg, len, dir;

        meter_t(uint8_t _max, uint8_t _min, uint8_t _cur, uint8_t _x, uint8_t _y, uint8_t _fg, uint8_t _bg) : 
            maxv(_max),
            minv(_min),
            curv(_cur),
            lastv(_cur),
            x(_x),
            y(_y),
            fg(_fg),
            bg(_bg) 
        {
            len = 10;
            dir = 0;    // 0 <, 1 ^, 2 v, 3 >
        }

        
    };

}; // namespace fANSI

#endif // FANSI_INCL
