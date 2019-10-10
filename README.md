# Chess-Validator
A program that reads a state of a chess from a file and creates a document file showing, for each piece, the list of moves it can do.

The program recognizes every piece with a char, and a struct for every piece implements the list of the moves it can do.

The chess is seen as a matrix 8x8 in which there are white and black pieces, the first are lower case characters, the second uppercase. User are given just the program file and a document representing the state of a chess. Once the program runs it creates the document showing the moves of the pieces.


    p Pawn         | Pedone

    r Rook         | Torre

    n Knight       | Cavallo

    b Bishop       | Alfiere

    q Queen        | Regina

    k King         | Re

    No Piece       | Nessun Pezzo
