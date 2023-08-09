# cursed-matrix
Matrix effect developed in C using ncurses library.

> **IMPORTANT**: This project is still under development. It displays a very basic and unfinished version of the matrix effect. More changes are upcoming

## About 

![](docs/output.gif)

## Technology stack
Project has been developed in C. 

## Getting Started

### Prerequisites
The project has been developed in C using the `ncurses` library. 

The following list are the dependencies required to properly run the project:
- `libncurses5-dev`
- `gcc` or any C compiler.
- `Make` to build the project.

### Installation & Building
To install execute the following steps:

1) Clone the repository. Command: `git clone https://github.com/salorak/cursed-matrix.git`.
2) Go into directory. Command: `cd cursed-matrix/`.
3) Build the project. Command: `make all`.


### Usage 

Once project is built a new binary file would be available called `main`.
To run it execute on the project directory.

```bash
./main --help

# Usage: mcursed [-fs --falling-speed] [ -c --color ] [ -tm --trailing-memory] [-h --help]
#    -fs / --failing-speed NUMBER:
#        Changes the speed of the letters falling. Range 1 - 100
#    -tm / --trailing-memory NUMBER:
#        the amount of characters alive in the trailing while alive. Range 0 - 50
#    -c / --cells NUMBER:
#        Changes the maximum amount of leading characters on screen. Range 1 - 100
#    -co / --color COLOR:
#        Not implemented yet. Changes the color of the leading character falling. One of WHITE | GREEN | BLUE | RED | PURPLE | YELLOW. 
#    -h / --help:" 
#        Displays this usage help messsage

```


## Upcoming changes

- [ ] Improve code readability.
- [ ] Improve image display.
- [X] Add command line argument to support changing maximum cells on screen. 
- [X] Add command line argument to support changing falling speed.
- [X] Add command line argument to support changing trailing memory distance. ( How many characters are shown on each falling column )
- [ ] Add command line argument to support changing colors.


## License

Distributed under the MIT License. See `LICENSE` for more information. 

