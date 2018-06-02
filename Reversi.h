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
    bool verticalpos(int coluna,int linha);
    bool verticalneg(int coluna,int linha);
    bool horizontalpos(int coluna,int linha);
    bool horizontalneg(int coluna,int linha);
    bool diagdirpos(int coluna,int linha);
    bool diagdirneg(int coluna,int linha);
    bool diagesqpos(int coluna,int linha);
    bool diagesqneg(int coluna,int linha);
    bool verificalados(Cell* cell);
    /*
    bool verticalp(Cell* cell);
    bool verticaln(Cell* cell);
    bool horizontalp(Cell* cell);
    bool horizontaln(Cell* cell);
    bool diagdirp(Cell* cell);
    bool diagdirn(Cell* cell);
    bool diagesqp(Cell* cell);
    bool diagesqn(Cell* cell);
    bool fimdejogo();
    bool verificafim(Cell* cell);*/

};

#endif // REVERSI_H
