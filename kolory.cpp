//program p15,	 KTB Jan 3, 1997
//port C/C++ 2013, JP
#include <iostream>
#include <iomanip>
#include <time.h>


using namespace std;

const int NMAX = 100;

inline int random(int a) {
	return rand() % a;
}

inline bool coinflip(double probability) {
	return rand() <= probability * RAND_MAX;
}

inline void print_array(int count, int arr[])
{
	for (int i = 0; i < count; i++)
		cout << arr[i] << ' ';
}

int max_in_array(int n, int x[])
{
	int m = x[0];
	for (int i = 1; i < n; i++)
	if (x[i] > m)
		m = x[i];
	return m;
}

void print_independent_sets(int node_count, int set_count, bool sets[][NMAX]) {
	cout << "Niezalezne zbiory: " << endl;
	for (int set = 0; set < set_count; set++) {
		for (int node = 0; node < node_count; node++)
		{
			if (sets[set][node]) {
				cout << node << ' ';
			}
		}
		cout << endl;
	}
}

void print_graph(int node_count, bool graph[][NMAX]) {
	cout << endl << "Krawedzie:" << endl;
	for (int i = 0; i < node_count - 1; i++) {
		for (int j = i; j < node_count; j++)	{
			if (graph[i][j]) {
				cout << setw(5) << i << setw(3) << j;
			}
		}
	}
	cout << endl << endl;
}

void color_node(int node_count, int node, bool graph[][NMAX], int colors[]) {
	// okreœl kolory sasiadow wierzcho³ka node
	// color = -1 oznacza wierzcholek niepokolorowany
	bool neighbor_colors[NMAX] = { false };
	for (int i = 0; i < node_count; i++) {
		if (graph[node][i] && colors[i] != -1) {
			neighbor_colors[colors[i]] = true;
		}
	}

	// pokoloruj node najnizszym kolorem który nie nalezy do sasiada
	for (int color = 0; color < node_count; color++) {
		if (!neighbor_colors[color]) {
			colors[node] = color;
			break;
		}
	}
}

void color_graph_monte_carlo(int node_count, bool graph[][NMAX], int colors[]) {
	bool visited[NMAX] = { false };
	int visited_count = 0;

	for (int i = 0; i < node_count; i++)	// przygotowanie tablicy kolorow
		colors[i] = -1;

	while (visited_count < node_count) {
		int node = random(node_count);
		if (visited[node]) {
			continue;
		}
		visited[node] = true;
		visited_count++;

		for (int i = 0; i < node_count; i++) {
			color_node(node_count, i, graph, colors);
		}
	}
}

void find_independent_sets(int node_count, int trials, bool graph[][NMAX], int *set_count, bool sets[][NMAX]) {
	if (trials == 0) {
		return;
	}
	
	// make _trials_ attempts to find best coloring using Monte Carlo method
	int* colors = new int[node_count]();
	int best_chromatic_number = node_count + 1;
	for (int i = 0; i < trials; i++) {
		int* coloring_attempt = new int[node_count];
		color_graph_monte_carlo(node_count, graph, coloring_attempt);
		int chromatic_number = max_in_array(node_count, coloring_attempt);
		if (chromatic_number < best_chromatic_number) {
			delete[] colors;
			colors = coloring_attempt;
		} else {
			delete[] coloring_attempt;
		}
	}

	*set_count = best_chromatic_number;
	for (int color = 0; color < *set_count; color++) {
		for (int node = 0; node < node_count; node++) {
			sets[color][node] = false;
		}
	}

	for (int node = 0; node < node_count; node++) {
		int color = colors[node];
		sets[color][node] = true;
	}

	delete[] colors;
}

void calculate_node_degrees(int node_count, bool graph[NMAX][NMAX], int degrees[]) {
	for (int i = 0; i < node_count; i++) {
		degrees[i] = 0;
		for (int j = 0; j < node_count; j++) {
			if (graph[i][j]) {
				degrees[i]++;
			}
		}
	}
}

void color_graph_recursive(int node_count, int degree, bool graph[][NMAX], int degrees[], int colors[]) {
	if (degree < 0)
		return;
	for (int node = 0; node < node_count; node++) {
		if (degrees[node] != degree) {
			continue;
		}
		color_node(node_count, node, graph, colors);
	}
	color_graph_recursive(node_count, degree - 1, graph, degrees, colors);
}

/*operacja kolorowania wierzcholkow grafu minimalna liczba kolorow,
Krzysztof Krol, Oct.1995, Inf. */
// port C/C++ 2013 JP

