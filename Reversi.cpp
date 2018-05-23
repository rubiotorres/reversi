#include "Reversi.h"
#include "ui_reversi.h"
#include <QMessageBox>
#include <QDebug>

Reversi::Reversi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reversi) {

    ui->setupUi(this);

    m_count[0] = 0;
    m_count[1] = 0;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Cell* cell = this->findChild<Cell*>(
                 QString("cell%1%2").arg(r).arg(c));
            Q_ASSERT(cell != 0);
            cell->setRow(r);
            cell->setCol(c);

            QObject::connect(
                cell,
                SIGNAL(clicked(bool)),
                this,
                SLOT(play())
            );

            QObject::connect(
                cell,
                SIGNAL(playerChanged(int,int)),
                this,
                SLOT(updateStatus(int,int))
            );

            m_cells[r][c] = cell;
        }
    }

    this->reset();

    QObject::connect(
            ui->actionNovo,
            SIGNAL(triggered(bool)),
            this,
            SLOT(reset())
    );

    QObject::connect(
            ui->actionSair,
            SIGNAL(triggered(bool)),
            qApp,
            SLOT(quit())
    );

    QObject::connect(
            ui->actionSobre,
            SIGNAL(triggered(bool)),
            this,
            SLOT(showAbout())
    );

    this->adjustSize();
    this->setFixedSize(this->size());
}

Reversi::~Reversi() {
    delete ui;
}

void Reversi::play() {
    Cell* cell = qobject_cast<Cell*>(QObject::sender());
    Q_ASSERT(cell != 0);
    if(cell->player()==0&&verificalados(cell)){
        switch (player) {
            case 1:
                cell->setPlayer(player);
                player = 2;
                break;

            case 2:
                cell->setPlayer(player);
                player = 1;
                break;

            default:
                break;
        }

    }
    else{
       qDebug()  <<"Não permitido";
    }

    qDebug() << "Play on ("
             << cell->row() << ", "
             << cell->col() << ")";
}

void Reversi::reset(){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            m_cells[i][j]->setPlayer(0);
        }
    }
    m_cells[3][3]->setPlayer(1);
    m_cells[3][4]->setPlayer(2);
    m_cells[4][3]->setPlayer(2);
    m_cells[4][4]->setPlayer(1);

}

void Reversi::showAbout() {
    QMessageBox::information(this, tr("Sobre"), tr("Reversi\n\nRenan Siman Claudino - renansiman22@gmail.com\nRubio Torres Castro Viana - rubiotorres15@gmail.com"));
}
bool Reversi::horizontalpos(Cell *cell){
    if(m_cells[cell->row()][cell->col()+1]->player()==player||
       m_cells[cell->row()][cell->col()+1]->player()==0){
        return false;
    }
    for(int j=cell->col()+2;j<8;j++){
        if(m_cells[cell->row()][j]->player()==player){
            for(int i=cell->col()+1;i<j;i++){
                m_cells[cell->row()][i]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}
bool Reversi::horizontalneg(Cell *cell){
    if(m_cells[cell->row()][cell->col()-1]->player()==player||
       m_cells[cell->row()][cell->col()-1]->player()==0){
        return false;
    }
    for(int j=cell->col()-2;j>=0;j--){
        if(m_cells[cell->row()][j]->player()==player){
            for(int i=cell->col()-1;i>j;i--){
                m_cells[cell->row()][i]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}

bool Reversi::verticalpos(Cell *cell){
    if(m_cells[cell->row()+1][cell->col()]->player()==player||
       m_cells[cell->row()+1][cell->col()]->player()==0){
        return false;
    }
    for(int j=cell->row()+2;j<8;j++){
        if(m_cells[j][cell->col()]->player()==player){
            for(int i=cell->row()+1;i<j;i++){
                m_cells[i][cell->col()]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}

bool Reversi::verticalneg(Cell *cell){
    if(m_cells[cell->row()-1][cell->col()]->player()==player||
       m_cells[cell->row()-1][cell->col()]->player()==0){
        return false;
    }
    for(int j=cell->row()-2;j>=0;j++){
        if(m_cells[j][cell->col()]->player()==player){
            for(int i=cell->row()-1;i>=j;i--){
                m_cells[i][cell->col()]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}
bool Reversi::diagesqneg(Cell *cell){
    if(m_cells[cell->row()-1][cell->col()+1]->player()==player||
       m_cells[cell->row()-1][cell->col()+1]->player()==0){
        return false;
    }
    for(int j=cell->row()-2, k=cell->col()+2;j>=0;j--,k++){
        if(m_cells[j][k]->player()==player){
            for(int i=cell->row()-1, l=cell->col()+1;i>j;i--,l++){
                m_cells[i][l]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}
bool Reversi::diagesqpos(Cell *cell){
    if(m_cells[cell->row()+1][cell->col()+1]->player()==player||
       m_cells[cell->row()+1][cell->col()+1]->player()==0){
        return false;
    }
    for(int j=cell->row()+2, k=cell->col()+2;j<8;j++,k++){
        if(m_cells[j][k]->player()==player){
            for(int i=cell->row()+1, l=cell->col()+1;i<j;i++,l++){
                m_cells[i][l]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}


bool Reversi::diagdirneg(Cell *cell){
    if(m_cells[cell->row()-1][cell->col()-1]->player()==player||
       m_cells[cell->row()-1][cell->col()-1]->player()==0){
        return false;
    }
    for(int j=cell->row()-2, k=cell->col()-2;j>=0;j--,k--){
        if(m_cells[j][k]->player()==player){
            for(int i=cell->row()-1, l=cell->col()-1;i>j;i--,l--){
                m_cells[i][l]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}
bool Reversi::diagdirpos(Cell *cell){
    if(m_cells[cell->row()+1][cell->col()-1]->player()==player||
       m_cells[cell->row()+1][cell->col()-1]->player()==0){
        return false;
    }
    for(int j=cell->row()+2, k=cell->col()-2;j<8;j++,k--){
        if(m_cells[j][k]->player()==player){
            for(int i=cell->row()+1, l=cell->col()-1;i<j;i++,l--){
                m_cells[i][l]->setPlayer(player);
            }
            return true;
        }
    }
    return false;

}
bool Reversi::verificalados(Cell* cell){
    int verifica=0;
    if(this->verticalneg(cell)){
        verifica++;
    }
    if(this->verticalpos(cell)){
        verifica++;
    }
    if(this->horizontalneg(cell)){
        verifica++;
    }
    if(this->horizontalpos(cell)){
        verifica++;
    }
    if(this->diagdirneg(cell)){
        verifica++;
    }
    if(this->diagdirpos(cell)){
        verifica++;
    }
    if(this->diagesqneg(cell)){
        verifica++;
    }
    if(this->diagesqpos(cell)){
        verifica++;
    }
    if(verifica>0){
        return true;
    }
    return false;
}
void Reversi::updateStatus(int oldplayer, int newplayer) {
    if(oldplayer > 0)
        m_count[oldplayer - 1]--;

    if(newplayer > 0)
        m_count[newplayer - 1]++;

    qDebug() << "Old Player: " << oldplayer;
    qDebug() << "New Player: " << newplayer;
    ui->statusBar->showMessage(QString("Vermelho: %1 Vs Azul: %2")
                               .arg(m_count[0])
                               .arg(m_count[1]));

}


