// Game of Life JS

var gridHeight = 500; // adjust height - also must change in HTML file canvas element
var gridWidth = 500;  // adjust width - also must change in HTML file canvas element
var theGrid = createArray(gridWidth);
var mirrorGrid = createArray(gridWidth);
var c = document.getElementById("cellsCanvas");
var ctx = c.getContext("2d");
ctx.fillStyle = "#33cc33";

fillRandom(); // create the starting state for the grid by filling it with random cells

tick(); // call main loop

// functions
function tick() { // main loop
    console.time("loop");
    drawGrid();
    updateGrid();
    console.timeEnd("loop");
    requestAnimationFrame(tick); // update animation on canvas
}

function createArray(rows) { // creates a 2 dimensional array of required height
    var arr = [];
    for (var i = 0; i < rows; i++) {
        arr[i] = [];
    }
    return arr;
}

function fillRandom() { // fill the grid randomly
    for (var j = 100; j < gridHeight - 100; j++) { // iterate through rows
        for (var k = 100; k < gridWidth - 100; k++) { // iterate through columns
            theGrid[j][k] = Math.round(Math.random()); // creates fp number between 0 and 1 and rounds to 0 or 1
        }
    }
}

function drawGrid() { // draw the contents of the grid onto a canvas
var liveCount = 0;
    ctx.clearRect(0, 0, gridHeight, gridWidth); // clear the canvas ahead of each redraw
    for (var j = 1; j < gridHeight; j++) { // iterate through rows
        for (var k = 1; k < gridWidth; k++) { // iterate through columns
            if (theGrid[j][k] === 1) {
                ctx.fillRect(j, k, 1, 1);
                liveCount++;
            }
        }
    }
    console.log(liveCount/100);
}

function updateGrid() { // perform one iteration of grid update
    
    for (var j = 1; j < gridHeight - 1; j++) { // iterate through rows
        for (var k = 1; k < gridWidth - 1; k++) { // iterate through columns
            var totalCells = 0;
            // add up the total values for the surrounding cells
            totalCells += theGrid[j - 1][k - 1]; // top left
            totalCells += theGrid[j - 1][k]; // top center
            totalCells += theGrid[j - 1][k + 1]; // top right

            totalCells += theGrid[j][k - 1]; // middle left
            totalCells += theGrid[j][k + 1]; // middle right

            totalCells += theGrid[j + 1][k - 1]; // bottom left
            totalCells += theGrid[j + 1][k]; // bottom center
            totalCells += theGrid[j + 1][k + 1]; // bottom right

            // apply the rules to each cell
            switch (totalCells) {
                case 2:
                    mirrorGrid[j][k] = theGrid[j][k]; // grid pos remains the same
                    break;
                case 3:
                    mirrorGrid[j][k] = 1; // = 1 so if empty, cell created and if full, cell remains
                    break;
                default:
                    mirrorGrid[j][k] = 0; // otherwise, cell dies or pos. remains empty
            }
        }
    }

    // mirror edges to create wraparound effect
    for (var l = 1; l < gridHeight - 1; l++) { // iterate through rows
        // top and bottom
        mirrorGrid[l][0] = mirrorGrid[l][gridHeight - 3];
        mirrorGrid[l][gridHeight - 2] = mirrorGrid[l][1];
        // left and right
        mirrorGrid[0][l] = mirrorGrid[gridHeight - 3][l];
        mirrorGrid[gridHeight - 2][l] = mirrorGrid[1][l];
    }

    // swap grids
    var temp = theGrid;
    theGrid = mirrorGrid;
    mirrorGrid = temp;

}
