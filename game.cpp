#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}
{
   for(int i=0;i<9;i++)
   {
       status[i]=-1;
   }
}

int Game::possibleWins(int position, int expectedNbCircles){
    int x = position % 3;
    int y = position / 3;
    int result=0;
    int nbCross = 0;
    int nbCircles = 0;

    for(int i=0;i<3;i++)
    {
        if(getSquareStatus(status, i, y) == currentPlayer)
        {
            nbCircles++;
        }
        else if(getSquareStatus(status, i, y) != -1)
        {
            nbCross++;
        }
    }
    if(nbCircles == expectedNbCircles && nbCross == 0)
        result++;


    nbCross = 0;
    nbCircles = 0;
    for(int i=0;i<3;i++)
    {
        if(getSquareStatus(status, x, i) == currentPlayer)
        {
            nbCircles++;
        }
        else if(getSquareStatus(status, x, i) != -1)
        {
            nbCross++;
        }
    }
    if(nbCircles == expectedNbCircles && nbCross == 0)
        result++;


    if(position == 0)
    {
        nbCross = 0;
        nbCircles = 0;

        if(status[4] == currentPlayer)
            nbCircles++;

        else if(status[4] == 1 - currentPlayer)
            nbCross++;

        if(status[8] == currentPlayer)
            nbCircles++;

        else if(status[8] == 1 - currentPlayer)
            nbCross++;

        if(nbCircles == expectedNbCircles && nbCross == 0)
            result++;
    }


    if(position == 2)
    {
        nbCross = 0;
        nbCircles = 0;

        if(status[4] == currentPlayer)
            nbCircles++;

        else if (status[4] == 1 - currentPlayer)
            nbCross++;

        if(status[6] == currentPlayer)
            nbCircles++;

        else if (status[6] == 1 - currentPlayer)
            nbCross++;

        if(nbCircles == expectedNbCircles && nbCross == 0)
            result++;

    }


    if(position == 4)
    {
        nbCross = 0;
        nbCircles = 0;

        if(status[0] == currentPlayer)
            nbCircles++;

        else if(status[0] == 1 - currentPlayer)
            nbCross++;

        if(status[8] == currentPlayer)
            nbCircles++;

        else if(status[8] == 1 - currentPlayer)
            nbCross++;

        if(nbCircles == expectedNbCircles && nbCross == 0)
            result++;


        nbCross = 0;
        nbCircles = 0;

        if(status[2] == currentPlayer)
            nbCircles++;

        else if(status[2] == 1 - currentPlayer)
            nbCross++;

        if(status[6] == currentPlayer)
            nbCircles++;

        else if(status[6] == 1 - currentPlayer)
            nbCross++;

        if(nbCircles == expectedNbCircles && nbCross == 0)
            result++;

    }

    if(position == 6)
    {

        nbCross = 0;
        nbCircles = 0;

       if(status[4] == currentPlayer)
           nbCircles++;

       else if(status[4] == 1 - currentPlayer)
           nbCross++;

       if(status[2] == currentPlayer)
           nbCircles++;

       else if(status[2] == 1 - currentPlayer)
           nbCross++;

       if(nbCircles == expectedNbCircles && nbCross == 0)
           result++;
    }

    if(position == 8)
    {
        nbCross = 0;
        nbCircles = 0;

        if(status[4] == currentPlayer)
            nbCircles++;

        else if(status[4] == 1 - currentPlayer)
            nbCross++;

        if(status[0] == currentPlayer)
            nbCircles++;

        else if(status[0] == 1 - currentPlayer)
            nbCross++;

        if(nbCircles == expectedNbCircles && nbCross == 0)
            result++;
    }
    return result;
}

int Game::possibleWinsIn2(int position){
    return possibleWins(position, 1);
}

int Game::possibleWinsIn3(int position){
    return possibleWins(position, 0);
}

bool Game::hasWon(int position)
{
    auto newStatus = status;
    newStatus[position] = currentPlayer;
    return didPlayerWin(newStatus, currentPlayer, false);
}

int Game::score(int position)
{
    if(hasWon(position))
        return 1000;
    int fourBonus = position == 4 ? 1 : 0;
    int oddBonus = position %2;
    int critBonus = criticalPosition(position);
    if(critBonus > 0)
        return critBonus + oddBonus + fourBonus;
    int nbPossilbeWinsIn2 = possibleWinsIn2(position);
    int nbPossibleWinsIn3 = possibleWinsIn3(position);

    return 1 + nbPossibleWinsIn3 * 2 + 60 * nbPossilbeWinsIn2 + oddBonus + fourBonus;
}

