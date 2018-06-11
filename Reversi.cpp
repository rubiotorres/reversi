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
    if(cell->player()==0){
            if(verificalados(cell)){
                switch (player) {
                    case 1:
                        //cell->setPlayer(player);
                        player = 2;
                        break;

                    case 2:
                        //cell->setPlayer(player);
                        player = 1;
                        break;

                    default:
                        break;
                }
            }
        else{
           qDebug()  <<"Não permitido";
        }
    }
    qDebug() << "Play on ("
             << cell->row() << ", "
             << cell->col() << ")";
    if(!fimdejogo()){
        int vermelho=m_count[0];
        int azul=m_count[1];
        if(vermelho>azul){
            QMessageBox::warning(this, tr("Fim de jogo"),
                                 tr("Parabens!!!\nvitoria do jogador Vermelho."));
        }
        else if(vermelho<azul){
            QMessageBox::warning(this, tr("Fim de jogo"), tr("Parabens!!!\n"
                                                                     " vitoria do jogador Azul."));
        }
        else if(vermelho==azul){
            QMessageBox::warning(this, tr("Fim de jogo"), tr("Empate!!!\n"
                                                                     " Os jogadores possuem os mesmos pontos."));
        }

        reset();
    }

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
    player=1;

}

void Reversi::showAbout() {
    QMessageBox::information(this, tr("Sobre"), tr("Reversi\n\nRenan Siman Claudino - renansiman22@gmail.com\nRubio Torres Castro Viana - rubiotorres15@gmail.com"));
}
bool Reversi::horizontalpos(int coluna,int linha){
    if(coluna<7){
            if(m_cells[linha][coluna+1]->player()==player||
               m_cells[linha][coluna+1]->player()==0){
                return false;
            }
        for(int j=coluna+2;j<8;j++){
            if(m_cells[linha][j]->player()==player){
                for(int i=coluna;i<j;i++){
                    m_cells[linha][i]->setPlayer(player);
                }
                qDebug()<<"HP";
                return true;


            }

            if(m_cells[linha][j]->player()==0){
                return false;
            }
        }
    }
    return false;

}
bool Reversi::horizontalneg(int coluna,int linha){
    if(coluna>0){
        if(m_cells[linha][coluna-1]->player()==player||
            m_cells[linha][coluna-1]->player()==0){
              return false;
         }
        for(int j=coluna-2;j>=0;j--){
            if(m_cells[linha][j]->player()==player){
                for(int i=coluna;i>j;i--){
                    m_cells[linha][i]->setPlayer(player);
                }
                qDebug()<<"HN";
                return true;


            }

            if(m_cells[linha][j]->player()==0){
                return false;
            }
        }
     }
     return false;
}

bool Reversi::verticalpos(int coluna,int linha){
    qDebug()<<"VP";

    if(linha<7){
        if(m_cells[linha+1][coluna]->player()==player||
           m_cells[linha+1][coluna]->player()==0){
            return false;
        }
    }
    for(int j=linha+2;j<8;j++){
        if(m_cells[j][coluna]->player()==player){
            for(int i=linha;i<j;i++){
                m_cells[i][coluna]->setPlayer(player);
            }
             return true;

        }

        if(m_cells[j][coluna]->player()==0){
            return false;
        }
    }
    return false;
}

