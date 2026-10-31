#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#define APP_NAME "Stylify"
#define APP_VERSION "0.1.0"
#define APP_AUTHOR "Andhika Rahman"

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

// Show version
void showVersion() {
    std::cout << APP_NAME << ' ' << APP_VERSION << '\n';
    std::cout << "by " << APP_AUTHOR << '\n';
    exit(0);
}

struct Config {
    std::string str;
    bool isSetStr = false;

    std::string fgColor = FG_DEFAULT;
    std::string bgColor = BG_DEFAULT;

    bool bold       = false;
    bool italic     = false;
    bool underline  = false;
};

void setForegroundColor(Config &conf, const std::string &color) {
    if(conf.fgColor != FG_DEFAULT) {
        throwError("You are setting the foreground color more than once!");
    }

    if(color == "black")        conf.fgColor = FG_BLACK;
    else if(color == "red")     conf.fgColor = FG_RED;
    else if(color == "green")   conf.fgColor = FG_GREEN;
    else if(color == "yellow")  conf.fgColor = FG_YELLOW;
    else if(color == "blue")    conf.fgColor = FG_BLUE;
    else if(color == "magenta") conf.fgColor = FG_MAGENTA;
    else if(color == "cyan")    conf.fgColor = FG_CYAN;
    else if(color == "white")   conf.fgColor = FG_WHITE;
    else throwError("Unknown color `" + color + "`!");
}

void setBackgroundColor(Config &conf, const std::string &color) {
    if(conf.bgColor != BG_DEFAULT) {
        throwError("You are setting the foreground color more than once!");
    }

    if(color == "black")        conf.bgColor = BG_BLACK;
    else if(color == "red")     conf.bgColor = BG_RED;
    else if(color == "green")   conf.bgColor = BG_GREEN;
    else if(color == "yellow")  conf.bgColor = BG_YELLOW;
    else if(color == "blue")    conf.bgColor = BG_BLUE;
    else if(color == "magenta") conf.bgColor = BG_MAGENTA;
    else if(color == "cyan")    conf.bgColor = BG_CYAN;
    else if(color == "white")   conf.bgColor = BG_WHITE;
    else throwError("Unknown color `" + color + "`!");
}

void setBold(Config &conf) {
    if(conf.bold) {
        throwError("You have included the --bold flag more than once!");
    }

    conf.bold = true;
}

void setItalic(Config &conf) {
    if(conf.italic) {
        throwError("You have included the --italic flag more than once!");
    }

    conf.italic = true;
}

void setUnderline(Config &conf) {
    if(conf.underline) {
        throwError("You have included the --underline flag more than once!");
    }

    conf.underline = true;
}

void setString(Config &conf, const std::string &s) {
    if(conf.isSetStr) {
        throwError("You may only enter one string!");
    }

    conf.str = s;
    conf.isSetStr = true;
}

std::string generate(const Config &conf) {
    std::string result = conf.fgColor + conf.bgColor;

    if(conf.bold) result += BOLD;
    if(conf.italic) result += ITALIC;
    if(conf.underline) result += UNDERLINE;

    result += conf.str + RESET;

    return result;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        throwError("You must provide at least one argument!");
    } else {
        Config strConfig;

        for(size_t i = 1; i < argc; i++) {
            std::string arg = argv[i];

            if(arg.size() >= 1 && arg[0] == '-') {
                if(arg == "--fg-color") {
                    if(i < argc - 1) setForegroundColor(strConfig, argv[++i]);
                    else throwError("Missing color!");
                } else if(arg == "--bg-color") {
                    if(i < argc - 1) setBackgroundColor(strConfig, argv[++i]);
                    else throwError("Missing color!");
                } else if(arg == "--bold") {
                    setBold(strConfig);
                } else if(arg == "--italic") {
                    setItalic(strConfig);
                } else if(arg == "--underline") {
                    setUnderline(strConfig);
                } else if(arg == "--string") {
                    if(i < argc - 1) setString(strConfig, argv[++i]);
                    else throwError("Missing string!");
                } else if(arg == "--version") {
                    showVersion();
                } else {
                    throwError("Unknown flag `" + arg + "`!");
                }
            } else {
                setString(strConfig, arg);
            }
        }

        std::string result = generate(strConfig);

        std::cout << result << '\n';
    }
}