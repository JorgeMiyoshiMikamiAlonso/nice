#include <stdio.h>
//printf, scanf, fgets, ...
#include <math.h>
// pow (potencia)
#include <string.h>

/*
	esta función recibe como parámetros: 
		- el número decimal a transformar
		-la base a la que deseo transfomrar
		- la referencia del arreglo a donde va a guardar el resultado invertido
	devuelve el tamaño de mi número transformado
*/

int decimalABaseN(int numero, int base, int * numeroTransformado){
	int cociente=numero, indice=0;
	
	while(cociente>0){
		numeroTransformado[indice]= cociente % base;
		cociente =cociente / base;
		indice +=1;
	}
	//devolviendo el tamaño del arreglo
	return indice;
}

/*
	esta función recibe como parámetros: 
		- el número en arreglo de enteros, donde los dígitos están invertidos
		- el tamaño del número (cantidad de dígitos)
	devuelve estado de terminacion exitoso 0
*/
int imprimeNumeroArregloInvertido(int * numeroTransformado, int tamanio_numero){
	while (tamanio_numero>0){
		tamanio_numero = tamanio_numero - 1;
		if (numeroTransformado[tamanio_numero] <10){
			printf("%d", numeroTransformado[tamanio_numero]);
		}else{
			printf("%c", numeroTransformado[tamanio_numero]+55);
		}
	}
	return 0;
}

/*
	transforma e imprime un número de octal o hexadecimal a binario
	esta función recibe como parámetros: 
		- el número en octal en arreglo de enteros, donde los dígitos están en orden
		- el tamaño del número (cantidad de dígitos)
		- la base original a transformar
	devuelve estado de terminacion exitoso 0
*/
int octHexABinario(int * numeroOctal, int tamanio_numero, int baseOriginal){
	//suponiendo que se va a transformar 7 6 2 ... tamanio_numero  3
	int tamanioTransformacion, digitosTotalesPorCifra, indiceOctal;
	int resultadoTransformacion [4], grupo;
	
	if (baseOriginal == 8){
		grupo=3;
	}else if (baseOriginal == 16){
		grupo=4;
	}else{
		return -1;
	}
	
	for(indiceOctal=0; indiceOctal < tamanio_numero ; indiceOctal++){
		tamanioTransformacion = decimalABaseN(numeroOctal[indiceOctal], 2, resultadoTransformacion);
		digitosTotalesPorCifra = tamanioTransformacion;
		while (digitosTotalesPorCifra < grupo){
			printf("0");
			digitosTotalesPorCifra = digitosTotalesPorCifra+1;
		}
		imprimeNumeroArregloInvertido(resultadoTransformacion, tamanioTransformacion );
	}
	return 0;
}


int baseNADecimal(int * numeroBaseN, int tamanio_numero, int baseOriginal){
	int decimal=0, indice=0;
	
	while (tamanio_numero > 0 ){
		decimal = decimal + (numeroBaseN[indice] * pow(baseOriginal,tamanio_numero -1) ); 
		tamanio_numero = tamanio_numero -1;	
		indice = indice +1;
	}
	return decimal;
}

/*
	Pide un número entero correspondiente a la base del número que el usuario ingresará para ser transformado
	Parámetros:
		- 
	Dato devuelto:
		- 
*/
int pideBase(){
	int base;
	printf("\n\tIngrese la base del numero que desea transformar (2, 8, 10, 16): ");
	do{
		scanf("%d", &base );
	}while(validaBase(base)==0);
	
	return base;
}

/*
	Valida que el numero entero proporcionado sea una base válida (2, 8, 10, 16)
	Parámetros:
		- número base para validar
	Dato devuelto:
		- Estado de validez de el número base ingresado
			0 - Base inválida
			1 - Base Válida
*/
int validaBase(int base){
	if (base == 2 || base == 8 || base == 10 || base == 16){
		return 1;
	}else{
		printf("\n\tLa base ingresada no es valida, favor de ingresar alguna de las opciones validas (2, 8, 10, 16): ");
		return 0;
	}
}



