#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Cell : public QPushButton {
    Q_OBJECT

public:
    explicit Cell(QWidget *parent = 0);
    virtual ~Cell();

    int player() const { return m_player; }
    int row() const { return m_row; }
    int col() const { return m_col; }

    void setRow(int row) { m_row = row; }
    void setCol(int col) { m_col = col; }

signals:
    void playerChanged(int oldplayer, int newplayer);

public slots:
    void setPlayer(int player);

private:
    int m_player;
    int m_row;
    int m_col;
};

#endif // CELL_H