void color_graph(int node_count, bool graph[][NMAX], int degrees[], int colors[])
{
	calculate_node_degrees(node_count, graph, degrees);

	int max_degree = max_in_array(node_count, degrees);						// max stopien
	for (int i = 0; i < node_count; i++)									// przygotowanie tablicy kolorow
		colors[i] = -1;
	color_graph_recursive(node_count, max_degree, graph, degrees, colors);	// kolorowanie poczawszy od wierzcholkow o stopniu delta
} // kolor

void generate_graph_by_probability(int node_count, double probability, bool graph[][NMAX]) {
	for (int i = 0; i < node_count; i++)
		graph[i][i] = false;

	for (int i = 0; i < node_count - 1; i++)
	for (int j = i + 1; j < node_count; j++) {
		bool x = coinflip(probability);
		graph[i][j] = x;
		graph[j][i] = x;
	}
}

void generate_graph_by_edges(int node_count, int edge_count, bool graph[][NMAX]) {
	for (int i = 0; i < node_count; i++)
	for (int j = 0; j < node_count; j++)
		graph[i][j] = false;

	while (edge_count > 0)
	{
		int x = random(node_count);
		int y = random(node_count);

		if (x == y)
			continue;

		if (graph[x][y])
			continue;

		graph[x][y] = true;
		graph[y][x] = true;
		edge_count--;
	}
}

int ask_for_node_count() {
	int n;
	cout << "Podaj ilosc wierzcholkow grafu: " << endl;
	cin >> n;
	return n;
}

int ask_for_edge_count() {
	int n;
	cout << "Podaj ilosc krawedzi grafu: " << endl;
	cin >> n;
	return n;
}

double ask_for_edge_probability() {
	double p = 2.0;
	while (p > 1 || p < 0) {
		cout << "Podaj prawdopodobienstwo wystapienia krawedzi grafu: " << endl;
		cin >> p;
	}
	return p;
}

int ask_for_repetitions() {
	int n;
	cout << "Podaj ilosc powtorzen: " << endl;
	cin >> n;
	return n;
}

void variant1() {
	int node_count = ask_for_node_count();
	int edge_count = ask_for_edge_count();
	int repetitions = ask_for_repetitions();

	bool graph[NMAX][NMAX];
	int degrees[NMAX];
	int	colors[NMAX];
	cout << "Wierzcholkow: " << node_count <<
		" krawedzi: " << edge_count <<
		" powtorzen: " << repetitions << endl;

	for (int i = 0; i < repetitions; i++) {
		generate_graph_by_edges(node_count, edge_count, graph);
		color_graph(node_count, graph, degrees, colors);
		print_graph(node_count, graph);

		cout << "Stopnie wierzcholkow: ";
		print_array(node_count, degrees);
		cout << endl << "Najwyzszy stopien wierzcholka: " << max_in_array(node_count, degrees) << endl;

		int chromatic_number = max_in_array(node_count, colors);
		cout << "Kolory: ";
		print_array(node_count, colors);
		cout << endl << "Liczba chromatyczna = " << chromatic_number << endl;

		bool independent_sets[NMAX][NMAX];
		const int monte_carlo_trials = 1;
		find_independent_sets(node_count, monte_carlo_trials, graph, &chromatic_number, independent_sets);
		print_independent_sets(node_count, chromatic_number, independent_sets);
	}
}

void variant2() {
	int node_count = ask_for_node_count();
	double probability = ask_for_edge_probability();
	int repetitions = ask_for_repetitions();

	cout << "Wierzcholkow: " << node_count << endl <<
		"Prawdopodobienstwo: " << probability << endl <<
		"Powtorzen: " << repetitions << endl;
	bool graph[NMAX][NMAX];
	int degrees[NMAX];
	int colors[NMAX];
	for (int i = 0; i < repetitions; i++) {
		generate_graph_by_probability(node_count, probability, graph);
		color_graph(node_count, graph, degrees, colors);
		cout << endl;
		print_graph(node_count, graph);

		cout << "Stopnie wierzcholkow: " << endl;
		print_array(node_count, degrees);
		cout << endl << "Najwyzszy stopien wierzcholka: " << max_in_array(node_count, degrees) << endl << endl;

		cout << "Kolory wierzcholkow: " << endl;
		print_array(node_count, colors);
		cout << endl << "Liczba chromatyczna: " << max_in_array(node_count, colors);
	}
	cout << endl;
}

