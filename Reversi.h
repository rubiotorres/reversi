#ifndef REVERSI_H
#define REVERSI_H

#include <QMainWindow>

class Cell;

namespace Ui {
    class Reversi;
}

class Reversi : public QMainWindow {
    Q_OBJECT

public:
    explicit Reversi(QWidget *parent = 0);
    virtual ~Reversi();

private:
    Ui::Reversi *ui;
    Cell* m_cells[8][8];
    int m_count[2];
    int player = 1;

private slots:
    void play();
    void reset();
    void showAbout();
    void updateStatus(int oldplayer, int newplayer);
    bool verticalpos(Cell* cell);
    bool verticalneg(Cell* cell);
    bool horizontalpos(Cell* cell);
    bool horizontalneg(Cell* cell);
    bool diagdirpos(Cell* cell);
    bool diagdirneg(Cell* cell);
    bool diagesqpos(Cell* cell);
    bool diagesqneg(Cell* cell);
    bool verificalados(Cell* cell);

};

#endif // REVERSI_H
