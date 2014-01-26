#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define TAM 128000
#define UMBRAL 500

typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;

void ini_monticulo(monticulo *m) {
	m->ultimo = 0;

}
void copiarVectorAMonticulo(int v[], int n, monticulo *m) {
	int i;
	for (i = 0; i < n; i++) {
		m->vector[i] = v[i];
	}
}

void hundir(monticulo *m, int i) { //
	int aux = 0;
	int j = 0;

	do {
		int hijoIzq = 2 * i + 1;
		int hijoDer = 2 * i + 2;
		j = i;
		if ((hijoDer < m->ultimo) && (m->vector[hijoDer] > m->vector[i])) {
			i = hijoDer;
		}
		if ((hijoIzq < m->ultimo) && (m->vector[hijoIzq] > m->vector[i])) {
			i = hijoIzq;
		}
		aux = m->vector[j];
		m->vector[j] = m->vector[i];
		m->vector[i] = aux;
	} while (i != j);
}

void crear_monticulo(int v[], int n, monticulo *m) {
	int i = 0;
	int tamMont = 0;
	copiarVectorAMonticulo(v, n, m);
	(*m).ultimo = n;
	tamMont = (*m).ultimo;
	for (i = tamMont / 2; i >= 0; i--) {
		hundir(m, i);
	}
}

int monticulo_vacio(monticulo *m) {

	return m->ultimo == 0;
}

int eliminar_mayor(monticulo *m) {
	int x;

	if (monticulo_vacio(m)) {
		printf("Monticulo Vacio\n");
		exit(EXIT_FAILURE);
	} else {
		x = m->vector[0];
		m->vector[0] = m->vector[m->ultimo - 1];
		m->ultimo = (m->ultimo) - 1;
		if (m->ultimo > 0) {
			hundir(m, 0);
		}
		return x;
	}
}

void imprimirVector(int v[], int n) {
	int i = 0;
	printf("[ ");
	for (i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("]\n");
}

void imprimirMonticulo(monticulo m) {
	int i = 0;
	printf("[ ");
	for (i = 0; i < m.ultimo; i++) {
		printf("(%d) ", m.vector[i]);
	}
	printf("]\n");
}

void ordenacion_por_monticulo(int *v, int n) {
	int i;
	monticulo maxHeap;
	crear_monticulo(v, n, &maxHeap);
	for (i = n - 1; i >= 0; i--) {
		v[i] = eliminar_mayor(&maxHeap);

	}
}

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
	srand(time(NULL));
}

void aleatorio(int v[], int n) {
	int i, m = 2 * n + 1;
	for (i = 0; i < n; i++)
		v[i] = (rand() % m) - n;
	/* se generan números pseudoaleatorio entre -n y +n */
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

void cotas(double t, int n, double f, double g, double h, int menorQueUMBRAL) {
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
double tiemposUmbralCreMont(int v[], monticulo *maxHeap, int j) {
	double ta = 0, tb = 0, t1 = 0, t2 = 0, t = 0, k = 0;
	ta = microsegundos();
	for (k = 0; k < 1000; k++) {
		ascendente(v, j);
		crear_monticulo(v, j, maxHeap);
	}
	tb = microsegundos();
	t1 = tb - ta;
	ta = microsegundos();
	for (k = 0; k < 1000; k++) {
		ascendente(v, j);
	}
	tb = microsegundos();
	t2 = tb - ta;
	t = (t1 - t2) / 1000;
	return t;
}

double tiemposUmbralOrdeMont(int v[], monticulo *maxHeap, int j,
		void (*tipoDeOrdenacion)(int v[], int n)) {
	double ta = 0, tb = 0, t1 = 0, t2 = 0, t = 0, k = 0;
	ta = microsegundos();
	for (k = 0; k < 1000; k++) {
		tipoDeOrdenacion(v, j);
		ordenacion_por_monticulo(v, j);
	}
	tb = microsegundos();
	t1 = tb - ta;
	ta = microsegundos();
	for (k = 0; k < 1000; k++) {
		ascendente(v, j);
	}
	tb = microsegundos();
	t2 = tb - ta;
	t = (t1 - t2) / 1000; //1000=k
	return t;
}

void testCrearMonticulo() {
	int n = 32001, i = 0, j = 0;
	int v[32000];
	double ta, tb, t;
	monticulo maxHeap;
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.99",
			"t(n)/n^1.01", "t(n)/n^1.09");
	for (i = 0; i < 3; i++) {
		for (j = 2000; j < n; j = j * 2) {
			ascendente(v, j);
			ta = microsegundos();
			crear_monticulo(v, j, &maxHeap);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbralCreMont(v, &maxHeap, j);
				cotas(t, j, pow(j, 0.99), pow(j, 1.01), pow(j, 1.09), 1); //t, n, f(n), h(n),g(n),T menores al umbral=1 SINO 0
			} else {
				cotas(t, j, pow(j, 0.99), pow(j, 1.01), pow(j, 1.09), 0); //t, n, f(n), h(n),g(n),T menores al umbral=1 SINO 0
			}
		}
		printf("\n");
	}
}

