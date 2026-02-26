# Terminal Chess

A two-player chess game that runs in the terminal, built in C with full move validation and check/checkmate detection.

---

## Features

- Two-player local gameplay (White vs Black)
- Full move validation for all pieces — Pawn, Rook, Bishop, Knight, Queen, and King
- Check and checkmate detection
- Blocking check — allied pieces can intercept an attack on the king
- Color-coded board rendering using ANSI escape codes
- Input sanitization and error handling throughout

---

## Project Structure

```
terminal-chess/
├── chess.c       # Main source file (entire game logic)
├── README.md     # Project documentation
└── .gitignore    # Git ignore rules
```

---

## How to Compile

Make sure you have `gcc` installed, then run:

```bash
gcc chess.c -o chess -lm
```

---

## How to Run

```bash
./chess
```

---

## How to Play

The board is displayed with coordinates — columns labeled `a` to `h`, rows labeled `1` to `8`.

Enter your move when prompted, in this format:

```
<column> <row> <column> <row>
```

**Example** — move a piece from E2 to E4:

```
Enter the characters : E 2 E 4
```

- **Yellow** pieces = White
- **Cyan** pieces = Black

Players alternate turns, starting with White. The game ends when a king is in **checkmate**.

---

## Piece Reference

| Piece  | Symbol |
| ------ | ------ |
| Pawn   | P      |
| Rook   | R      |
| Bishop | B      |
| Knight | N      |
| Queen  | Q      |
| King   | K      |

---

## Key Functions

| Function                    | Description                                                          |
| --------------------------- | -------------------------------------------------------------------- |
| `canIMove()`                | Validates whether a move is legal for a given piece                  |
| `isCheck()`                 | Detects if either king is currently under check                      |
| `isGameOver()`              | Checks for checkmate — king escape, capture attacker, or block       |
| `movePiece()`               | Executes the move on the board                                       |
| `renderBoard()`             | Renders the board with ANSI colors to the terminal                   |
| `isItRightMoveUnderCheck()` | Ensures a move resolves check rather than leaving the king in danger |

---

## Requirements

- GCC compiler
- A terminal with ANSI color support (most modern terminals work fine)

---

## Known Limitations

- No support for special moves: castling, en passant, or pawn promotion
- No undo/redo functionality
- Two players must share the same keyboard

---

## Author

**ED24B017**
