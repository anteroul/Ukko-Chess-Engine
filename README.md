# Ukko Chess Engine v0.4.5 alpha

### ATTENTION! This is an old repository, please for the love of God do not code C++ like this.

#### Version changes:
- Abstracted promotion table UI into a separate class which inherits the GUI class.
- Fixed the memory leak when exiting the program.

#### TODO:
- Make GUI to inherit the Game class.
- Separate Game class functionalities into separate data structures (std::function might be useful here).
- Implement Button class to inherit GUI.
- Tidy-up the Game::Render() function.
