#include "verificalados.h"
bool Reversi::horizontalneg(Cell *cell){
    if(m_cells[cell->row()][cell->col()-1]->player()==player||
       m_cells[cell->row()][cell->col()-1]->player()==0){
        return false;
    }
    for(int j=cell->col()-2;j>=0;j--){
        if(m_cells[cell->row()][j]->player()==player){
            for(int i=cell->col()-1;i>j;i--){
                m_cells[cell->row()][i]->setPlayer(player);
                return true;
            }
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
                return true;
            }
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
            for(int i=cell->row()-1;i>j;i--){
                m_cells[i][cell->col()]->setPlayer(player);
                return true;
            }
        }
    }
    return false;

}
bool Reversi::diagdirneg(Cell *cell){
    if(m_cells[cell->row()-1][cell->col()+1]->player()==player||
       m_cells[cell->row()-1][cell->col()+1]->player()==0){
        return false;
    }
    for(int j=cell->row()-2, k=cell->col()+2;j>=0;j++,k--){
        if(m_cells[j][k]->player()==player){
            for(int i=cell->row()-1, l=cell->col()+1;i>j;i--,l++){
                m_cells[i][l]->setPlayer(player);
                return true;
            }
        }
    }
    return false;

}
