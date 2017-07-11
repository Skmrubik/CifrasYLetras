# CifrasYLetras
Dados unos números y un resultado a conseguir, con la combinacion de los números te muestra por pantalla las distintas formas de rcombinarlos para obtener el resultado (en caso de tener solución)
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

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
//La funcion encargada de ver que combinaciones de operaciones llegan al resultado
void cyl(solucion sol, int resultado, vector<int> el){
  if(sol.elementos.size()==1 ){
    if(sol.elementos[0]==resultado)           mostrar(sol);
  }
  else if(esta(sol.elementos, resultado))     mostrar(sol);
  else{
    solucion s;
    for(int i=0; i<sol.elementos.size(); i++){
      for(int j=i+1; j<sol.elementos.size();j++){
        if(i<j){
          s=codigo(sol,'+',i,j); //SUMA
          cyl(s,resultado,el);
          s=codigo(sol,'x',i,j); //MULTIPLICACION
          cyl(s,resultado,el);
        }
        if(i!=j){
          if(restaPosible(sol.elementos[i], sol.elementos[j])){
            s=codigo(sol,'-',i,j);  //RESTA
            cyl(s,resultado,el);
          }
          if(divisionPosible(sol.elementos[i], sol.elementos[j])){
            s=codigo(sol,'/',i,j);  //DIVISION
            cyl(s,resultado,el);
          }
        }
      }
    }
  }
}

int main(){
  solucion v;
  int num=-1, resultado;

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

  cout << "Ahora introduce el resultado a conseguir" << endl;
  cin >> resultado;
  cyl(v,resultado,v.elementos);
}