void testVectorOrdenadoAscendente() {
	int n = 32001, i = 0, j = 0;
	int v[32000];
	double ta, tb, t;
	monticulo maxHeap;
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.99",
				"t(n)/log(n)", "t(n)/n^1.19");
	for (i = 0; i < 3; i++) {
		for (j = 2000; j < n; j = j * 2) {
			ascendente(v, j);
			ta = microsegundos();
			ordenacion_por_monticulo(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbralOrdeMont(v, &maxHeap, j, ascendente);
				cotas(t, j, pow(j, 0.99), j * log(j), pow(j, 1.19), 0);
			} else {
				cotas(t, j, pow(j, 0.99), j * log(j), pow(j, 1.19), 0); //t, n, f(n), h(n),g(n),T menores al umbral=1 SINO 0
			}
		}
		printf("\n");
	}
}

void testVectorOrdenadoDescendente() {
	int n = 32001, i = 0, j = 0;
	int v[32000];
	double ta, tb, t;
	monticulo maxHeap;
	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.99",
			"t(n)/log(n)", "t(n)/n^1.19");
	for (i = 0; i < 3; i++) {
		for (j = 2000; j < n; j = j * 2) {
			descendente(v, j);
			ta = microsegundos();
			ordenacion_por_monticulo(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbralOrdeMont(v, &maxHeap, j, descendente);
				cotas(t, j, pow(j, 0.99), j * log(j), pow(j, 1.19), 0);
			} else {
				cotas(t, j, pow(j, 0.99), j * log(j), pow(j, 1.19), 0); //t, n, f(n), h(n),g(n),T menores al umbral=1 SINO 0
			}
		}
		printf("\n");
	}
}

void testVectorDesordenadoAleatorio() {
	int n = 32001, i = 0, j = 0;
	int v[32000];
	double ta, tb, t;
	monticulo maxHeap;

	printf("%s%12s%18s%19s%18s%18s\n", " ", "n", "t(n)", "t(n)/n^0.99",
			"t(n)/n^1.1 ", "t(n)/n^1.19");

	for (i = 0; i < 3; i++) {
		for (j = 2000; j < n; j = j * 2) {
			aleatorio(v, j);
			ta = microsegundos();
			ordenacion_por_monticulo(v, j);
			tb = microsegundos();
			t = tb - ta;
			if (t < UMBRAL) {
				t = tiemposUmbralOrdeMont(v, &maxHeap, j, aleatorio);
				cotas(t, j, pow(j, 0.99), pow(j, 1.1), pow(j, 1.19), 0);
			} else {
				cotas(t, j, pow(j, 0.99), pow(j, 1.1), pow(j, 1.19), 0); //t, n, f(n), h(n),g(n),T menores al umbral=1 SINO 0
			}
		}
		printf("\n");
	}
}

void complejidadDeOrdenacion() {

	printf("\n %10s %s\n", " ",
			"Ordenar monticulo con inicialización Ascendente\n ");
	testVectorOrdenadoAscendente();
	printf("\n %10s %s\n", " ",
			"Ordenar monticulo con inicialización Descendente\n ");
	testVectorOrdenadoDescendente();
	printf("\n %10s %s\n", " ",
			"Ordenar monticulo con inicialización Aleatoria\n ");
	testVectorDesordenadoAleatorio();
}

void validarOperaciones() {
	int v[15];
	int n = 15;
	monticulo maxHeap;
	ascendente(v, n); //
	printf("\n***************** VALIDAR OPERACIONES ***********************\n");
	ini_monticulo(&maxHeap);
	printf("\n Monticulo Inicializado: %d", maxHeap.ultimo);
	printf("\n Crear monticulo : \n");
	crear_monticulo(v, n, &maxHeap);
	imprimirMonticulo(maxHeap);
	printf("\n Eliminar mayor: %d\n", eliminar_mayor(&maxHeap));
	printf(" Monticulo: ");
	imprimirMonticulo(maxHeap);
	printf("\n Vector antes de ordenar por monticulo de maximos \n");
	imprimirVector(v, n);
	printf("\n Vector despues de ordenar por monticulo de maximos \n");
	ordenacion_por_monticulo(v, n);
	imprimirVector(v, n);
	printf("\n");
}

int main() {

	inicializar_semilla();
	validarOperaciones();
	printf("\n %10s %s\n", " ",
			"Crear monticulo con inicialización Ascendente\n ");
	testCrearMonticulo();
	complejidadDeOrdenacion();

	return 0;
}
