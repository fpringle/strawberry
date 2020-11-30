# strawberry
A C++ chess engine.

### Submodules
strawberry has several components.

#### [strawberryCore](https://github.com/fpringle/strawberryCore)
- the core of the strawberry chess engine.

#### [strawberryGUI](https://github.com/fpringle/strawberryGUI)
- a Graphical User Interface (GUI) for the chess engine, written using Qt.

#### [strawberryUCI](https://github.com/fpringle/strawberryUCI)
- an interface for strawberry to communicate via the Universal Chess Interface (UCI) protocol.


### Build dependencies
- [Qt](https://www.qt.io)
  - all submodules need qmake to generate makefile
  - strawberryGUI needs Qt core and Qt gui
