# ANSI escape codes

## Level 1: Complete Beginner - What Are These Magic Codes?

### The Problem

Have you ever wondered how command-line tools show colored text, progress bars, or interactive menus? Or why some terminal output looks boring and black-and-white while others are vibrant and dynamic? The secret is ANSI escape codes.

### What Exactly Are ANSI Escape Codes?

Think of ANSI escape codes as secret instructions you whisper to your terminal. Instead of just printing normal text, you send special invisible commands that say things like:

- "Make the next text red"
- "Move the cursor up two lines"
- "Clear the screen"
- "Make this text bold and blinking"

These "instructions" are just special character sequences that start with an escape character (think of it as saying "Hey terminal, listen up, special command coming!").

### Your First ANSI Code

Let's start with the absolute simplest example. In most programming languages, this is how you make red text:

```
\033[31mHello World\033[0m

```

Breaking this down:

- `\033[` - "Hey terminal, special command coming!"
- `31m` - "Make text red"
- `Hello World` - Your actual text
- `\033[0m` - "Stop being red, go back to normal"

### Why the Weird Numbers?

The escape character `\033` is just the number 27 written in a special way (octal notation). You might also see it as `\x1B` (hexadecimal) or `\e` in some contexts. They all mean the same thing: "escape character."

## Level 2: Getting Comfortable - Basic Colors and Formatting

### The 8 Basic Colors

Every terminal supports these 8 fundamental colors:

```
30 = Black       31 = Red         32 = Green       33 = Yellow
34 = Blue        35 = Magenta     36 = Cyan        37 = White

```

**Hands-on Practice:**
Try these in your terminal or code:

```bash
# In bash terminal:
echo -e "\033[31mRed text\033[0m"
echo -e "\033[32mGreen text\033[0m"
echo -e "\033[34mBlue text\033[0m"

```

```python
# In Python:
print("\033[31mRed text\033[0m")
print("\033[32mGreen text\033[0m")
print("\033[34mBlue text\033[0m")

```

### Background Colors

Add 10 to any foreground color to make it a background color:

- `\033[41m` = Red background
- `\033[42m` = Green background
- `\033[44m` = Blue background

**Try this:**

```python
print("\033[41m\033[37mWhite text on red background\033[0m")

```

### Basic Text Formatting

```
1 = Bold          2 = Dim           3 = Italic        4 = Underline
5 = Blinking      7 = Reverse       8 = Hidden        9 = Strikethrough

```

**Experiment:**

```python
print("\033[1mBold text\033[0m")
print("\033[4mUnderlined text\033[0m")
print("\033[1;4mBold AND underlined\033[0m")  # Combine with semicolons!

```

### The Golden Rule: Always Reset!

**ALWAYS** end your colored text with `\033[0m` or you'll "leak" formatting to everything that comes after.

**Bad:**

```python
print("\033[31mRed text")
print("This will also be red!")  # Oops!

```

**Good:**

```python
print("\033[31mRed text\033[0m")
print("This is normal")  # Perfect!

```

## Level 3: Intermediate Skills - Cursor Control and Screen Manipulation

### Moving the Cursor Around

Now we're getting into the fun stuff! You can move your cursor anywhere on the screen:

```
\033[A = Up one line        \033[B = Down one line
\033[C = Right one column   \033[D = Left one column
\033[H = Go to top-left corner
\033[{row};{col}H = Go to specific position

```

**Cool Example - Overwriting Text:**

```python
import time
print("Loading", end="")
for i in range(5):
    print(".", end="", flush=True)
    time.sleep(1)
print("\033[6D\033[KDone!")  # Go back 6 chars, clear to end, write "Done!"

```

### Screen Control

```
\033[2J = Clear entire screen
\033[K = Clear from cursor to end of line
\033[1K = Clear from start of line to cursor
\033[2K = Clear entire current line

```

**Pro Tip Combo:**

```python
print("\033[2J\033[H", end="")  # Clear screen AND go to top-left

```

### Building a Simple Progress Bar

Let's combine what we've learned:

```python
import time

def progress_bar(total):
    for i in range(total + 1):
        percent = int(50 * i / total)
        bar = '█' * percent + '-' * (50 - percent)
        print(f'\r\033[32m[{bar}] {i}/{total}\033[0m', end='', flush=True)
        time.sleep(0.1)
    print()  # New line when done

progress_bar(20)

```

## Level 4: Advanced - 256 Colors and True Color

### 256-Color Mode

Modern terminals support 256 colors using this format:

```
\033[38;5;{n}m = Foreground color n (0-255)
\033[48;5;{n}m = Background color n (0-255)

```

