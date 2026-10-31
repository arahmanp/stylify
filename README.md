# Stylify

A small command-line tool for styling terminal text with colors and text effects using ANSI escape codes.

## Features

- Set the foreground (text) color
- Set the background color
- Bold, italic, and underline effects
- Clear error messages with hints
- Built-in `--help` and `--version`

## Requirements

- A C++20 compatible compiler (GCC 10+, Clang 11+, or MSVC 2019 16.11+)
- [CMake](https://cmake.org/) 3.20 or newer
- Git
- A terminal that supports ANSI escape codes (most Linux/macOS terminals, Windows Terminal, and Windows 10+ consoles)

## Build and install

### 1. Clone the repository

```bash
git clone https://github.com/arahmanp/stylify
cd stylify
```

### 2. Generate the build files

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

### 3. Build

```bash
cmake --build build --config Release
```

The binary will be created in the `build` folder (`build/stylify` on Linux/macOS, or `build\Release\stylify.exe` on Windows with Visual Studio).

### 4. Copy the binary to your PATH

**Linux/macOS**

```bash
sudo cp build/stylify /usr/local/bin/
```

**Windows (PowerShell)**

Copy `stylify.exe` to a folder that is already in your `PATH`, or create one and add it to `PATH`:

```powershell
mkdir $env:USERPROFILE\bin
copy build\Release\stylify.exe $env:USERPROFILE\bin\
```

Then add `%USERPROFILE%\bin` to your `PATH` environment variable and restart your terminal.

After that, verify the installation:

```bash
stylify --version
```

## Usage

```bash
stylify [OPTIONS] <text>
stylify [OPTIONS] --text <text>
```

The text can be passed directly as an argument or with `--text`. Only one text is allowed, so wrap text containing spaces in quotes.

## Options

| Option | Description |
| --- | --- |
| `--fg-color <color>` | Set the text (foreground) color |
| `--bg-color <color>` | Set the background color |
| `--bold` | Make the text bold |
| `--italic` | Make the text italic |
| `--underline` | Underline the text |
| `--text <text>` | Provide the text to style |
| `--version` | Show version information |
| `--help` | Show the help message |

### Available colors

`black`, `red`, `green`, `yellow`, `blue`, `magenta`, `cyan`, `white`

## Examples

```bash
# Red, bold text
stylify "Hello" --fg-color red --bold

# Underlined text on a blue background
stylify --text "Hello World" --bg-color blue --underline

# Combine everything
stylify "Hi" --fg-color white --bg-color magenta --italic --underline
```

Because Stylify prints the styled text followed by a newline, it can be used inside shell scripts:

```bash
echo "Status: $(stylify OK --fg-color green --bold)"
```

## Errors and warnings

Errors and warnings are printed to `stderr`, with a hint when one is available. An error stops the program with exit code `1`.

**Errors**

- No arguments provided
- Unknown flag or unknown color
- A flag that needs a value is missing it (`--fg-color`, `--bg-color`, `--text`)
- A color, effect flag, or text is given more than once
- No text provided

**Warnings**

- The provided text is empty
- No style options were given, so the text is printed unchanged

Example:

```
$ stylify "hi" --fg-color pink
error: Unknown color `pink`.
  hint: Available colors: black, red, green, yellow, blue, magenta, cyan, white.
```

## Notes

- A text that starts with `--` is treated as a flag. To style such text, use `--text`, for example `stylify --text "--5 degrees"`.
- Colors are displayed according to your terminal theme. For example, `black` text may be hard to read on a dark background.

## Version

Stylify 0.1.0

## Author

Andhika Rahman