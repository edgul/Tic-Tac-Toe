#include "AI.h"

#include <QDebug>
#include "Utils.h"
#include <time.h>

AI::AI()
{
    difficulty = DIFFICULTY_MEDIUM;
}

Cell AI::getMove(SimpleBoard simpleBoard, PieceType piece, Difficulty difficulty)
{
    if (difficulty == DIFFICULTY_EASY)
    {
        return getDumbassMove(simpleBoard, piece);
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

Cell AI::getDumbassMove(SimpleBoard simpleBoard, PieceType piece)
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

Cell AI::getRandomMove(SimpleBoard simpleBoard, PieceType piece)
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

    return getRandomMove(simpleBoard, piece);;
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

Quad AI::get_best_move(BoardModel board)
{
    Quad best_move = board.available_win(piece_type);

    if (best_move == QUAD_NONE)
    {
        QString player_piece = PLAYER_O;
        if (piece_type == PLAYER_O) player_piece = PLAYER_X;

        best_move = board.available_win(player_piece);
    }

    if (best_move == QUAD_NONE)
    {
        best_move = highest_productivity_move(board);
    }

    return best_move;
}

Quad AI::get_move(BoardModel board)
{
    Quad move;
    if (difficulty == DIFFICULTY_EASY)
    {
        move = get_dumbass_move(board);
    }
    else
    {
        move = get_best_move(board);
    }

    return move;
}

// Assumes there is at least one move to make
Quad AI::get_dumbass_move(BoardModel board)
{
    Quad move;

    // dumb AI -- first empty quad
    for (int i = 0; i < board.size(); i ++)
    {
        if (board.piece_at(i) == EMPTY_CELL)
        {
            move = (Quad) i;
            break;
        }
    }

    return move;
}

Quad AI::highest_productivity_move(BoardModel board)
{
    QList<Quad> empty_quads = board.quads_with_piece(EMPTY_CELL);

    Quad highest_p_quad = empty_quads[0];
    int highest_productivity = board.productivity(QUAD_TOP_LEFT, piece_type);
    foreach (Quad quad, empty_quads)
    {
        int p = board.productivity(quad, piece_type);

        if (p > highest_productivity)
        {
            highest_productivity = p;
            highest_p_quad = quad;
        }
    }

    return highest_p_quad;
}

void AI::set_piece_type(QString piece)
{
    piece_type = piece;
}

QString AI::get_piece()
{
    return piece_type;
}

void AI::set_difficulty(Difficulty new_diff)
{
    difficulty = new_diff;
}
