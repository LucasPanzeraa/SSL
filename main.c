#include <stdio.h>

int columna(char c) {
    if (c == '+' || c == '-') return 0;
    if (c == '0') return 1;
    if (c >= '1' && c <= '7') return 2;
    if (c == '8' || c == '9') return 3;
    if (c == 'x' || c == 'X') return 4;
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 5;
    if (c == '@') return 6;
    return 7;
}

//Funcion ejercicio 1
void analizar_cadena(const char *cadena) {
   
    static int tablatransicion[9][8] = {
        {1, 2, 4, 4, 8, 8, 8, 8},
        {8, 7, 4, 4, 8, 8, 8, 8},
        {8, 5, 5, 8, 3, 8, 0, 8},
        {8, 6, 6, 6, 8, 6, 8, 8},
        {8, 4, 4, 4, 8, 8, 0, 8},
        {8, 5, 5, 8, 8, 8, 0, 8},
        {8, 6, 6, 6, 8, 6, 0, 8},
        {8, 8, 8, 8, 8, 8, 0, 8},
        {8, 8, 8, 8, 8, 8, 8, 8}
    };

    int estado = 0;
    int i = 0;
    int cant_dec = 0; 
	int cant_oct = 0;
	int cant_hex = 0;
    char c = cadena[0];

    while (c != '\0') {
        int col = columna(c);
        int estado_anterior = estado;
        
        estado = tablatransicion[estado][col];

      
        if (col == 6) { 
            if (estado_anterior == 5) cant_oct++;
            else if (estado_anterior == 2 || estado_anterior == 4 || estado_anterior == 7) cant_dec++;
            else if (estado_anterior == 6) cant_hex++;
        }

        i++;
        c = cadena[i];
    }

   
    if (estado == 2 || estado == 4 || estado == 5 || estado == 6 || estado == 7) {
        if (estado == 5) cant_oct++;
        else if (estado == 2 || estado == 4 || estado == 7) cant_dec++;
        else if (estado == 6) cant_hex++;

        printf("Cantidad de Decimales: %d | Cantidad de Octales: %d | Cantidad de Hexa: %d\n", cant_dec, cant_oct, cant_hex);
        printf("\nLa cadena pertenece al lenguaje y fue procesada correctamente.\n");
    } else {
        printf("\nLa cadena NO es valida (contiene errores lexicos).\n");
    }

}

//Funcion ejercicio 2
int char_a_entero(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0'; 
    }
    return -1; 
}

int calcular(const char *cadena) {
    int numeros[20];
    char operadores[20];
    int nums = 0; 
    int oper = 0;
    int i = 0;

    
    while (cadena[i] != '\0') {
        if (nums == oper) {
            int signo = 1;
            int digito;
            int val = 0;
            if (cadena[i] == '+' || cadena[i] == '-') {
                if (cadena[i] == '-') signo = -1;
                i++;
            }
            while ((digito = char_a_entero(cadena[i])) != -1) {
                val = val * 10 + digito;
                i++;
            }
            numeros[nums++] = signo * val;
        } else {
            operadores[oper++] = cadena[i];
            i++;
        }
    }

    
    for (int j = 0; j < oper; j++) {
        if (operadores[j] == '*') {
            numeros[j] = numeros[j] * numeros[j + 1];
           
            for (int k = j + 1; k < nums - 1; k++){
                numeros[k] = numeros[k + 1];
            }
            for (int k = j; k < oper - 1; k++){
                operadores[k] = operadores[k + 1];
            }
            nums--; 
            oper--; 
            j--; 
        }
    }

    
    int resultado = numeros[0];
    for (int j = 0; j < oper; j++) {
        if (operadores[j] == '+'){
            resultado += numeros[j + 1];
        } 
        else if (operadores[j] == '-'){
            resultado -= numeros[j + 1];
        }
    }

    return resultado;
}

int columna_cuenta(char c) {
    if (c == '0') return 0;
    if (c >= '1' && c <= '9') return 1;
    if (c == '+' || c == '-') return 2;
    if (c == '*') return 3;
    return 4;
}
//Funcion ejercicio 3
void analizar_cadena_cuenta(const char *cadena) {
    
    static int tablatransicion[4][5] = {
        {1, 1, 2, 3, 3},
        {1, 1, 0, 0, 3},
        {1, 1, 3, 3, 3},
        {3, 3, 3, 3, 3}
    };

    int estado = 0;
    int i = 0;
    char c = cadena[0];

    while (c != '\0') {
        int col = columna_cuenta(c);
        estado = tablatransicion[estado][col];
        i++;
        c = cadena[i];
    }

    
    if (estado == 1) {
        printf("\nLa cadena pertenece al lenguaje y fue procesada correctamente.\n");
        int resultado = calcular(cadena);
        printf("\nEl resultado de la cuenta es: %d",resultado);
    } else {
        printf("\nLa cadena NO es valida (contiene errores lexicos).\n");
    }

}

int main() {
    char cadena[] = "0xABF@-152@0Xafe@015@5";
    printf("\nCadena a analizar: %s\n",cadena);
    analizar_cadena(cadena);
   
    char cuenta[] = "2+3*4*5";
    printf("\nCadena a analizar: %s\n",cuenta);
    analizar_cadena_cuenta(cuenta);
    return 0;
}