void variant3() {
	int node_count = ask_for_node_count();
	double probability = ask_for_edge_probability();
	int rep = ask_for_repetitions();

	cout << "Wierzcholkow: " << node_count << endl <<
		"Prawdopodobienstwo: " << probability << endl <<
		"Powtorzen: " << rep << endl;
	int degrees[NMAX];
	int colors[NMAX];
	clock_t czas1 = clock();
	for (int i = 0; i < rep; i++) {
		bool graph[NMAX][NMAX];
		generate_graph_by_probability(node_count, probability, graph);
		color_graph(node_count, graph, degrees, colors);
	}
	clock_t czas2 = clock();
	cout << "czas: " << (1000 * (float)(czas2 - czas1) / CLOCKS_PER_SEC) << " [ms]" << endl;
}

//Gnk, rozklad liczby chromatycznej, momenty
//przy stalym n i roznych k, zadanie domowe
void variant4() {
	int node_count = ask_for_node_count();
	int edge_count = ask_for_edge_count();
	int repetitions = ask_for_repetitions();
	cout << "Wierzcholkow: " << node_count <<
		" krawedzi: " << edge_count <<
		" powtorzen: " << repetitions << endl;

	bool graph[NMAX][NMAX];
	int degrees[NMAX];
	int colors[NMAX];
	for (int i = 1; i <= repetitions; i++) {
		generate_graph_by_edges(node_count, edge_count, graph);
		color_graph(node_count, graph, degrees, colors);
		//zbieranie informacji
	}
	// momenty
	//druk wynikow
}

//Gnk, rozklad liczby chromatycznej, momenty
//w zaleznosci od n oraz k = n*(n-1) div 4, zadanie domowe
void variant5() {
	int node_count = ask_for_node_count();
	int edge_count = ask_for_edge_count();
	int repetitions = ask_for_repetitions();
	cout << "Wierzcholkow: " << node_count <<
		" krawedzi: " << edge_count <<
		" powtorzen: " << repetitions << endl;

	bool A[NMAX][NMAX];
	int Deg[NMAX];
	int colors[NMAX];
	for (int i = 0; i < repetitions; i++) {
		generate_graph_by_edges(node_count, edge_count, A);
		color_graph(node_count, A, Deg, colors);
		//zbieranie informacji
	}
	//momenty
	//druk wynikow
}

// zmiana rekurencji na iteracje w algorytmie kolor,
// porownanie czasu wykonania, zadanie domowe
void variant6() {
}

int main()
{
	srand((unsigned)time(NULL));

	char variant = 'n';
	while (variant != 'q') {
		cout << endl << endl <<
			"Wybierz wariant: " << endl <<
			"1 - Kolorowanie grafu z okreslona liczba krawedzi" << endl <<
			"2 - Kolorowanie grafu z prawdopodobienstwem wystapienia krawedzi" << endl <<
			"3 - Zmierz czas wariantu 2" << endl <<
			"4 - Zadanie domowe" << endl <<
			"5 - Zadanie domowe" << endl <<
			"6 - Zadanie domowe" << endl <<
			"7 - Zadanie domowe" << endl <<
			"q - Wyjdz" << endl;
		cin >> variant;
		switch (variant) {
			// Gnk w E, transEA i kolor
		case '1':
			variant1();
			break;

			// Gnp w A i kolor
		case '2':
			variant2();
			break;

			// czas Gnp i kolor
		case '3':
			variant3();
			break;

			// Gnk, rozklad liczby chromatycznej, momenty
			// przy stalym n i roznych k, zadanie domowe
		case '4':
			variant4();
			break;

			// Gnk, rozklad liczby chromatycznej, momenty
			// w zaleznosci od n oraz k = n*(n-1) div 4, zadanie domowe
		case '5':
			variant5();
			break;

			// zmiana rekurencji na iteracje w algorytmie kolor,
			// porownanie czasu wykonania, zadanie domowe
		case '6':
			variant6();
			break;

			// testowanie innych algorytmow kolorowania, zadanie wlasne
		case '7':
			break;
		case 'q':
			break;
		case '\n':
			break;
		default:
			cout << "Taki wariant nie istnieje!" << endl;
			break;
		}
	}

	return 0;
}

void stat(int alltr, int rep, int Q[], float *x, float *y)
{
	float s = 0;
	for (int i = 0; i <= alltr; i++)
		s += (Q[i] / (float)rep)*i;
	*x = s;
	s = 0;
	for (int i = 0; i <= alltr; i++)
		s += (Q[i] / (float)rep)*(i - *x)*(i - *x);    //sqr(i-*x);
	*y = s;
} //stat