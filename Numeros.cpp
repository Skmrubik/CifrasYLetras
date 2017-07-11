# CifrasYLetras
Dados unos números y un resultado a conseguir, con la combinacion de los números te muestra por pantalla las distintas formas de rcombinarlos para obtener el resultado (en caso de tener solución)
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
static int cont=0;
struct solucion{
  vector<int> elementos;    //elementos disponibles para realizar operaciones
  vector<vector<int> > operaciones; //tripletas correspondientes a las operaciones hasta llegar a la solucion
  vector<char> operando;    //vector de los operadores en orden
};

bool restaPosible(int a, int b){
  bool posible=true;
  if(a<=b)
    posible=false;
  return posible;
}

bool divisionPosible(int a, int b){
  bool posible=false;
  if(a>b)
    if(a%b==0)    posible=true;
  return posible;
}
//En el vector v busca los enteros a y b y los borra
void borrar(vector<int> &v,int a, int b){
  int i=0, tam=v.size();
  bool encA=false, encB=false;
  while(i<tam){
    if(v[i]==a and !encA){
      v.erase(v.begin()+i);
      encA=true;
      tam--;
    }
    else if(v[i]==b and !encB){
      v.erase(v.begin()+i);
      encB=true;
      tam--;
    }
    else
      i++;
  }
}
//Esta el entero result en el vector v?
bool esta(vector<int> v, int result){
  bool esta=false;
  for(int i=0; i<v.size() and !esta; i++)
    if(v[i]==result)   esta=true;
  return esta;
}

void mostrar(solucion v){
  for(int i=0; i<v.operaciones.size(); i++)
    cout << v.operaciones[i][0] << v.operando[i]<< v.operaciones[i][1] << " = "<< v.operaciones[i][2] << endl;
  cout << endl;
}
//Funcion para evitar la repetición de código en la funcion cyl
solucion codigo(solucion sol, char oper, int i, int j){
  solucion s=sol;
  int operacion;
  if(oper == '+')   operacion=s.elementos[i]+s.elementos[j];
  if(oper == '-')   operacion=s.elementos[i]-s.elementos[j];
  if(oper == 'x')   operacion=s.elementos[i]*s.elementos[j];
  if(oper == '/')   operacion=s.elementos[i]/s.elementos[j];
  vector<int> op;
  op.push_back(s.elementos[i]);
  op.push_back(s.elementos[j]);
  op.push_back(operacion);
  s.operaciones.push_back(op);
  s.operando.push_back(oper);
  borrar(s.elementos, s.elementos[i], s.elementos[j]);
  s.elementos.push_back(operacion);
  return s;
}
//Devuelve todas las soluciones posibles
void cyl(solucion sol, int resultado, int tam, vector<int> el){
  if(tam==1 ){
    if(sol.elementos[0]==resultado){
      mostrar(sol);
      cont++;
    }
  }
  else if(esta(sol.elementos, resultado)){
    mostrar(sol);
    cont++;
  }
  else{
    int operacion;
    solucion s;
    for(int i=0; i<tam; i++){
      for(int j=i+1; j<tam;j++){
        s=codigo(sol,'+',i,j); //SUMA
        cyl(s,resultado,tam-1,el);
        s=codigo(sol,'x',i,j); //MULTIPLICACION
        cyl(s,resultado,tam-1,el);
      }
    }
    for(int i=0; i<tam; i++){
      for(int j=0; j<tam;j++){
        if(i!=j){
          if(restaPosible(sol.elementos[i], sol.elementos[j])){
            s=codigo(sol,'-',i,j);  //RESTA
            cyl(s,resultado,tam-1,el);
          }
          if(divisionPosible(sol.elementos[i], sol.elementos[j])){
            s=codigo(sol,'/',i,j);  //DIVISION
            cyl(s,resultado,tam-1,el);
          }
        }
      }
    }
  }
}
//Devuelve una solucion para cada N numero de operandos
void cyl(solucion sol, int resultado, int tam, vector<int> el, vector <bool> &rep){
  if(esta(sol.elementos, resultado) and !rep[tam]){
    rep[tam]=true;
    cout << "CON " << el.size()-tam << " OPERACIONES: " << endl;
    cout << "_____________________________________" << endl;
    mostrar(sol);
    cont++;
  }
  else{
    int operacion;
    solucion s;
    for(int i=0; i<tam; i++){
      for(int j=i+1; j<tam;j++){
        s=codigo(sol,'+',i,j); //SUMA
        cyl(s,resultado,tam-1,el,rep);
        s=codigo(sol,'x',i,j); //MULTIPLICACION
        cyl(s,resultado,tam-1,el,rep);
      }
    }
    for(int i=0; i<tam; i++){
      for(int j=0; j<tam;j++){
        if(i!=j){
          if(restaPosible(sol.elementos[i], sol.elementos[j])){
            s=codigo(sol,'-',i,j);  //RESTA
            cyl(s,resultado,tam-1,el,rep);
          }
          if(divisionPosible(sol.elementos[i], sol.elementos[j])){
            s=codigo(sol,'/',i,j);  //DIVISION
            cyl(s,resultado,tam-1,el,rep);
          }
        }
      }
    }
  }
}
int main(){
  solucion v;
  int num=-1, resultado;
  vector <bool> rep;
  int modo;
  system("clear");
  cout << "MODO DE USO: " << endl;
  cout << "Quieres que aparezcan (selecciona 1 o 2):" << endl;
  cout << "1. Todas las soluciones posibles" << endl;
  cout << "2. Solo una solucion para cada numero N de operaciones en el calculo de la solucion " << endl;
  cin >> modo;
  while(num!=0){
    system("clear");
    cout << "NUMEROS A OPERAR" << endl;
    for(int i=0; i<v.elementos.size(); i++)
      cout << "| " << v.elementos[i] << " ";
    cout << "|" << endl;
    cout << "Introduce un número y pulsa enter (para dejar de meter numeros introduce 0)" << endl;
    cin >> num;
    if(num!=0)
      v.elementos.push_back(num);
  }
  for(int i=0; i<v.elementos.size(); i++){
    rep.push_back(false);
  }
  cout << "Ahora introduce el resultado a conseguir" << endl;
  cin >> resultado;
  if(modo ==1)    cyl(v,resultado,v.elementos.size(),v.elementos);
  if(modo ==2)    cyl(v,resultado,v.elementos.size(),v.elementos,rep);
  cout << "SOLUCIONES ENCONTRADAS: " << cont << endl;
}
