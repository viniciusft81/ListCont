// implemente aqui sua função

#include "questao.h"

bool decrementa(list<int> & lcont) {

    if(lcont.empty()) return false;

    for(auto & num: lcont){

        if(num != 0) num--;
    }
    return true;

}