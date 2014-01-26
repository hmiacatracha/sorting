#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define MAX1 32001
#define UMBRAL 500
int umbral;


int ordenado(int v[], int n) {
	int ord = 1, i = 1;
	while (i < n && ord) {
		if (!(v[i - 1] <= v[i])) {
			ord = 0;
		}
		i++;
	}
	return ord;
}

void estaOrdenado(int v[], int n, int ordenando) {
	int i;
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%4d ", v[i]);
	}
	printf("\n");
	printf("¿Esta Ordenado? %d\n", ordenado(v, n));

	if (ordenando) {
		printf("ordenando...");
	}
}

void inicializar_semilla() {
	srand(time(NULL));
}

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v[], int n) {
	int i, m = 2 * n + 1;
	for (i = 0; i < n; i++)
		v[i] = (rand() % m) - n;
	/* se generan números pseudoaleatorio entre -n y +n */
}

void ord_sel(int v[], int n) {
	int i, j, minx, minj;
	for (i = 0; i < n; i++) {
		minj = i;
		minx = v[i];
		for (j = i + 1; j < n; j++) {
			if (v[j] < minx) {
				minj = j;
				minx = v[j];
			}
		}
		v[minj] = v[i];
		v[i] = minx;
	}
}

void ord_shell(int v[], int n) {
	int incremento, tmp, seguir;
	int i, j;
	incremento = n;

	while (incremento > 0) {
		incremento /= 2;
		;
		for (i = incremento; i < n; i++) {
			tmp = v[i];
			j = i;
			seguir = 1;
			while ((j - incremento) >= 0 && seguir) {
				if (tmp < v[j - incremento]) {
					v[j] = v[j - incremento];
					j -= incremento;
				} else {
					seguir = 0;
				}
			}
			v[j] = tmp;
		}
	}
}

void ascendente(int v[], int n) {
	int i;
	for (i = 0; i < n; i++)
		v[i] = i;
}
void descendente(int v[], int n) {
	int i;
	int j;
	for (i = 0, j = n - 1; i < n; i++, j--) {
		v[i] = j;
	}
}



void testSel(void) {
	int n = 10;
	int v[n];
	printf("%80s\n", "****************************************************** ");
	printf("%81s\n", "*           Ordenación por Seleccion                 * ");
	printf("%80s\n", "****************************************************** ");
	printf("\n%20s", "Ordenacion por seleccion con inicializacion Aleatoria");
	aleatorio(v, n);
	estaOrdenado(v, n, 1);
	ord_sel(v, n);
	estaOrdenado(v, n, 0);
	printf("\n%20s", "Ordenacion por seleccion con inicializacion Descendente");
	descendente(v, n);
	estaOrdenado(v, n, 1);
	ord_sel(v, n);
	estaOrdenado(v, n, 0);
	printf("\n%20s", "Ordenacion por seleccion con inicializacion Ascendente");
	ascendente(v, n);
	estaOrdenado(v, n, 1);
	ord_sel(v, n);
	estaOrdenado(v, n, 0);

}
void testShell(void) {
	int n = 10;
	int v[n];
	printf("%80s\n", "****************************************************** ");
	printf("%81s\n", "*                Ordenación por Shell                * ");
	printf("%80s\n", "****************************************************** ");
	printf("\n%20s", "Ordenacion por shell  con inicializacion Aleatoria");
	aleatorio(v, n);
	estaOrdenado(v, n, 1);
	ord_shell(v, n);
	estaOrdenado(v, n, 0);
	printf("\n%20s", "Ordenacion por shell con inicializacion Descendente");
	descendente(v, n);
	estaOrdenado(v, n, 1);
	ord_shell(v, n);
	estaOrdenado(v, n, 0);
	printf("\n%20s", "Ordenacion por shell con inicializacion Ascendente");
	ascendente(v, n);
	estaOrdenado(v, n, 1);
	ord_shell(v, n);
	estaOrdenado(v, n, 0);

}
/*			ALGORITMO DE ORDENACION POR SELECCION




 */

void cotas(double t, int n, double f, double g, double h, int menorQueUMBRAL) { //menorQueUmbral= bit que representa si el tiempo es menor que el umbral
	double sub = 0, ajus = 0, sobre = 0;

	sub = t / f;/*Serie crece t(n)/f(n)*/
	ajus = t / g; /*Constante t(n)/g(n)*/
	sobre = t / h; /*Serie decrece t(n)/h(n)*/
	if (menorQueUMBRAL) {
		printf("|%12d | %15.3f* | %15.6f | %15.6f | %15.6f|\n", n, t, sub, ajus,
				sobre);
	} else {
		printf("|%12d | %15.3f  | %15.6f | %15.6f | %15.6f|\n", n, t, sub, ajus,
				sobre);
	}

}

