
# CPP-Editor
CPP-Editor is a proof of concept terminal based user interface (TUI) implementing a file explorer, editor and terminal.
![img.png](img.png)

## How to run
```bash
git clone https://github.com/et118/CPP-Editor
cd CPP-Editor
```
Now you can either 1: use docker/podman, or 2: compile and run manually
### 1. Docker/Podman
On windows: Click ``run.bat``
<br>
On linux: Run ``make``

### 2. Compile and run manually
```bash
cmake -S . -B build
cmake --build build
./build/CPP-Editor

(optionally run with Valgrind to perform a memory check)
valgrind --leak-check=full ./build/CPP-Editor
```


## Shortcuts
Note: You need to hover your mouse over the Editor window for it to capture your input.

| Key        | Action                  |
|------------|-------------------------|
| Ctrl + S   | Save the current file   |
| Ctrl + Q   | Exit entire application |

## Features
* Automatic scaling
* Loading all text based files
* Saving all text based files
* Running .py files
* Keyboard based text editing
* Mouse based filesystem explorer navigation
* Autosaving on crash

## Shortcomings
* HEAVILY underoptimized (had no time for that). This makes larger files (a couple kilobytes) too slow to run even on a good pc, and might cause freezing during the time it takes to render.
* Cant create new files
* Can't type or handle all characters (Tab, emojis etc.)
* No copy pasting
* No mouse scrolling (though the editor supports keyboard based scrolling)
* Only supports running python files
* Doesnt support displaying the error pipe when running programs
* It supports colors, but i didnt have time to add any
* No way to show notifications for status messages (like if a file is unavailable)
