#include <stdio.h>
//printf, scanf, fgets, ...
#include <math.h>
// pow (potencia)
#include <string.h>

/*
	esta funci�n recibe como par�metros: 
		- el n�mero decimal a transformar
		-la base a la que deseo transfomrar
		- la referencia del arreglo a donde va a guardar el resultado invertido
	devuelve el tama�o de mi n�mero transformado
*/

int decimalABaseN(int numero, int base, int * numeroTransformado){
	int cociente=numero, indice=0;
	
	while(cociente>0){
		numeroTransformado[indice]= cociente % base;
		cociente =cociente / base;
		indice +=1;
	}
	//devolviendo el tama�o del arreglo
	return indice;
}

/*
	esta funci�n recibe como par�metros: 
		- el n�mero en arreglo de enteros, donde los d�gitos est�n invertidos
		- el tama�o del n�mero (cantidad de d�gitos)
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
	transforma e imprime un n�mero de octal o hexadecimal a binario
	esta funci�n recibe como par�metros: 
		- el n�mero en octal en arreglo de enteros, donde los d�gitos est�n en orden
		- el tama�o del n�mero (cantidad de d�gitos)
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
	Pide un n�mero entero correspondiente a la base del n�mero que el usuario ingresar� para ser transformado
	Par�metros:
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
	Valida que el numero entero proporcionado sea una base v�lida (2, 8, 10, 16)
	Par�metros:
		- n�mero base para validar
	Dato devuelto:
		- Estado de validez de el n�mero base ingresado
			0 - Base inv�lida
			1 - Base V�lida
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
	Valida que el numero proporcionado a travez de una cadena de caracteres contenga caracteres v�lidos para la base indicada (2, 8, 10, 16)
	Par�metros:
		- el numero en una cadena de caracteres (apuntador a caracter)
		- Numero entero para la base
	Dato devuelto:
		- Estado de validez de el n�mero base ingresado
			0 - Base inv�lida
			1 - Base V�lida
*/
int validaNumero(char * numero, int base, int tamanioCadena){
	// Condici�n para determinar que un d�gito corresponda a la base 2 , suponer que el d�gito es la variable d  =>   '0' <= d && d <= '1'
	// Condici�n para determinar que un d�gito corresponda a la base 8 , =>   '0' <= d && d <= '7'
	// Condici�n para determinar que un d�gito corresponda a la base 10 , =>   '0' <= d && d <='9'
	// Condici�n para determinar que un d�gito corresponda a la base 16 , =>   '0' <= d && d <='9'  ||  'A' <= d && d <= 'F'
	int contador = 0;
	
	do{
		/* Inicio del proceso de validaci�n de cada d�gito para la base ingresada */
		//Verficando el digito sea v�lido para la base 2
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
		/* FIN del proceso de validaci�n de cada d�gito para la base ingresada */
	}while(contador < tamanioCadena);
	return 1;
}

/*
	Transforma una cadena de caracteres (correspondiente a un n�mero en base 2, 8, 10 o 16) a un arreglo de enteros
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
	Par�metros:
		- La cadena de caracteres que contiene el n�mero en base 2, 8, 10 o 16
		- La referncia del arreglo de enteros donde se almacenar� el n�mero transformado
	Dato devuelto
		Estado de ejecici�n de la funci�n
			1 - Terminacion exitosa
			0 Terminaci�n por error
				
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