The color palette is organized as:

- 0-15: Standard colors (same as basic 16)
- 16-231: 6×6×6 color cube (216 colors)
- 232-255: Grayscale ramp (24 shades)

**Color Cube Formula:**
For the 6×6×6 cube, color number = 16 + 36×r + 6×g + b
Where r, g, b are each 0-5.

**Example:**

```python
# Bright orange: r=5, g=2, b=0
color_num = 16 + 36*5 + 6*2 + 0  # = 208
print(f"\033[38;5;{color_num}mBright orange text\033[0m")

```

### True Color (24-bit RGB)

The ultimate in color control:

```
\033[38;2;{r};{g};{b}m = RGB foreground
\033[48;2;{r};{g};{b}m = RGB background

```

**Rainbow Text Example:**

```python
import math

def rainbow_text(text):
    output = ""
    for i, char in enumerate(text):
        hue = (i * 360 // len(text)) % 360
        # Convert HSV to RGB (simplified)
        r = int(255 * (1 + math.cos(math.radians(hue))) / 2)
        g = int(255 * (1 + math.cos(math.radians(hue + 120))) / 2)
        b = int(255 * (1 + math.cos(math.radians(hue + 240))) / 2)
        output += f"\033[38;2;{r};{g};{b}m{char}"
    return output + "\033[0m"

print(rainbow_text("RAINBOW TEXT!"))

```

## Level 5: Expert - Complex Applications and Libraries

### Building Interactive Menus

```python
import sys

class Menu:
    def __init__(self, options):
        self.options = options
        self.selected = 0

    def display(self):
        print("\033[2J\033[H", end="")  # Clear screen
        print("\033[1;36mSelect an option:\033[0m\n")

        for i, option in enumerate(self.options):
            if i == self.selected:
                print(f"\033[1;32m> {option}\033[0m")  # Highlighted
            else:
                print(f"  {option}")

    def navigate(self, direction):
        if direction == "up" and self.selected > 0:
            self.selected -= 1
        elif direction == "down" and self.selected < len(self.options) - 1:
            self.selected += 1
        self.display()

# Usage (simplified - real version would handle keyboard input)
menu = Menu(["Option 1", "Option 2", "Option 3"])
menu.display()

```

### Advanced Text Effects

```python
import time
import random

def matrix_effect(text, duration=3):
    """Create a Matrix-style revealing effect"""
    chars = "!@#$%^&*()_+-=[]{}|;:,.<>?"

    for step in range(20):
        output = ""
        for i, char in enumerate(text):
            if step > i:
                output += f"\033[32m{char}\033[0m"  # Revealed character
            else:
                random_char = random.choice(chars)
                output += f"\033[92m{random_char}\033[0m"  # Random character

        print(f"\r{output}", end="", flush=True)
        time.sleep(duration / 20)

    print(f"\r\033[1;32m{text}\033[0m")  # Final reveal

matrix_effect("HELLO WORLD")

```

### Professional Libraries (Don't Reinvent the Wheel!)

For real applications, use established libraries:

**Python:**

- `colorama` - Cross-platform colored terminal text
- `rich` - Rich text and beautiful formatting
- `click` - Command line interfaces with colors
- `termcolor` - Simple colored terminal output

**JavaScript/Node.js:**

- `chalk` - Terminal string styling
- `colors` - Colors and styles for node.js console
- `ansi-colors` - Easily add colors to text

**Example with Rich (Python):**

```python
from rich.console import Console
from rich.table import Table
from rich.progress import track

console = Console()

# Rich makes complex layouts easy
table = Table(title="Star Wars Movies")
table.add_column("Released", style="cyan")
table.add_column("Title", style="magenta")
table.add_column("Box Office", justify="right", style="green")

table.add_row("Dec 20, 2019", "Star Wars: The Rise of Skywalker", "$1.074 billion")
console.print(table)

# Built-in progress bars
for step in track(range(100), description="Processing..."):
    time.sleep(0.01)

```

## Level 6: Pro Tips and Advanced Techniques

### Detecting Terminal Capabilities

```python
import sys
import os

def supports_color():
    """Check if terminal supports colors"""
    return (
        hasattr(sys.stdout, "isatty") and sys.stdout.isatty() and
        os.environ.get("TERM") != "dumb"
    )

def get_terminal_size():
    """Get terminal dimensions"""
    try:
        return os.get_terminal_size()
    except OSError:
        return os.terminal_size([80, 24])  # Default fallback

```

### Performance Optimization

```python
# Slow - multiple print calls
for i in range(1000):
    print(f"\033[31mRed line {i}\033[0m")

# Fast - build string then print once
output = []
for i in range(1000):
    output.append(f"\033[31mRed line {i}\033[0m")
print('\n'.join(output))

```

