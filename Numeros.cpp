# CifrasYLetras
Dados unos números y un resultado a conseguir, con la combinacion de los números te muestra por pantalla las distintas formas de rcombinarlos para obtener el resultado (en caso de tener solución)
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
struct solucion{
  vector<int> elementos;
  vector<vector<int> > operaciones;
  vector<char> operando;
};

int suma(int a, int b){
  return a+b;
}

int resta(int a, int b){
  return a-b;
}

bool restaPosible(int a, int b){
  bool posible=true;
  if(a<=b)
    posible=false;
  return posible;
}

int multiplicacion(int a, int b){
  return a*b;
}

int division(int a, int b){
  return a/b;
}

bool divisionPosible(int a, int b){
  bool posible=false;
  if(a>b)
    if(a%b==0)    posible=true;
  return posible;
}

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

bool esta(vector<int> v, int result){
  bool esta=false;
  for(int i=0; i<v.size() and !esta; i++)
    if(v[i]==result)   esta=true;
  return esta;
}

bool esta2(vector <vector <int> > v, int result){
  bool esta2=false;
  for(int i=0; i<v.size() and !esta2; i++)
    if(esta(v[i],result))    esta2=true;
  return esta2;
}

void mostrar(solucion v){
  for(int i=0; i<v.operaciones.size(); i++)
    cout << v.operaciones[i][0] << v.operando[i]<< v.operaciones[i][1] << " = "<< v.operaciones[i][2] << endl;
  cout << endl;
}

void operar(solucion aux, vector <solucion> &acumulador, char oper, int i, int j){
  int operacion;
  vector <int> op;
  if(oper=='+')     operacion=suma(aux.elementos[i],aux.elementos[j]);
  if(oper=='-')     operacion=resta(aux.elementos[i],aux.elementos[j]);
  if(oper=='x')     operacion=multiplicacion(aux.elementos[i],aux.elementos[j]);
  if(oper=='/')     operacion=division(aux.elementos[i],aux.elementos[j]);
  aux.operando.push_back(oper);
  op.push_back(aux.elementos[i]);
  op.push_back(aux.elementos[j]);
  op.push_back(operacion);
  borrar(aux.elementos,aux.elementos[i],aux.elementos[j]);
  aux.elementos.push_back(operacion);
  aux.operaciones.push_back(op);
  acumulador.push_back(aux);
}

void cyl(vector <solucion > grupo, vector <solucion > acumulador, int resultado, int prof){
  if(grupo[0].elementos.size()==prof){
    for(int i=0; i<grupo.size();i++){
      if(esta(grupo[i].elementos,resultado))      mostrar(grupo[i]);
    }
  }
  else{
    for(int a=0; a<grupo.size();a++){
      for(int i=0; i<grupo[0].elementos.size(); i++){
        for(int j=i+1; j<grupo[0].elementos.size(); j++){
          operar(grupo[a],acumulador,'+',i,j);
          operar(grupo[a],acumulador,'x',i,j);
        }
      }
      for(int i=0; i<grupo[0].elementos.size(); i++){
        for(int j=0; j<grupo[0].elementos.size(); j++){
          if(i!=j){
            if(restaPosible(grupo[a].elementos[i],grupo[a].elementos[j]))
              operar(grupo[a], acumulador, '-',i,j);
            if(divisionPosible(grupo[a].elementos[i],grupo[a].elementos[j]))
              operar(grupo[a], acumulador, '/',i,j);
          }
        }
      }
    }
    grupo.clear();
    grupo=acumulador;
    acumulador.clear();
    cyl(grupo, acumulador, resultado, prof);
  }
}

int main(){
  vector<solucion> grupo, acumulador;
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

  grupo.push_back(v);
  for(int i=v.elementos.size()-1; i>0; i--){
    cout << "CON " << v.elementos.size()-i << " OPERACIONES:" << endl;
    cout << "_____________________" << endl;
    cyl(grupo,acumulador,resultado,i);
  }
}
