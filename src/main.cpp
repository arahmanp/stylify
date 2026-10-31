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
void throwError(const std::string &msg, const std::string &hint = "") {
    std::cerr << BOLD << FG_RED << "error: " << RESET << msg << '\n';

    if(!hint.empty()) {
        std::cerr << BOLD << FG_CYAN << "  hint: " << RESET << hint << '\n';
    }

    exit(1);
}

// Warning
void throwWarning(const std::string &msg, const std::string &hint = "") {
    std::cerr << BOLD << FG_YELLOW << "warning: " << RESET << msg << '\n';

    if(!hint.empty()) {
        std::cerr << BOLD << FG_CYAN << "  hint: " << RESET << hint << '\n';
    }
}

// Show version
void showVersion() {
    std::cout << BOLD << APP_NAME << RESET << ' ' << APP_VERSION << '\n'
              << "A small CLI tool for styling terminal text.\n"
              << "Author: " << APP_AUTHOR << '\n';
    exit(0);
}

// Show help
void showHelp() {
    std::cout << BOLD << APP_NAME << RESET << ' ' << APP_VERSION << '\n'
              << "A small CLI tool for styling terminal text.\n\n"

              << BOLD << "USAGE" << RESET << '\n'
              << "  stylify [OPTIONS] <string>\n"
              << "  stylify [OPTIONS] --string <string>\n\n"

              << BOLD << "OPTIONS" << RESET << '\n'
              << "  --fg-color <color>   Set the text (foreground) color\n"
              << "  --bg-color <color>   Set the background color\n"
              << "  --bold               Make the text bold\n"
              << "  --italic             Make the text italic\n"
              << "  --underline          Underline the text\n"
              << "  --string <string>    Provide the text to style\n"
              << "  --version            Show version information\n"
              << "  --help               Show this help message\n\n"

              << BOLD << "COLORS" << RESET << '\n'
              << "  " << FG_BLACK   << "black"   << RESET << ", "
              << FG_RED     << "red"     << RESET << ", "
              << FG_GREEN   << "green"   << RESET << ", "
              << FG_YELLOW  << "yellow"  << RESET << ", "
              << FG_BLUE    << "blue"    << RESET << ", "
              << FG_MAGENTA << "magenta" << RESET << ", "
              << FG_CYAN    << "cyan"    << RESET << ", "
              << FG_WHITE   << "white"   << RESET << "\n\n"

              << BOLD << "EXAMPLES" << RESET << '\n'
              << "  stylify \"Hello\" --fg-color red --bold\n"
              << "  stylify --string \"Hello World\" --bg-color blue --underline\n"
              << "  stylify \"Hi\" --fg-color white --bg-color magenta --italic\n";

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
        throwError("The foreground color was set more than once.",
                   "Use --fg-color only once.");
    }

    if(color == "black")        conf.fgColor = FG_BLACK;
    else if(color == "red")     conf.fgColor = FG_RED;
    else if(color == "green")   conf.fgColor = FG_GREEN;
    else if(color == "yellow")  conf.fgColor = FG_YELLOW;
    else if(color == "blue")    conf.fgColor = FG_BLUE;
    else if(color == "magenta") conf.fgColor = FG_MAGENTA;
    else if(color == "cyan")    conf.fgColor = FG_CYAN;
    else if(color == "white")   conf.fgColor = FG_WHITE;
    else throwError("Unknown color `" + color + "`.",
                    "Available colors: black, red, green, yellow, blue, magenta, cyan, white.");
}

void setBackgroundColor(Config &conf, const std::string &color) {
    if(conf.bgColor != BG_DEFAULT) {
        throwError("The background color was set more than once.",
                   "Use --bg-color only once.");
    }

    if(color == "black")        conf.bgColor = BG_BLACK;
    else if(color == "red")     conf.bgColor = BG_RED;
    else if(color == "green")   conf.bgColor = BG_GREEN;
    else if(color == "yellow")  conf.bgColor = BG_YELLOW;
    else if(color == "blue")    conf.bgColor = BG_BLUE;
    else if(color == "magenta") conf.bgColor = BG_MAGENTA;
    else if(color == "cyan")    conf.bgColor = BG_CYAN;
    else if(color == "white")   conf.bgColor = BG_WHITE;
    else throwError("Unknown color `" + color + "`.",
                    "Available colors: black, red, green, yellow, blue, magenta, cyan, white.");
}

void setBold(Config &conf) {
    if(conf.bold) {
        throwError("The --bold flag was given more than once.",
                   "Remove the duplicate --bold.");
    }

    conf.bold = true;
}

void setItalic(Config &conf) {
    if(conf.italic) {
        throwError("The --italic flag was given more than once.",
                   "Remove the duplicate --italic.");
    }

    conf.italic = true;
}

void setUnderline(Config &conf) {
    if(conf.underline) {
        throwError("The --underline flag was given more than once.",
                   "Remove the duplicate --underline.");
    }

    conf.underline = true;
}

void setString(Config &conf, const std::string &s) {
    if(conf.isSetStr) {
        throwError("More than one string was provided.",
                   "Wrap your text in quotes, e.g. stylify \"hello world\" --bold");
    }

    conf.str = s;
    conf.isSetStr = true;
}

std::string generate(const Config &conf) {
    if(!conf.isSetStr) {
        throwError("No string was provided.",
                   "Pass text directly or use --string \"text\".");
    }

    if(conf.str.empty()) {
        throwWarning("The provided string is empty, so there is nothing to style.",
                     "Provide a non-empty string, e.g. stylify \"hello\" --bold");
    }

    if(conf.fgColor == FG_DEFAULT && conf.bgColor == BG_DEFAULT &&
       !conf.bold && !conf.italic && !conf.underline) {
        throwWarning("No style options were given, so the text is printed unchanged.",
                     "Try adding --fg-color, --bold, etc.");
    }

    std::string result = conf.fgColor + conf.bgColor;

    if(conf.bold) result += BOLD;
    if(conf.italic) result += ITALIC;
    if(conf.underline) result += UNDERLINE;

    result += conf.str + RESET;

    return result;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        throwError("No arguments provided.",
                   "Try: stylify \"hello\" --fg-color red --bold");
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
                } else if(arg == "--help") {
                    showHelp();
                } else {
                    throwError("Unknown flag `" + arg + "`!");
                }
            } else {
                setString(strConfig, arg);
            }
        }

        std::cout << generate(strConfig) << '\n';
    }
}