bool Reversi::verticalneg(int coluna,int linha){
    qDebug()<<"VN";

    if(linha>0){
            if(m_cells[linha-1][coluna]->player()==player||
               m_cells[linha-1][coluna]->player()==0){
                return false;
            }

        for(int j=linha-2;j>=0;j--){
            qDebug()  <<"J:" <<j;
            if(m_cells[j][coluna]->player()==player){
                for(int i=linha;i>j;i--){
                    m_cells[i][coluna]->setPlayer(player);
                }
            return true;

            }

            if(m_cells[j][coluna]->player()==0){
                return false;
            }
        }
    }
    return false;

}
bool Reversi::diagesqneg(int coluna,int linha){
    qDebug()<<"DEN";
    if(linha>0&&coluna<7){
            if(m_cells[linha-1][coluna+1]->player()==player||
               m_cells[linha-1][coluna+1]->player()==0){
                return false;
            }

        for(int j=linha-2, k=coluna+2;j>=0&&k<8;j--,k++){
            if(m_cells[j][k]->player()==player){
                for(int i=linha, l=coluna;i>j;i--,l++){
                    m_cells[i][l]->setPlayer(player);
                }
                return true;
            }

            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;

}
bool Reversi::diagesqpos(int coluna,int linha){
    qDebug()<<"DEP";

    if(linha<7&&coluna<7){
        qDebug()<<"linha+1:"<<linha+1;
        qDebug()<<"coluna+1"<<coluna+1;
            if(m_cells[linha+1][coluna+1]->player()==player||
               m_cells[linha+1][coluna+1]->player()==0){
                return false;
            }
        for(int j=linha+2, k=coluna+2;j<8&&k<8;j++,k++){
            qDebug()<<"J"<<j;
            qDebug()<<"K"<<k;


            if(m_cells[j][k]->player()==player){
                for(int i=linha, l=coluna;i<j;i++,l++){
                    qDebug()<<"I"<<i;
                    qDebug()<<"L"<<l;
                    m_cells[i][l]->setPlayer(player);
                }
                return true;
            }

            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }

    return false;

}


bool Reversi::diagdirneg(int coluna,int linha){
    qDebug()<<"DDN";

    if(coluna>0&&linha>0){
            if(m_cells[linha-1][coluna-1]->player()==player||
               m_cells[linha-1][coluna-1]->player()==0){
                return false;
            }

        for(int j=linha-2, k=coluna-2;j>=0&&k>=0;j--,k--){
            if(m_cells[j][k]->player()==player){
                for(int i=linha, l=coluna;i>j;i--,l--){
                    m_cells[i][l]->setPlayer(player);
                }
                return true;
            }

            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;

}
bool Reversi::diagdirpos(int coluna,int linha){
    qDebug()<<"DDP";

    if(linha<7&&coluna>0){
            if(m_cells[linha+1][coluna-1]->player()==player||
               m_cells[linha+1][coluna-1]->player()==0){
                return false;
            }

        for(int j=linha+2, k=coluna-2;j<8&& k>=0;j++,k--){
            if(m_cells[j][k]->player()==player){
                for(int i=linha, l=coluna;i<j;i++,l--){
                    m_cells[i][l]->setPlayer(player);
                }
                return true;
            }
            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;

}
bool Reversi::verificalados(Cell* cell){
    int coluna=cell->col();
    int linha=cell->row();
    int verifica=0;
    qDebug() << player;

    if(this->verticalneg(coluna,linha)){
        verifica++;
    }
    if(this->verticalpos(coluna,linha)){
        verifica++;
    }
    if(this->horizontalneg(coluna,linha)){
        verifica++;
    }
    if(this->horizontalpos(coluna,linha)){
        verifica++;
    }
    if(this->diagdirneg(coluna,linha)){
        verifica++;
    }
    if(this->diagdirpos(coluna,linha)){
        verifica++;
    }
    if(this->diagesqneg(coluna,linha)){
        verifica++;
    }
    if(this->diagesqpos(coluna,linha)){
        verifica++;
    }
    if(verifica>0){
        return true;
    }
    return false;
}

bool Reversi::verificafim(Cell* cell){
    int coluna=cell->col();
    int linha=cell->row();
    int verifica=0;

    if(this->verticaln(coluna,linha)){
        verifica++;
    }
    if(this->verticalp(coluna,linha)){
        verifica++;
    }
    if(this->horizontaln(coluna,linha)){
        verifica++;
    }
    if(this->horizontalp(coluna,linha)){
        verifica++;
    }
    if(this->diagdirn(coluna,linha)){
        verifica++;
    }
    if(this->diagdirp(coluna,linha)){
        verifica++;
    }
    if(this->diagesqn(coluna,linha)){
        verifica++;
    }
    if(this->diagesqp(coluna,linha)){
        verifica++;
    }
    if(verifica>0){
        return true;
    }
    return false;
}
bool Reversi::horizontalp(int coluna,int linha){
    if(coluna<7){
            if(m_cells[linha][coluna+1]->player()==player||
               m_cells[linha][coluna+1]->player()==0){
                return false;
            }
        for(int j=coluna+2;j<8;j++){
            if(m_cells[linha][j]->player()==player){
                return true;
            }
            if(m_cells[linha][j]->player()==0){
                return false;
            }
        }
    }
    return false;
}
bool Reversi::horizontaln(int coluna,int linha){
    if(coluna>0){
        if(m_cells[linha][coluna-1]->player()==player||
            m_cells[linha][coluna-1]->player()==0){
              return false;
         }
        for(int j=coluna-2;j>=0;j--){
            if(m_cells[linha][j]->player()==player){
                return true;
            }
            if(m_cells[linha][j]->player()==0){
                return false;
            }
        }
     }
     return false;
}
bool Reversi::verticalp(int coluna,int linha){
    if(linha<7){
        if(m_cells[linha+1][coluna]->player()==player||
           m_cells[linha+1][coluna]->player()==0){
            return false;
        }
    }
    for(int j=linha+2;j<8;j++){
        if(m_cells[j][coluna]->player()==player){
             return true;
        }
        if(m_cells[j][coluna]->player()==0){
            return false;
        }
    }
    return false;
}

bool Reversi::verticaln(int coluna,int linha){
    if(linha>0){
            if(m_cells[linha-1][coluna]->player()==player||
               m_cells[linha-1][coluna]->player()==0){
                return false;
            }
        for(int j=linha-2;j>=0;j--){
            qDebug()  <<"J:" <<j;
            if(m_cells[j][coluna]->player()==player){
                 return true;
            }
            if(m_cells[j][coluna]->player()==0){
                return false;
            }
        }
    }
    return false;
}
bool Reversi::diagesqn(int coluna,int linha){
    if(linha>0&&coluna<7){
            if(m_cells[linha-1][coluna+1]->player()==player||
               m_cells[linha-1][coluna+1]->player()==0){
                return false;
            }
        for(int j=linha-2, k=coluna+2;j>=0&&k<8;j--,k++){
            if(m_cells[j][k]->player()==player){
                return true;
            }
            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;
}
bool Reversi::diagesqp(int coluna,int linha){
    if(linha<7&&coluna<7){
            if(m_cells[linha+1][coluna+1]->player()==player||
               m_cells[linha+1][coluna+1]->player()==0){
                return false;
            }
        for(int j=linha+2, k=coluna+2;j<8&&k<8;j++,k++){
            if(m_cells[j][k]->player()==player){
                return true;
            }
            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;
}


bool Reversi::diagdirn(int coluna,int linha){
    if(coluna>0&&linha>0){
            if(m_cells[linha-1][coluna-1]->player()==player||
               m_cells[linha-1][coluna-1]->player()==0){
                return false;
            }
        for(int j=linha-2, k=coluna-2;j>=0&&k>=0;j--,k--){
            if(m_cells[j][k]->player()==player){
                return true;
            }
            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;
}
bool Reversi::diagdirp(int coluna,int linha){
    if(linha<7&&coluna>0){
            if(m_cells[linha+1][coluna-1]->player()==player||
               m_cells[linha+1][coluna-1]->player()==0){
                return false;
            }
        for(int j=linha+2, k=coluna-2;j<8&& k>=0;j++,k--){
            if(m_cells[j][k]->player()==player){
                return true;
            }
            if(m_cells[j][k]->player()==0){
                return false;
            }
        }
    }
    return false;
}
bool Reversi::fimdejogo(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(m_cells[i][j]->player()==0){
                if(this->verificafim(m_cells[i][j])){
                    return true;
                }
            }

        }
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


