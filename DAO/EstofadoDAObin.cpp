#include "EstofadoDAObin.h"
#include <iostream>
#include <string.h>
EstofadoDAObin::EstofadoDAObin() {

}
EstofadoDAObin::~EstofadoDAObin() {
    fechar();
}

/*Métodos privados*/

bool EstofadoDAObin::gravar(sEstofado estofado, const char* nome) {

    if(abrir(nome, ios::app)){
            arquivo.write((const char*)(&estofado), sizeof(sEstofado));
            fechar();
            return true;
        }
    fechar();
    return false;
}

/*Métodos publicos*/

bool EstofadoDAObin::abrir(const char* nome, std::ios_base::openmode modo){

    arquivo.open(nome, modo);
    if(!arquivo.is_open() || !arquivo.good()) {
      return false;
    }

    return true;
}

bool EstofadoDAObin::gravar(const char* nome, MEstofado* estofado) {
    sEstofado m;

    m.id = estofado->getId();
    m.ds = estofado->getDataSaida().getDia();
    m.ms = estofado->getDataSaida().getMes();
    m.as = estofado->getDataSaida().getAno();
    m.de = estofado->getDataEntrada().getDia();
    m.me = estofado->getDataEntrada().getDia();
    m.ae = estofado->getDataEntrada().getDia();
    strcpy(m.nome, (estofado->getNome()).c_str());
    strcpy(m.fabricante, (estofado->getFabricante()).c_str());
    strcpy(m.cor, (estofado->getCor()).c_str());
    m.largura = estofado->getLargura();
    m.altura = estofado->getAltura();
    m.profundidade = estofado->getProfundidade();
    m.custo = estofado->getCusto();
    m.preco = estofado->getPreco();
    m.vendida = estofado->getStatus();
    m.lugares = estofado->getLugares();

    return gravar(m, nome);
}

list<MEstofado*> EstofadoDAObin::getListaEstofados(const char* nome) {
    list<MEstofado*> lista;
    sEstofado m;
  
    if(abrir(nome, ios::in)){
        while(arquivo && !arquivo.eof()) {
            arquivo.read((char *)(&m), sizeof(sEstofado));
            MEstofado* estofado = new MEstofado(m.id, m.nome, m.fabricante, m.cor, m.largura, m.altura, m.profundidade, m.custo, m.preco, m.lugares);
            estofado->setDataEntrada(m.de,m.me,m.ae);
            estofado->setDataSaida(m.ds,m.ms,m.as);
            lista.push_back(estofado);
        }        
    }

    fechar();
    return lista;
}


void EstofadoDAObin::fechar(){
    arquivo.close();
}