int Game::criticalPosition(int position)
{
    auto newStatus = status;
    newStatus[position] = 1-currentPlayer;
    if( didPlayerWin(newStatus,1-currentPlayer, false))
        return 500;
    int critPosCount = 0;
    for(int i=0; i<9;i++)
    {
        if(position != i && status[i]==-1)
        {
            if(possibleCriticalPosition(newStatus, i))
                critPosCount++;
        }
    }
    if(critPosCount > 1)
        return 150;
    return 0;
}

bool Game::possibleCriticalPosition(std::array<int,9> status2, int position)
{
    auto newStatus = status2;
    newStatus[position] = 1-currentPlayer;
    return didPlayerWin(newStatus,1-currentPlayer, false);
}

void Game::nextMove()
{
    std::array<int, 9> scores;
    for(int i=0;i<9;i++)
    {
        if(status[i]==-1)
        {
            scores[i] = score(i);
        }
        else
        {
            scores[i] = 0;
        }
    }
    int nbScores150=0;
    for(int i=0;i<9;i++)
    {
        if(scores[i]==150)
            nbScores150++;
    }
    if(nbScores150>1)
    {
        for(int i=0;i<9;i++)
        {
            if(scores[i]==150)
               scores[i]=30;
        }
    }
    auto bestMove= std::max_element(scores.cbegin(), scores.cend());
    auto bestMoveValue = *bestMove;
    int nbBestMoves=0;
    for(int i=0;i<9;i++)
    {
        if(scores[i] == bestMoveValue)
            nbBestMoves++;
    }
     std::srand(std::time(nullptr));
    auto idx = std::rand() % nbBestMoves;
    for(int i=0;i<9;i++)
    {
        if(scores[i] == bestMoveValue)
        {
            if(idx-- == 0)
                place(i%3,i/3);
        }
    }

    //auto index = std::distance(scores.cbegin(), bestMove);
    //place(index%3,index/3);
}

void Game::place(int x, int y)
{
    int idx=y*3+x;

    if(status[idx] != -1)
    {
        return;
    }

    status[idx] = currentPlayer;

    if(currentPlayer == 0)
    {
        displayCross(x, y);
    }
    else
    {
       displayCircle(x, y);
    }
    if(didPlayerWin(status, currentPlayer, true))
        playerWon(currentPlayer);

    else
    {
        setCurrentPlayer(1-currentPlayer);
        if(++counter==9)
        {
            draw();
        }
        else if((currentPlayer == 1 && circleIsAI ) || (currentPlayer == 0 && crossIsAI))
        {
            nextMove();
        }
    }
}

bool Game::didPlayerWin(std::array<int,9> stat, int player, bool emitSignals)
{
    bool completeDiagLeft = true;
    bool completeDiagRight = true;

    for(int y=0;y<3;y++)
    {

        bool completeRow = true;
        bool completeColumn = true;
        for(int x=0;x<3;x++)
        {
           completeRow = completeRow && getSquareStatus(stat, x, y)==player;
           completeColumn = completeColumn && getSquareStatus(stat, y, x)==player;
        }
        if(completeRow || completeColumn)
        {
            if(emitSignals)
            {
                if(completeColumn)
                {
                    for(int a=0;a<3;a++)
                        coloriseSquare(y, a);
                }
                if(completeRow)
                {
                    for(int b=0; b<3;b++)
                        coloriseSquare(b, y);
                }
            }
            return true;
        }
        completeDiagLeft = completeDiagLeft && getSquareStatus(stat, y, y)==player;
        completeDiagRight = completeDiagRight && getSquareStatus(stat, 2-y, y)==player;
    }
    if(completeDiagLeft && emitSignals)
    {
        for(int c=0; c<3; c++)
            coloriseSquare(c, c);
    }
    if(completeDiagRight && emitSignals)
    {
        for(int d=0; d<3; d++)
            coloriseSquare(2-d, d);
    }

    return completeDiagLeft || completeDiagRight;
}

void Game::startGame(bool crossesAreHuman, bool cirlesAreHuman)
{
    crossIsAI = !crossesAreHuman;
    circleIsAI = !cirlesAreHuman;
    newGame();
    if(crossIsAI)
        nextMove();

}

int Game::getSquareStatus(std::array<int, 9> stat, int x, int y){
    return stat[y*3+x];
}

int Game::getCurrentPlayer()
{
    return currentPlayer;
}


void Game::setCurrentPlayer(int player)
{
    if(currentPlayer !=player)
    {
        currentPlayer = player;
        currentPlayerChanged();
        playerCounter(currentPlayer);
    }
}
