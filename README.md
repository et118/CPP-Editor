
# CPP-Editor
CPP-Editor is a proof of concept terminal based user interface (TUI) implementing an explorer, editor and terminal.
![img.png](img.png)

## Features
* Automatic scaling
* Loading all text based files
* Saving all text based files
* Running .py files
* Keyboard based text editing
* Mouse based explorer menu
* Autosaving on crash

## Shortcomings
* HEAVILY underoptimized (had no time for that). This makes larger files (around a kilobyte (Nevermind, that was only on WSL for some reason)) too slow to run even on a good pc, and might cause freezing during the time it takes to render.
* Cant create new files
* A bit unstable on linux (it was developed in WSL so not really the same terminal environment as Alacritty)
* Can't type all characters
* No copy pasting
* No mouse scrolling (though the editor supports keyboard based scrolling)
* Can't display tabs or certain non-monospace characters
* Only supports running python files
* Doesnt support displaying the error pipe when running programs
* It supports colors, but i didnt have time to add any
* No way to show notifications for status messages (like if a file is unavailable)
