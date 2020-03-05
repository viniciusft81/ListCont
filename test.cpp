//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;

class TesteQuestao : public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }

    int gen_lista(list<int> & q, int min, int max) {
        int n, maior = 0;

        n = 5 + (rand() % 10);
        while (n-- > 0) {
            int x = min + (rand() % (max - min));
            if (x > maior) maior = x;
            q.push_back(x);
        }
        return maior;
    }

    bool meu_decrementa(list<int> & q) {
        bool ok = false;

        for (auto & x: q) {
            if (x > 0) {
                ok = true;
                x--;
            }
        }
        return ok;
    }

    string ltos(list<int> & l) {
        ostringstream os;

        for (auto & x: l) os << x << ',';
        return os.str();
    }
};

string randstr(int len) {
    string r;

    while (len-- > 0) {
        char c = 'a' + (rand() % 26);
        r += c;
    }
    return r;
}

TEST_F(TesteQuestao, Vazia) {
    try {
        list<int> q;

        bool ok = decrementa(q);

        if (q.size() > 0) {
            FAIL() << "lista inicialmente vazia tem tamanho maior que 0 após decrementa";
            return;
        }

        if (ok) {
            FAIL() << "decrementa retornou true, mas lista está vazia";
        }

    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

TEST_F(TesteQuestao, Normal) {
    try {
        list<int> q, aux, old;

        int num = gen_lista(q, 1, 30);
        aux = q;
        old = q;

        bool ok = decrementa(q);

        if (q.size() != aux.size()) {
            FAIL() << "lista teve seu size modificado após decrementa";
            return;
        }

        bool mok = meu_decrementa(aux);

        if (not (q == aux)) {
            FAIL() << "após decrementa, contadores não estão com os valores esperados:"
             << "esperado: "+ltos(aux)
             << "obtido: "+ltos(q);
            return;
        }

        if (ok != mok) {
            if (ok) FAIL() << "decrementa retornou true, mas deveria retornar false, pois lista estava assim: "+ltos(old);
            else FAIL() << "decrementa retornou false, mas deveria retornar true, pois lista estava assim: "+ltos(old);
        }
    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

TEST_F(TesteQuestao, Zeros) {
    try {
        list<int> q, aux, old;

        int num = gen_lista(q, 1, 30);
        q.push_front(0);
        q.push_front(0);
        q.push_front(0);

        vector<int> v(q.begin(), q.end());

        random_shuffle(v.begin(), v.end());
        q.clear();
        q.insert(q.begin(), v.begin(), v.end());

        aux = q;
        old = q;

        bool ok = decrementa(q);

        if (q.size() != aux.size()) {
            FAIL() << "lista teve seu size modificado após decrementa";
            return;
        }

        bool mok = meu_decrementa(aux);

        if (not (q == aux)) {
            FAIL() << "após decrementa, contadores não estão com os valores esperados:"
             << ", esperado: "+ltos(aux)
             << ", obtido: "+ltos(q);
            return;
        }

        if (ok != mok) {
            if (ok) FAIL() << "decrementa retornou true, mas deveria retornar false, pois lista estava assim: "+ltos(old);
            else FAIL() << "decrementa retornou false, mas deveria retornar true, pois lista estava assim: "+ltos(old);
        }
    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

TEST_F(TesteQuestao, Maximo) {
    try {
        list<int> q, aux;

        int num = gen_lista(q, 1, 30);
        q.push_front(0);
        q.push_front(0);
        vector<int> v(q.begin(), q.end());

        random_shuffle(v.begin(), v.end());
        q.clear();
        q.insert(q.begin(), v.begin(), v.end());
        aux = q;

        int n = 0, lim = num;
        while (decrementa(q) and lim) {
            lim--;
            n++;
        }

        if (n != num) {
            FAIL() << "o maior contador valia "+to_string(num)+", mas decrementa foi executado sucessivamente "+to_string(n)+" vezes antes de retornar false"
             << ", lista original: "+ltos(aux)
             << ", lista após decrementa ser chamado sucessivamente: "+ltos(q);
        }
    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}
