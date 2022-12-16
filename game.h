#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <array>

class Game : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentPlayer READ getCurrentPlayer WRITE setCurrentPlayer NOTIFY currentPlayerChanged)

public:
    explicit Game(QObject *parent = nullptr);


    Q_INVOKABLE void place(int x, int y);

    int getCurrentPlayer();

    void setCurrentPlayer(int player);

    int getSquareStatus(std::array<int, 9> stat, int x, int y);

    bool didPlayerWin(std::array<int,9> stat, int player, bool emitSignals);

    Q_INVOKABLE void startGame(bool crossesAreHuman, bool cirlesAreHuman);

    bool possibleCriticalPosition(std::array<int,9> status2, int position);

signals:

    void displayCross(int x, int y);

    void displayCircle(int x, int y);

    void currentPlayerChanged();

    void playerWon(int);

    void draw();

    void newGame();

    void chooseCaracter();

    void playerCounter(int);

    void coloriseSquare(int x, int y);

    void beginningText();

private:
    bool hasWon(int position);

    int criticalPosition(int position);

    int possibleWins(int position, int expectedNbCircles);

    int possibleWinsIn2(int position);

    int possibleWinsIn3(int position);

    int score(int position);

    void nextMove();

    int currentPlayer = 0;

    std::array<int,9> status;

    int counter = 0;

    bool crossIsAI = false;

    bool circleIsAI = false;

};

#endif // GAME_H
