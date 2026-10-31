#include <cstdlib>
#include <iostream>
#include <string>

#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"

#define FG_BLACK     "\033[30m"
#define FG_RED       "\033[31m"
#define FG_GREEN     "\033[32m"
#define FG_YELLOW    "\033[33m"
#define FG_BLUE      "\033[34m"
#define FG_MAGENTA   "\033[35m"
#define FG_CYAN      "\033[36m"
#define FG_WHITE     "\033[37m"
#define FG_DEFAULT   "\033[39m"

#define BG_BLACK     "\033[40m"
#define BG_RED       "\033[41m"
#define BG_GREEN     "\033[42m"
#define BG_YELLOW    "\033[43m"
#define BG_BLUE      "\033[44m"
#define BG_MAGENTA   "\033[45m"
#define BG_CYAN      "\033[46m"
#define BG_WHITE     "\033[47m"
#define BG_DEFAULT   "\033[49m"

#define RESET "\033[0m"

class StyledString {
private:
    std::string str;

    std::string fgColor = FG_DEFAULT;
    std::string bgColor = BG_DEFAULT;

    bool bold       = false;
    bool italic     = false;
    bool underline  = false;

public:
    StyledString() : str("") {}
    StyledString(const std::string &s) : str(s) {}

    StyledString& setForegroundColor(const std::string &color) {
        if(color == "black")        fgColor = FG_BLACK;
        else if(color == "red")     fgColor = FG_RED;
        else if(color == "green")   fgColor = FG_GREEN;
        else if(color == "yellow")  fgColor = FG_YELLOW;
        else if(color == "blue")    fgColor = FG_BLUE;
        else if(color == "magenta") fgColor = FG_MAGENTA;
        else if(color == "cyan")    fgColor = FG_CYAN;
        else if(color == "white")   fgColor = FG_WHITE;
        else if(color == "default") fgColor = FG_DEFAULT;
        else {
            std::cerr << BOLD << FG_RED << "error:" << RESET
                      << " Unknown color `" << color << "`!\n";
            exit(1);
        }

        return *this;
    }

    StyledString& setBackgroundColor(const std::string &color) {
        if(color == "black")        bgColor = BG_BLACK;
        else if(color == "red")     bgColor = BG_RED;
        else if(color == "green")   bgColor = BG_GREEN;
        else if(color == "yellow")  bgColor = BG_YELLOW;
        else if(color == "blue")    bgColor = BG_BLUE;
        else if(color == "magenta") bgColor = BG_MAGENTA;
        else if(color == "cyan")    bgColor = BG_CYAN;
        else if(color == "white")   bgColor = BG_WHITE;
        else if(color == "default") bgColor = BG_DEFAULT;
        else {
            std::cerr << BOLD << FG_RED << "error:" << RESET
                      << " Unknown color `" << color << "`!\n";
            exit(1);
        }

        return *this;
    }

    StyledString& setBold(bool value) {
        bold = value;

        return *this;
    }

    StyledString& setItalic(bool value) {
        italic = value;

        return *this;
    }

    StyledString& setUnderline(bool value) {
        underline = value;

        return *this;
    }

    StyledString& setString(const std::string &s) {
        str = s;

        return *this;
    }

    StyledString& resetStyle() {
        fgColor = FG_DEFAULT;
        bgColor = BG_DEFAULT;

        bold = false;
        italic = false;
        underline = false;

        return *this;
    }

    std::string build() const {
        std::string result = fgColor + bgColor;

        if(bold)      result += BOLD;
        if(italic)    result += ITALIC;
        if(underline) result += UNDERLINE;

        result += str + RESET;

        return result;
    }
};

int main() {
    StyledString s;

    s.setString("Hello, world!");
    s.setBold(true);
    s.setItalic(true);

    std::string s1 = s.build();

    s.resetStyle();
    s.setString("Andhika Rahman");
    s.setForegroundColor("maenta");
    s.setUnderline(true);

    std::string s2 = s.build();

    std::cout << s1 << '\n' << s2 << '\n';
}