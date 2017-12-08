# Flip Puzzle

A `n x m` grid, with numbers 1 through `nm`, must be rearranged in such way that the numbers end up in ascending order, much like in the 15-puzzle.

#### Operations

The operations that allow for the re-arrangement of the cells are the following:

* Flip Row: Invert the order of the elements in the selected row.
* Flip Column: Invert the order of the elements in the selected column.

#### Constraints

To allow for better visualization of the problem, `n` and `m` must both be even.

# The program

The program looks for a solution using A*, showing a visualization of the solution.

#### Dependencies

The visualizator requires GTK+3 to be installed. If you are on any Debian distribution, like Ubuntu, you should be able to install it with:

```
$ sudo apt-get install libgtk-3-dev
```

#### Compiling

To compile the programs, go to the root folder of the repository, and enter

```
$ make
```

That will create three executables in that same folder:

* `generator`: for generating tests
* `solver`: for solving the different instances of the problem.
* `beholder`: the visualization window. Both the generator and the solver will run this to show what they're doing.

#### Running

To run the solver, enter

```
./solver test
```

Where `test` is the path to a test. The test folder comes with some tests to try the solver on.

## Generator
