#include <iostream>
using namespace std;

/*
    Definición matemática del factorial
        0! = 1
        1! = 1
        n! = n(n-1)!
*/

//Recursión por Posposición
int factorial(int n){
    if(n == 0) return 1;        //Condición de paro
    return n * factorial(n - 1);  //Llamada recursiva con trabajo pendiente
}
/*
    4*____      4*6=24
    3*____      3*2=6
    2*____      2*1=2
    1*____      1*1=1
    1
*/

//Recursión por Cola
int factorial_cola(int acc, int cnt, int n){ //Se usa un acumulador y un contador
    if(cnt == n) return acc * cnt;               //Condición de paro
    return factorial_cola(acc * cnt, cnt + 1, n);  //Llamada recursiva sin trabajo pendiente
}
/*
    acc     cont    n
     1       1      4
     1       2      4
     2       3      4
     6       4      4
     24
*/

//Fibonacci
int fibonacci(int n){
    if(n == 0 || n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
/*
    La ejecución de la función fibonacci, y la ejecución de toda función recursiva
    de manera natural provoca una estructura de árbol entre las distintas instancias
    en memoeria durante el proceso:

                                   fibonacci(3) ...
                                  /
                      fibonacci(4)
                     /            \
                    /              fibonacci(2) ...
        fibonacci(5)
                    \              fibonacci(2) ...
                     \            /
                      fibonacci(3)
                                  \
                                   fibonacci(1) -> 1
*/

int main() {
    cout << "El factorial de 4 es: " << factorial(4) << "\n\n";
    cout << "El factorial de 4 es: " << factorial_cola(1,1,4) << "\n\n";

    cout << "El quinto término de la sucesión de Fibonacci es: " << fibonacci(5) << "\n";

    return 0;
}