# Game of Life

## Two Implementations of Conway's Game of Life:

### 1. A C implementation, run and visualised in the terminal using ASCII.

This version assumes that:
1. The user wishes to manually create or choose an initial configuration
2. The user wishes to specify the number of generations the game runs for
3. The user wishes to specifiy the width and height of the grid the cells live/die in

To run:
1. Clone this repository
2. Navigate to `./CVersion`
3. Compile by running `gcc -ansi -Wall GameOfLife.c -o GameOfLife`
4. Run `./GameOfLife <initial config file path> <width> <height> <no. of generations>`

See the Instructions.txt file for more info.

### 2. A simple, automatic, and browser-running implementation using JavaScript, HTML, CSS, and an HTTP local server.

This version assumes that:
1. The grid features wrap-around.
2. The user doesn't require the ability to enter their own initial state i.e. it is randomly generated using JS.
3. The user doesn't require the ability to stop or pause the game i.e. it creates a continuous pretty visualisation, generation by generation, in the browser.

References:
- <a href="https://www.w3schools.com/html/html5_canvas.asp>">https://www.w3schools.com/html/html5_canvas.asp</a>
- <a href="http://disruptive-communications.com/conwaylifejavascript/">http://disruptive-communications.com/conwaylifejavascript/</a>

To run:
1. Clone this repository.
2. Navigate to `./BrowserVersion`.
3. Run `npm start`.
4. Click on "GameOfLife.html" from the index page or navigate to <a href="http://localhost:7000/GameOfLife.html">localhost:7000/GameOfLife.html</a> in your browser.

See the Instructions.txt file for more info.
