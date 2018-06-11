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
    bool verticalp(int coluna,int linha);
    bool verticaln(int coluna,int linha);
    bool horizontalp(int coluna,int linha);
    bool horizontaln(int coluna,int linha);
    bool diagdirp(int coluna,int linha);
    bool diagdirn(int coluna,int linha);
    bool diagesqp(int coluna,int linha);
    bool diagesqn(int coluna,int linha);
    bool fimdejogo();
    bool verificafim(Cell* cell);

};

#endif // REVERSI_H