int pideNumero(int base, int * numeroEntero){
	char numero[18];
	int tamanioCadena;
	printf("\n\tIngrese el numero que desea transformar en base %d: ", base);
	do{
		fflush(stdin);
		fgets(numero, 18, stdin);
		tamanioCadena = strlen(numero)-1;
	}while(validaNumero(numero, base, strlen(numero)-1) == 0);
	stringToIntArray(numero, numeroEntero,tamanioCadena);
	return tamanioCadena;
}

/*
	Valida que el numero proporcionado a travez de una cadena de caracteres contenga caracteres válidos para la base indicada (2, 8, 10, 16)
	Parámetros:
		- el numero en una cadena de caracteres (apuntador a caracter)
		- Numero entero para la base
	Dato devuelto:
		- Estado de validez de el número base ingresado
			0 - Base inválida
			1 - Base Válida
*/
int validaNumero(char * numero, int base, int tamanioCadena){
	// Condición para determinar que un dígito corresponda a la base 2 , suponer que el dígito es la variable d  =>   '0' <= d && d <= '1'
	// Condición para determinar que un dígito corresponda a la base 8 , =>   '0' <= d && d <= '7'
	// Condición para determinar que un dígito corresponda a la base 10 , =>   '0' <= d && d <='9'
	// Condición para determinar que un dígito corresponda a la base 16 , =>   '0' <= d && d <='9'  ||  'A' <= d && d <= 'F'
	int contador = 0;
	
	do{
		/* Inicio del proceso de validación de cada dígito para la base ingresada */
		//Verficando el digito sea válido para la base 2
		if (!(  
			(base==2 && '0' <= numero[contador] && numero[contador] <= '1') ||
		 	(base == 8 && '0' <= numero[contador] && numero[contador] <= '7') ||
			(base == 10 && '0' <= numero[contador] && numero[contador] <= '9') ||
			(base == 16 && ( ('0' <= numero[contador] && numero[contador] <= '9') ||  ('A' <= numero[contador] && numero[contador] <= 'F') ) )
		)){	
			printf("\n\tEl formato del numero no es valido para la base solicitada,\n\tingrese el numero en base %d: ", base);
			return 0;
		}
		contador ++;
		/* FIN del proceso de validación de cada dígito para la base ingresada */
	}while(contador < tamanioCadena);
	return 1;
}

/*
	Transforma una cadena de caracteres (correspondiente a un número en base 2, 8, 10 o 16) a un arreglo de enteros
	por ejemplo 
		'1' = 1 
		'A' = 10
		.......
	ejemplo de uso 
		cadena = "AB123"
		arreglo entero[0] = 10
				entero[1] = 11
				entero[2] = 1
				entero[3] = 2
				entero[4] = 3
	Parámetros:
		- La cadena de caracteres que contiene el número en base 2, 8, 10 o 16
		- La referncia del arreglo de enteros donde se almacenará el número transformado
	Dato devuelto
		Estado de ejecición de la función
			1 - Terminacion exitosa
			0 Terminación por error
				
*/
int stringToIntArray(char * cadena, int *  numero, int tamanioCadena){
	int contador;
	for(contador=0;contador < tamanioCadena ; contador ++){
		if ('0' <= cadena [contador]  && '9' >= cadena [contador] ){
			numero[contador] = cadena[contador] - 48;
		}else if ('A' <= cadena [contador]  && 'F' >= cadena [contador]){
			numero[contador] = cadena[contador] - 55;
		}else{
			return 0;
		}	
	}
	
	return 1;
}

int main(){
	int base, tamanioNumero;
	int numero[16];
	base = pideBase();
	tamanioNumero = pideNumero(base, numero);
	
	
	
	return 0;
}

