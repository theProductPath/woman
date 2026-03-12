# WoMAN Pages

**A curses-based Unix command browser — originally written in 1989, rebuilt in 2026.**

**[Try it in your browser →](https://theproductpath.github.io/woman/)** | **[GitHub](https://github.com/theProductPath/woman)**

[![Deploy on Railway](https://railway.com/button.svg)](https://railway.com/template/woman?referralCode=woman)

```
 v. 2.0        Welcome to the WoMAN Pages        Steve Jones
          Scroll through list and select a topic

   File Management
   Text Processing
 > System Information          ← highlighted
   Networking
   Compression and Archives
   Searching and Finding
   Disk and Storage
   User and Permissions
   Process Management
   Shell and Scripting
   Version Control

 J-Down  K-Up  T-Top  B-Bottom  Enter-Select  H-Help  Q-Quit
```

## The Story

In 1989, Unix man pages were the definitive reference — but only if you already knew what command you were looking for. There was no way to browse or discover commands by what they *did*.

As a college student, **Steven R. Jones** built **WoMAN** (a play on Unix's `man` command) to solve exactly that problem. WoMAN organized every available Unix command into browsable topics with short descriptions, letting users navigate with simple keystrokes and then jump straight into the man page for any command.

The program was adopted by the campus IT department and deployed across the university's Unix systems.

36 years later, the original source code was recovered from scanned printouts and rebuilt with the help of AI — bringing a 1989 terminal program back to life on modern systems.

## Quick Start

```bash
# Clone the repo
git clone https://github.com/theProductPath/woman.git
cd woman

# Build
cd src
make

# Run
./woman
```

## Requirements

- A C compiler (gcc or clang)
- ncurses library (included on macOS; install `libncurses-dev` on Debian/Ubuntu)
- A terminal emulator

### macOS
Everything you need is already installed with Xcode Command Line Tools:
```bash
xcode-select --install   # if you haven't already
```

### Linux (Debian/Ubuntu)
```bash
sudo apt-get install build-essential libncurses-dev
```

### Linux (Fedora/RHEL)
```bash
sudo dnf install gcc ncurses-devel
```

## How to Use

WoMAN uses vi-style navigation:

| Key | Action |
|-----|--------|
| `J` or `↓` | Move down |
| `K` or `↑` | Move up |
| `T` | Jump to top |
| `B` | Jump to bottom |
| `Enter` | Select item |
| `R` | Return to previous page |
| `H` | Help screen |
| `S` | The story behind WoMAN |
| `Q` | Quit |

1. **Topics page**: Browse command categories and press Enter to select one
2. **Commands page**: Browse commands within a topic and press Enter to view its man page
3. **Man page**: Read the full manual, then press `q` to return to WoMAN

## Customizing the Command List

WoMAN reads its command data from a file called `manual` in the same directory as the binary. The format is simple:

```
Topic Name
command1	Description of command 1
command2	Description of command 2

Another Topic
command3	Description of command 3
```

Rules:
- **Topic lines** start with an uppercase letter (no leading whitespace)
- **Command lines** are indented with a tab between the command name and description
- **Blank lines** separate topics from each other

Edit the `manual` file to add your own commands, tools, or even non-Unix references.

## Try It Online

**Web simulator** — no install needed, runs in your browser:
https://theproductpath.github.io/woman/

**Docker** — run a real terminal in your browser:
```bash
docker build -t woman .
docker run -p 7681:7681 woman
# Open http://localhost:7681
```

Or deploy to Railway with one click using the button above.

## Project Structure

```
woman/
├── README.md
├── LICENSE
├── Dockerfile              # Railway/Docker deployment
├── src/                    # Modernized source (compiles on current systems)
│   ├── Makefile
│   ├── woman.h
│   ├── main.c
│   ├── pick_topic.c
│   ├── highlt.c
│   ├── pr_heading.c
│   ├── pr_array.c
│   ├── get_topics.c
│   ├── get_comm.c
│   ├── get_string.c
│   ├── end_prog.c
│   ├── story.c
│   └── manual              # Command data file
├── docs/                   # VT100 web simulator (GitHub Pages)
│   └── index.html
├── docker/                 # Docker compose for local testing
│   ├── Dockerfile
│   └── docker-compose.yml
└── original_source/        # Faithful transcription of the 1989 source code
    └── *.c, *.h, Makefile
```

## History

- **1989** — Original version written by Steven R. Jones as a college student. Compiled with `mcc`, linked against curses and termcap. Deployed campus-wide.
- **2026** — Source code recovered from scanned printouts of the original dot-matrix printout. Rebuilt for modern ncurses with the assistance of AI (Claude). Published as open source for the first time.

## License

MIT License — see [LICENSE](LICENSE) for details.