### Cross-Platform Compatibility

```python
import platform

def clear_screen():
    """Clear screen on any platform"""
    if platform.system() == "Windows":
        os.system('cls')
    else:
        print("\033[2J\033[H", end="")

```

### Environment-Aware Output

```python
class SmartPrinter:
    def __init__(self):
        self.use_colors = self.supports_color()

    def supports_color(self):
        return (
            hasattr(sys.stdout, "isatty") and sys.stdout.isatty() and
            "NO_COLOR" not in os.environ
        )

    def success(self, message):
        if self.use_colors:
            print(f"\033[32m✓ {message}\033[0m")
        else:
            print(f"✓ {message}")

    def error(self, message):
        if self.use_colors:
            print(f"\033[31m✗ {message}\033[0m")
        else:
            print(f"✗ {message}")

```

### Advanced Color Science

```python
def hex_to_ansi(hex_color):
    """Convert hex color to ANSI RGB"""
    hex_color = hex_color.lstrip('#')
    r = int(hex_color[0:2], 16)
    g = int(hex_color[2:4], 16)
    b = int(hex_color[4:6], 16)
    return f"\033[38;2;{r};{g};{b}m"

def gradient_text(text, start_color, end_color):
    """Create gradient text between two hex colors"""
    start_r = int(start_color[1:3], 16)
    start_g = int(start_color[3:5], 16)
    start_b = int(start_color[5:7], 16)

    end_r = int(end_color[1:3], 16)
    end_g = int(end_color[3:5], 16)
    end_b = int(end_color[5:7], 16)

    output = ""
    for i, char in enumerate(text):
        ratio = i / (len(text) - 1) if len(text) > 1 else 0
        r = int(start_r + (end_r - start_r) * ratio)
        g = int(start_g + (end_g - start_g) * ratio)
        b = int(start_b + (end_b - start_b) * ratio)
        output += f"\033[38;2;{r};{g};{b}m{char}"

    return output + "\033[0m"

print(gradient_text("GRADIENT TEXT", "#FF0000", "#0000FF"))

```

## Master Level: Common Pitfalls and How to Avoid Them

### 1. The Reset Leak

**Problem:** Forgetting to reset formatting

```python
# Wrong
print("\033[31mError occurred")
print("This is also red!")  # Oops!

# Right
print("\033[31mError occurred\033[0m")
print("This is normal")

```

### 2. The File Redirect Issue

**Problem:** ANSI codes appearing in files

```python
# Better approach
import sys

def colored_print(text, color=None):
    if color and sys.stdout.isatty():
        print(f"\033[{color}m{text}\033[0m")
    else:
        print(text)

```

### 3. The Performance Trap

**Problem:** Too many individual print statements

```python
# Slow
for i in range(1000):
    print(f"\033[2K\rProgress: {i}")

# Fast
import sys
for i in range(1000):
    sys.stdout.write(f"\033[2K\rProgress: {i}")
    sys.stdout.flush()

```

### 4. The Compatibility Nightmare

**Solution:** Always test on multiple terminals and have fallbacks

```python
# Professional approach
class TerminalFormatter:
    def __init__(self):
        self.colors_supported = self._check_color_support()
        self.true_color = self._check_true_color_support()

    def _check_color_support(self):
        # Implementation details...
        pass

    def format(self, text, style):
        if not self.colors_supported:
            return text
        # Apply styling...
        return styled_text

```

## Graduation: You're Now an ANSI Expert!

Congratulations! You've journeyed from not knowing what ANSI codes are to understanding:

✅ **Basic colors and formatting**

✅ **Cursor control and screen manipulation**

✅ **Advanced color modes (256-color and RGB)**

✅ **Interactive terminal applications**

✅ **Performance optimization**

✅ **Cross-platform compatibility**

✅ **Professional libraries and tools**

✅ **Common pitfalls and solutions**

### Your Next Steps:

1. **Practice** - Build a small CLI tool with colors and interactive elements
2. **Explore Libraries** - Try `rich`, `colorama`, or `chalk` for your language
3. **Study Real Projects** - Look at how popular CLI tools implement their interfaces
4. **Experiment** - Create your own terminal effects and animations
5. **Share** - Teach others or contribute to open-source terminal applications

Remember: The best way to master ANSI codes is to use them in real projects. Start simple, then gradually add more sophisticated features as you become comfortable with the basics.

**Pro tip:** Keep this guide bookmarked - even experts need to look up specific codes sometimes!

Now go forth and make the terminal a more colorful, interactive place! 🌈