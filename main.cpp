#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

struct Visitados {
    int posI;
    int posJ;
};

void imprime_matriz(int** matriz, int vertices){
    int cont=0;
    cout<<"  ";
    for(int i = 0; i < vertices; i++){
        cout<<(i+1)<<"   ";
    }
    cout<<endl;
    for(int i = 0; i < vertices; i++) {
        cout<<(i+1)<<" ";
        for(int j = 0; j < vertices; j++) {
            if(matriz[i][j] != 1) {
                matriz[i][j] = 0;
            }
            cout << matriz[i][j];
            if(j == vertices-1) {
                cout << endl;
                cont++;
                continue;
            }
            cout << " - ";
        }
    }
}

int dfs(int** matriz, int vertices, int i, int visitados[]){
    visitados[i]=1;
    cout << "visitou: " << i+1 << "\n";
    for(int j=0; j<vertices; j++){
        if(!visitados[j]&&matriz[i][j]==1){
            dfs(matriz, vertices, j, visitados);
        }
    }
}

int** montar_matriz(int** matriz, bool dirigido){
    int val1 = 0, val2 = 0, cont = 1;
    bool seletor = true;

    cout << "Digite as conexões, cada número seguido de um ENTER." << endl;
    cout << "Digite um valor negativo para parar." << endl;

    while(seletor) {
        if(val1 < 0 || val2 < 0) {
            break;
        }

        cout << "Conexão " << cont << ": ";
        cin >> val1; cin >> val2; cout << endl;

        if(val1 < 0 || val2 < 0) {
            break;
        }

        if(dirigido) {
            matriz[val1][val2] = 1;
            cont++;
            continue;
        }

        matriz[val1][val2] = 1;
        matriz[val2][val1] = 1;

        cont++;
    }
    return matriz;
}

void menu(int** matriz, int vertices){

    int escolha=1;
    int visitados[vertices];
    while(escolha!=0){
        sleep(3);
        cout << "-----------------------------" << endl;
        cout << "imprimir(1)" << endl;
        cout << "dfs(2)" << endl;
        cout << "bfs(3)" << endl;
        cout << "sair(0)" << endl;
        cout << "-----------------------------" << endl;
        cout << endl << endl;
        cin >> escolha;
        if(!isdigit(escolha)){
            if(escolha!=0){
                switch(escolha){
                    case 1:
                        imprime_matriz(matriz,vertices);
                        break;
                    case 2:
                        for(int i=0; i<vertices; i++){
                            visitados[i]=0;
                        }
                        for(int i = 0; i<vertices; i++){
                            if(visitados[i]!=1){
                                dfs(matriz, vertices, i, visitados);
                            }
                        }
                        break;
                    case 3:
                        break;
                }
            }
        }
    }


}

int main() {

    int vertices = 0;
    bool dirigido = false;

    cout << "Entre com o número de vértices: "; cin >> vertices; cout << endl;
    cout << "Grafo não dirigido - 0; Grafo dirigido - 1: "; cin >> dirigido; cout << endl;

    //01 // 02 // 23 // 13 // -10
    int** (matriz) = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        matriz[i] = new int[vertices];
    }

    matriz = montar_matriz(matriz, dirigido);

    menu(matriz, vertices);


    return 0;
}