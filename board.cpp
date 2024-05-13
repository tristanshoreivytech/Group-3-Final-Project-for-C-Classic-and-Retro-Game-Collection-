#include "board.h"
#include <cctype>
#include <iostream>
#include <string>

#include "define.h"
#include "game.h"
#include "pieces.h"

// TODO: add other FEN fields
void Board::readFen(std::string fen) {
    int row = 0;
    int col = 0;

    for (char c : fen) {
        if (c == '/') {
            row++;
            col = 0;
            continue;
        }
        else {
            if (isdigit(c)) {
                for (int _ = 0; _ < static_cast<int>(c - '0'); _++) {
                    this->board[row][col] = 0x00;
                    col++;
                }
            }
            else {
                PieceColor color = isupper(c) ? DIAMOND : PEARL;
                Piece p;

                c = tolower(c);

                switch (c) {
                case 'p':
                    p = Pieces::makePiece(PAWN, color);
                    break;
                case 'r':
                    p = Pieces::makePiece(ROOK, color);
                    break;
                case 'n':
                    p = Pieces::makePiece(KNIGHT, color);
                    break;
                case 'b':
                    p = Pieces::makePiece(BISHOP, color);
                    break;
                case 'q':
                    p = Pieces::makePiece(QUEEN, color);
                    break;
                case 'k':
                    p = Pieces::makePiece(KING, color);
                    break;
                default:
                    p = Pieces::makePiece(PAWN, color);
                }

                this->board[row][col] = p;
                col++;
            }
        }
    }
}
// TODO: add other info to board printing
void Board::printBoard() {
    std::cout << "CHESSBOARD INFO" << std::endl;
    std::cout << "Turn: " << (this->getActiveColor() == DIAMOND ? "diamond" : "pearl") << std::endl;
    std::cout << "Move: " << this->getMoveNumber() << std::endl;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << this->board[i][j] << std::string((board[i][j] >= 10 ? 1 : 2), ' ');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

PieceColor Board::getActiveColor() {
    return this->active_color;
}

float Board::getMoveNumber() {
    return this->move_number;
}

void Board::incrementMoveNumber() {
    this->move_number += 0.5f;
}

void Board::toggleActiveColor() {
    this->active_color = this->getActiveColor() == DIAMOND ? PEARL : DIAMOND;
}

void Board::reverse() {
    int board[8][8];

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            board[7 - i][j] = this->board[i][j];
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            this->board[i][j] = board[i][j];
        }
    }

    this->is_reversed = !this->is_reversed;
}

bool Board::isReversed() {
    return this->is_reversed;
}

void Board::tryMove(Location starting, Location ending) {
    if (this->getActiveColor() != Pieces::getPieceColor(this->getPieceAt(starting))) { // out of turn
        return;
    }

    if (Game::isValidMove(this, starting, ending, true)) {
        this->makeMove(starting, ending);
        this->clearSelectedPiece();

        this->incrementMoveNumber();
        this->toggleActiveColor();
    }
}

void Board::makeMove(Location starting, Location ending) {
    int r1, c1, r2, c2;

    r1 = starting.first;
    c1 = starting.second;

    r2 = ending.first;
    c2 = ending.second;

    this->board[r2][c2] = this->board[r1][c1];
    this->board[r1][c1] = 0x00;
}

int Board::getPieceAt(Location location) {
    return this->board[location.first][location.second];
}


Location Board::getSelectedPiece() {
    return this->selected_piece;
}

void Board::setSelectedPiece(int i, int j) {
    this->selected_piece = makeLocation(i, j);
}

void Board::clearSelectedPiece() {
    this->selected_piece = makeLocation(-1, -1);
}

bool Board::hasSelectedPiece() {
    return (this->selected_piece.first != -1 && this->selected_piece.second != -1);
}