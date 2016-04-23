# gobl

Go machine learning library

-----------

This is the base of a machine learning system for the game of Go.
It provides components broken up into the following sections

```
goblb -- utilities for dealing with boards and playing games
gobld -- higher-level driver utilities for playing sgf's and
         iterating through games
gobll -- abstract classes for ML models
goblr -- utilities for creating representations or
         features used in the ML models
gobls -- utilities for parsing sgf files
goblu -- low-level utilities
```

Specifically, `goblr` provides utilities for creating the tensors that
be used in the [`tensorflow`](https://www.tensorflow.org/),
namely

*  liberties -- a group of matrices parameterized in the perspective
   (whose turn it is) and a level. Each number of liberties up to
   that level will have its own matrix, only the groups on the board
   with a number of liberties of that size will have a value of 1.0 in
   their respective locations in the matrix.
*  ko -- a matrix that has a value of 1.0 only in a place where there
   is currently an active ko.

#### Building

To build the library run
```bash
make lib
```
which will populate `gobl/include` with the library headers.

If the user has [`gtest`](https://github.com/google/googletest)
installed on their system, a test suite can be built by setting
`GTEST_DIR` to the location that `gtest` is installed
```bash
GTEST_DIR=/my/gtest/dir make gtest
```

#### Example

An example main has been provided that allows the user to play games
against himself. There is also an option `--parse filename`
to parse and then print an sgf file.

This can be built with
```
make main
```
