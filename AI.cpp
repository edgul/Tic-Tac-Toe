#include "AI.h"

#include <QDebug>
#include "Utils.h"
#include <time.h>

AI::AI()
{
}

Cell AI::getMove(SimpleBoard simpleBoard, PieceType piece, Difficulty difficulty)
{
    if (difficulty == DIFFICULTY_EASY)
    {
        return getRandomMove(simpleBoard);
    }
    else if (difficulty == DIFFICULTY_MEDIUM)
    {
        return getOkayMove(simpleBoard, piece);
    }
    else
    {
        return getBestMove(simpleBoard, piece);
    }
}

Cell AI::getDumbassMove(SimpleBoard simpleBoard)
{
    for (int i = 0; i < simpleBoard.board.size(); i++)
    {
        if (simpleBoard.board[i] == PIECE_TYPE_NONE)
        {
            return (Cell) i;
        }
    }
    return CELL_NONE;
}

Cell AI::getRandomMove(SimpleBoard simpleBoard)
{
    BoardModel boardModel(simpleBoard);
    QList<Cell> cells = boardModel.emptyCells();

    srand(time(NULL));
    int randomIndex = rand() % cells.length();
    return cells[randomIndex];
}

Cell AI::getOkayMove(SimpleBoard simpleBoard, PieceType piece)
{
    BoardModel boardModel(simpleBoard);

    // look for win
    Cell okayMove = boardModel.availableWin(piece);
    if (okayMove != CELL_NONE)
    {
        return okayMove;
    }

    // block a win
    okayMove = boardModel.availableWin(Utils::opponentPiece(piece));
    if (okayMove != CELL_NONE)
    {
        return okayMove;
    }

    return getRandomMove(simpleBoard);
}

Cell AI::getBestMove(SimpleBoard simpleBoard, PieceType piece)
{
    BoardModel boardModel(simpleBoard);

    // look for win
    Cell bestMove = boardModel.availableWin(piece);
    if (bestMove != CELL_NONE)
    {
        return bestMove;
    }

    // block a win
    bestMove = boardModel.availableWin(Utils::opponentPiece(piece));
    if (bestMove != CELL_NONE)
    {
        return bestMove;
    }

    return getHighestProductivityMove(simpleBoard, piece);
}

Cell AI::getHighestProductivityMove(SimpleBoard simpleBoard, PieceType piece)
{
    BoardModel boardModel(simpleBoard);

    QList<Cell> emptyCells = boardModel.emptyCells();

    if (emptyCells.isEmpty())
    {
        qDebug() << "Cannot compute productivity - No Empty cells";
        Q_ASSERT(false);
        return CELL_NONE;
    }

    Cell highestCell = emptyCells[0];
    int highestProductivity = productivity(emptyCells[0], simpleBoard, piece);
    foreach (Cell cell, boardModel.emptyCells())
    {
        int p = productivity(cell, simpleBoard, piece);

        if (p > highestProductivity)
        {
            highestProductivity = p;
            highestCell = cell;
        }
    }

    return highestCell;
}

int AI::productivity(Cell cell, SimpleBoard simpleBoard, PieceType piece)
{
    int p = 0;

    BoardModel boardModel(simpleBoard);

    foreach (auto winLine, boardModel.winLines())
    {
        if (winLine.keys().contains(cell))
        {
            if (!winLine.values().contains(Utils::opponentPiece(piece)))
            {
                p++;
            }
        }
    }

    return p;
}