double tiemposUmbral(int v[], int j, void (*funOrdenacion)(int v[], int n),
		void (*situacionVector)(int v[], int n)) {
	double ta = 0, tb = 0, t1 = 0, t2 = 0, t = 0, k = 0;
	ta = microsegundos();
	for (k = 0; k < 1000; k++) {
		situacionVector(v, j);
		funOrdenacion(v, j);
	}
	tb = microsegundos();
	t1 = tb - ta;
	ta = microsegundos();
	for (k = 0; k < 1000; k++) {
		situacionVector(v, j);
	}
	tb = microsegundos();
	t2 = tb - ta;
	t = (t1 - t2) / 1000;
	return t;
}
void tiempo_sel_Aleatorio(void) {
	int v[MAX1];
	int i = 0, j = 0;
	double ta = 0, tb = 0, t = 0;
	printf("%10s %s\n", " ",
			"Ordenación por selección con inicialización Alet");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.95",
			"t(n)/n^1.99", "t(n)/n^2.056");
	for (i = 0; i < 3; i++) {
		for (j = 500; j <= MAX1; j = j * 2) {
			aleatorio(v, j);
			ta = microsegundos();
			ord_sel(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbral(v, j, ord_sel, aleatorio);
				//cotas(t, j, pow(j, 1.95), pow(j, 1.99), pow(j, 2.056), 1);
			} else {
				//cotas(t, j, pow(j, 1.95), pow(j, 1.99), pow(j, 2.056), 0);
			}
		}
		printf("\n");
	}
}

void tiempo_sel_Descendente(void) {
	int v[MAX1];
	int i = 0, j = 0;
	double ta = 0, tb = 0, t = 0;
	printf("%10s %s\n", " ",
			"Ordenación por selección con inicialización Desc");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.95",
			"t(n)/n^1.99", "t(n)/n^2.054");
	for (i = 0; i < 3; i++) {
		for (j = 500; j <= MAX1; j = j * 2) {
			descendente(v, j);
			ta = microsegundos();
			ord_sel(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbral(v, j, ord_sel, descendente);
				//cotas(t, j, pow(j, 1.95), pow(j, 1.99), pow(j, 2.054), 1);
			} else {
				//cotas(t, j, pow(j, 1.95), pow(j, 1.99), pow(j, 2.056), 0);
			}
		}
		printf("\n");
	}
}

void tiempo_sel_Ascendente(void) {
	int v[MAX1];
	int i = 0, j = 0;
	double ta = 0, tb = 0, t = 0;
	printf("%10s %s\n", " ", "Ordenación por selección con inicialización Asc");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.97",
			"t(n)/n^1.99", "t(n)/n^2.03");
	for (i = 0; i < 3; i++) {
		for (j = 500; j <= MAX1; j = j * 2) {
			ascendente(v, j);
			ta = microsegundos();
			ord_sel(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbral(v, j, ord_sel, ascendente);
				//cotas(t, j, pow(j, 1.97), pow(j, 1.99), pow(j, 2.03), 1);
			} else {
				//cotas(t, j, pow(j, 1.97), pow(j, 1.99), pow(j, 2.03), 0);
			}
		}
		printf("\n");
	}
}

void tablas_Tiempo_Sel() {
	printf("\n  TABLA DE TIEMPOS PARA UN VECTOR ALEATORIO \n");
	tiempo_sel_Aleatorio();
	printf("\n   TABLA DE TIEMPOS PARA UN VECTOR DESCENDENTE \n");
	tiempo_sel_Descendente();
	printf("\n   TABLA DE TIEMPOS PARA UN VECTOR ASCENDENTE \n");
	tiempo_sel_Ascendente();

}

/*   			ALGORITMO DE ORDENACION POR SHELL




 */

void tiempo_shell_Aleatorio(void) {
	int v[MAX1];
	int i = 0, j = 0;
	double ta = 0, tb = 0, t = 0;
	printf("\n");
	printf("%10s %s\n", " ", "Ordenación por Shell con inicialización Aleat");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.1",
			"t(n)/n^1.2", "t(n)/n^1.3");
	for (i = 0; i < 3; i++) {
		for (j = 500; j <= MAX1; j = j * 2) {
			aleatorio(v, j);
			ta = microsegundos();
			ord_shell(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbral(v, j, ord_shell, aleatorio);
				cotas(t, j, pow(j, 1.1), pow(j, 1.2), pow(j, 1.3), 1);
			} else {
				cotas(t, j, pow(j, 1.1), pow(j, 1.2), pow(j, 1.3), 0);
			}
		}
		printf("\n");
	}
}

