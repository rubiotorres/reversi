#include "Cell.h"

Cell::Cell(QWidget *parent)
    : QPushButton(parent),
      m_player(0), m_row(0), m_col(0) {
}

Cell::~Cell() {
}

void Cell::setPlayer(int player) {
    if (player != m_player) {
        int oldplayer = m_player;
        m_player = player;

        switch (m_player) {
            case 0:
                this->setIcon(QPixmap());
                break;
            case 1:
                this->setIcon(QPixmap(":/red"));
                break;
            case 2:
                this->setIcon(QPixmap(":/blue"));
                break;
            default:
                Q_UNREACHABLE();
                break;
        }

        emit playerChanged(oldplayer, m_player);
    }
}
