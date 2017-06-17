#include <cstdio>
#include <cstdlib>
#include <iostream>

class Grafo{

    static bool x;



    int _n;
    int _m;
    int m_max;
    int vecino;



    friend void print(Grafo &);
    bool *v;
    int f(int , int);

public:

    int mar[6];
    Grafo(int);
    //int vecinos[5];
    //int vecindad;

     // ~ Falta destructor

      bool &edge(int, int) ;

      int m() const;
      int n() const;

      bool breadthFirstSearch(int, int, Grafo &);
      bool buscarMarcado(int);
      bool Vecindad(int, Grafo &); //antes era bool y regresaba un tru si si era vecino;
      void calcularVecindad(int, Grafo &);
      //int sizeVecindad(){return vecindad;}
};

 void print(Grafo &);

 class node{

    int _data;
    node *_siguiente;

public:

    node(int x):_data(x){_siguiente = NULL;}
    int dato(){return _data;}
    node *apuntador(node *_a, node *_b){return _a->_siguiente = _b;}
    node *siguiente(node *_a){return _a ->_siguiente;}
 };

 class Cola{

    node *_frente;
    int s;

public:
    Cola(){_frente = NULL; s = 0;}
    void enqueue(int);
    int dequeue();
    bool Vacia(){return s == 0 ? true : false;}
    int size(){return s;}
    void mostrar();
    node *frente(node *_a){return _frente = _a;}
	node *nodeFrente(){return _frente;}

 };

 void Cola::enqueue(int x){

     node *nuevo = new node(x);

    if(Vacia()){
        frente(nuevo);
        s++;
    }
    else{
            node *actual = nodeFrente();
        while(actual ->siguiente(actual) != NULL){
            actual = actual->siguiente(actual);
        }
        actual ->apuntador(actual, nuevo);
    }
 }

 int Cola::dequeue(){

    if(nodeFrente() == NULL)return -1;
    int valor;
    node *aux = nodeFrente();
    valor = nodeFrente()->dato();
   frente(aux->siguiente(aux));
    --s;
    return valor;
 }
 Cola Vecinos;

 void Cola::mostrar()
{
	node *actual = nodeFrente();
	while(actual != NULL)
	{
		printf("%i ", actual->dato());
		actual = actual->siguiente(actual);
	}
	puts("");
}

  bool Grafo::x = false;

    int Grafo::f(int u, int v){
      if(u== v)return 0;

      if(v>u){

        int aux = v;
        v =u;
        u = aux;

      }

      return (((u -1) * (u -2))/ 2) + v+1;

      }


      Grafo::Grafo(int n): _n(n){
        // _n = n;
        m_max = _n * (_n-1)/2;

        v = new bool[m_max];

       for(int i = 0; i < m_max; i++) v[i]= false;

      }


      bool &Grafo::edge(int i, int j){//devuelve una referencia
        if(i < 1 || i > _n || j < 1 || j > _n || j == i){

           printf("[Grafo]: bad index \n");
            return x;
        }
        return v[f(i, j)];
      }


      int Grafo::n()const{return _n;}
      int Grafo::m() const{return _m;}


        void print(Grafo &g){

            for(int i = 2; i <= g._n; i++){
                   // g.v[i] = false;
                for(int j = 1; j < i; j++){
                    printf("[%i:%i] %i\n", i, j, g.v[g.f(i,j)]);
                    //printf("[%i:%i] %i\n", i, j, g.edge(i,j));
                }

            }
            }

bool Grafo::buscarMarcado(int x){

    for(int i = 0; i < 6; i++){
        if(mar[i] == x){
                //printf("El numero ya estaba marcado: %i \n", x);
            return true;
        }
    }
    //printf("El numero no estaba marcado: %i\n", x);
    return false;
}
void Grafo::calcularVecindad(int u, Grafo &g){

   for(int j = 1; j <= 6;){
    if(g.v[f(u, j)] && !buscarMarcado(j)){
    Vecinos.enqueue(j);
    j++;
    }
    else{
        j++;
    }
   }

}
bool Grafo::Vecindad(int x, Grafo &g){

    for(int j = 1; j <= n();){
            //printf("%i se busca que sea vecino\n", j);
        if(g.v[f(x, j)] && !buscarMarcado(j)){
                vecino = j;
               // vecindad ++;
                //printf("%i si es vecino:\n", vecino);
            return true;
        }else{
        j++;
        }
    }
    //printf("%i no tiene vecinos disponibles");
   return false;
    //return vecindad;

}

bool Grafo::breadthFirstSearch(int source, int target, Grafo &g){

    Cola cola;
    int i = 0;
    int u;
    node *actual;

    cola.enqueue(source);
    mar[i] = source;
    i++;
    while (!cola.Vacia()){
        u = cola.dequeue();
        calcularVecindad(u, g);

        for(int j = 0; j <= Vecinos.size();){
           actual = Vecinos.nodeFrente();
        if(actual->dato() == target){
            return true;
        }
        cola.enqueue(actual->dato());
        mar[i] = actual->dato();
        i++;
        j++;
        Vecinos.dequeue();
        }

    }
    return false;
}


int main(){

    Grafo g(6);
    int sour, tar;

    g.edge(1, 3) = true;
    g.edge(1, 6) = true;
    g.edge(2, 3) = true;
    g.edge(2, 4) = true;
    g.edge(2, 5) = true;
    g.edge(5, 3) = true;
    g.edge(4, 5) = true;
    g.edge(4, 6) = true;
    g.edge(6, 5) = true;

    print(g);

    printf("comienza Busqueda en amplitud\n");
    printf("Source: \n");
    scanf("%i", &sour);
    printf("Target: \n");
    scanf("%i", &tar);
    g.breadthFirstSearch(sour, tar, g);

    return 0;
}