void tiempo_shell_Descendente(void) {
	int v[MAX1];
	int i = 0, j = 0;
	double ta = 0, tb = 0, t = 0;
	printf("%10s %s\n", " ", "Ordenación por Shell con inicialización Desc");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.1",
			"t(n)/n^1.11", "t(n)/n^1.2");
	for (i = 0; i < 3; i++) {
		for (j = 500; j <= MAX1; j = j * 2) {
			descendente(v, j);
			ta = microsegundos();
			ord_shell(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbral(v, j, ord_shell, descendente);
				//cotas(t, j, pow(j, 1.1), pow(j, 1.11), pow(j, 1.2), 1);
			} else {
				//cotas(t, j, pow(j, 1.1), pow(j, 1.11), pow(j, 1.2), 0);
			}
		}
		printf("\n");
	}
}

void tiempo_shell_Ascendente(void) {
	int v[MAX1];
	int i = 0, j = 0;
	double ta = 0, tb = 0, t = 0;
	printf("%10s %s\n", " ", "Ordenación por Shell con inicialización Asc");
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^1.1",
			"t(n)/n^1.126", "t(n)/n^1.2");
	for (i = 0; i < 3; i++) {
		for (j = 500; j <= MAX1; j = j * 2) {
			ascendente(v, j);
			ta = microsegundos();
			ord_shell(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbral(v, j, ord_shell, ascendente);
				//cotas(t, j, pow(j, 1.1), pow(j, 1.26), pow(j, 1.2), 1);
			} else {
				//cotas(t, j, pow(j, 1.1), pow(j, 1.26), pow(j, 1.2), 0);
			}
		}
		printf("\n");
	}
}

void tablas_tiempo_shell() {

	printf("\nTABLA DE TIEMPOS PARA UN VECTOR ALEATORIO \n");
	tiempo_shell_Aleatorio();
	printf("\n   TABLA DE TIEMPOS PARA UN VECTOR DESCENDENTE \n");
	tiempo_shell_Descendente();
	printf("\n   TABLA DE TIEMPOS PARA UN VECTOR ASCENDENTE \n");
	tiempo_shell_Ascendente();

}

/**
 *
 *                 ORDENACION POR INSERSION
 *
 *  */

void ord_ins(int v[], int n) {
	int i;
	int x;
	int j;
	for (i = 0; i < n; i++) {
		x = v[i];
		j = i - 1;
		while (j > -1 && v[j] > x) {
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = x;
	}
}

void testIns() {
	int v[50];
	int n = 10;
	printf("\nInicialización aleatoria \n");
	aleatorio(v, n);
	estaOrdenado(v, n,0);
	printf("Ordenación por Inserción \n");
	ord_ins(v, n);
	estaOrdenado(v, n,1);
	printf("\nInicialización descendente \n");
	descendente(v, n);
	estaOrdenado(v, n,0);
	printf("Ordenación por Inserción \n");
	ord_ins(v, n);
	estaOrdenado(v, n,1);
}

void intercambiar(int v[], int k, int j) {
	int aux;
	aux = v[k];
	v[k] = v[j];
	v[j] = aux;
}

void Mediana3(int v[], int i, int j) {
	int k;
	k = ((i + j) / 2);
	if (v[k] > v[j]) {
		intercambiar(v, k, j);
	}
	if (v[k] > v[i]) {
		intercambiar(v, k, i);
	}
	if (v[i] > v[j]) {
		intercambiar(v, i, j);
	}
}

void Ordenacion_rapida(int v[], int n) {
	OrdenarAux(v, 0, n - 1);
	if (umbral > 1) {
		ord_ins(v, n);
	}
}

void OrdenarAux(int v[], int izq, int der) {
	int pivote;
	int i, j;

	if (izq + umbral <= der) {
		Mediana3(v, izq, der);
		pivote = v[izq];
		i = izq;
		j = der;
		do {
			do {
				i = i + 1;
			} while (v[i] < pivote);
			do {
				j = j - 1;
			} while (v[j] > pivote);
			intercambiar(v, i, j);
		} while (j > i);
		intercambiar(v, i, j);
		intercambiar(v, izq, j);

		OrdenarAux(v, izq, (j - 1));
		OrdenarAux(v, (j + 1), der);
	}
}



void testQuick() {
	int v[10];
	umbral = 1;
	printf(" COMPROBACION QUICKSORT \n");
	descendente(v, 10);
	estaOrdenado(v, 10,0);
	Ordenacion_rapida(v, 10);
	estaOrdenado(v, 10,1);

	aleatorio(v, 10);
	estaOrdenado(v, 10,0);
	Ordenacion_rapida(v, 10);
	estaOrdenado(v, 10,1);
}

int main(void) {
	inicializar_semilla();
	testSel();
	testShell();
	testIns();
	testQuick();
	tablas_Tiempo_Sel();
	tablas_tiempo_shell();

}
