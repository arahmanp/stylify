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

// Error
void throwError(const std::string &e) {
    std::cerr << BOLD << FG_RED << "error: " << RESET
              << e << '\n';

    exit(1);
}

// Warning
void throwWarning(const std::string &msg) {
    std::cout << BOLD << FG_YELLOW << "warning: " << RESET
              << msg << '\n';
}

class StyledString {
private:
    std::string str;
    bool isSetStr = false;

    std::string fgColor = FG_DEFAULT;
    std::string bgColor = BG_DEFAULT;

    bool bold       = false;
    bool italic     = false;
    bool underline  = false;

public:
    StyledString& setForegroundColor(const std::string &color) {
        if(fgColor != FG_DEFAULT) {
            throwError("You are setting the foreground color more than once!");
        }

        if(color == "black")        fgColor = FG_BLACK;
        else if(color == "red")     fgColor = FG_RED;
        else if(color == "green")   fgColor = FG_GREEN;
        else if(color == "yellow")  fgColor = FG_YELLOW;
        else if(color == "blue")    fgColor = FG_BLUE;
        else if(color == "magenta") fgColor = FG_MAGENTA;
        else if(color == "cyan")    fgColor = FG_CYAN;
        else if(color == "white")   fgColor = FG_WHITE;
        else throwError("Unknown color `" + color + "`!");

        return *this;
    }

    StyledString& setBackgroundColor(const std::string &color) {
        if(bgColor != BG_DEFAULT) {
            throwError("You are setting the background color more than once!");
        }

        if(color == "black")        bgColor = BG_BLACK;
        else if(color == "red")     bgColor = BG_RED;
        else if(color == "green")   bgColor = BG_GREEN;
        else if(color == "yellow")  bgColor = BG_YELLOW;
        else if(color == "blue")    bgColor = BG_BLUE;
        else if(color == "magenta") bgColor = BG_MAGENTA;
        else if(color == "cyan")    bgColor = BG_CYAN;
        else if(color == "white")   bgColor = BG_WHITE;
        else throwError("Unknown color `" + color + "`!");

        return *this;
    }

    StyledString& setBold() {
        if(bold) {
            throwError("You have included the --bold flag more than once!");
        }

        bold = true;

        return *this;
    }

    StyledString& setItalic() {
        if(italic) {
            throwError("You have included the --italic flag more than once!");
        }

        italic = true;

        return *this;
    }

    StyledString& setUnderline() {
        if(underline) {
            throwError("You have included the --underline flag more than once!");
        }

        underline = true;

        return *this;
    }

    StyledString& setString(const std::string &s) {
        if(isSetStr) {
            throwError("You may only enter one string!");
        }

        str = s;
        isSetStr = true;

        return *this;
    }

    std::string build() const {
        if(!isSetStr) {
            throwError("You did not enter a string!");
        }

        if(str.empty()) {
            throwWarning("You entered an empty string.");
        }

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