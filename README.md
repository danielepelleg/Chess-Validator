<!-- PROJECT LOGO -->
<br />    
<p align="center">
  <a href="https://github.com/danielepelleg/Chess-Validator">
    <img src="https://www.flaticon.com/svg/static/icons/svg/3063/3063488.svg" alt="Logo" width="130" height="130">
  </a>
  <h1 align="center">Chess - Validator</h1>
  <p align="center">
    C++ implementation of a console program representing the moves every piece on a chess can perform.
  </p>
  
  <!-- TABLE OF CONTENTS -->
  ## Table of Contents
  
  - [Table of Contents](#table-of-contents)
  - [About The Project](#about-the-project)
  - [Getting Started](#getting-started)
  - [License](#license)
  - [Contributors](#contributors)

## About The Project

**Chess-Validator** is a program that reads a state of a chess from a file _src/scacchiera.txt_ and creates a document file _src/mosse.txt_ showing, for each piece, the list of moves it can do.

The program recognizes every piece with a char, and a struct for every piece implements the list of the moves it can do. A Cell is defined by a struct so composed:

    struct Cell {
        Piece piece;
        Color color;
    };

User are given just the program file and a document representing the state of a chess. Once the program runs it creates the document showing the moves of the pieces. The initial state of the chess given in the file is the following:

    -----------------
    | |b| | | | | | |
    -----------------
    | | |n|q| | | | |
    -----------------
    |p| | | | | |P| |
    -----------------
    |k|r| | |p|P|p| |
    -----------------
    | | |B| |Q|K| | |
    -----------------
    | | | | | |p|r|p|
    -----------------
    | |P| |p| |n| |p|
    -----------------
    | |b| | | | | | |
    -----------------

The chess is seen as a matrix 8x8 in which there are white and black pieces, the first are lower case characters, the second uppercase. Every character is assigned to a piece as it follows:

    p Pawn         | Pedone

    r Rook         | Torre

    n Knight       | Cavallo

    b Bishop       | Alfiere

    q Queen        | Regina

    k King         | Re

    No Piece       | Nessun Pezzo

Everyone of these Pieces, as it is for every Color is part of an enumeration. Like for the pieces the color has a value "no color" for the empty cell which contains no piece.

<!-- GETTING STARTED -->

## Getting Started

You can just clone this repository and run the "pasw00401.cpp" in "src/" folder to create the
"mosse.txt" file listing the moves every piece in the chess can perform. It is possible to change the initial state of the chess in the
"scacchiera.txt" file, just watch out to follow the legend used for every piece and count the empty space between the pieces.

<!-- LICENSE -->

## LICENSE

Distributed under the GPL License. See `LICENSE` for more information.

   <!-- CONTRIBUTORS -->

## CONTRIBUTORS

[Daniele Pellegrini](https://github.com/danielepelleg) - 285240
