//program p11, KTB Dec 10, 1996
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct dictionary_node {
	string value;
	dictionary_node* next = NULL;
};

struct dictionary {
	char binding;
	dictionary_node *data = NULL;
	dictionary *next = NULL;
};

inline int ask_for_word_count() {
	int ret;
	cout << "Podaj ilosc slow: " << endl;
	cin >> ret;
	// clear cin
	cin.ignore(1000, '\n');
	return ret;
}

inline string ask_for_word() {
	string ret;
	cout << "Podaj slowo ktore zostanie dodane do slownika" << endl;
	cin >> ret;
	// clear cin
	cin.ignore(1000, '\n');
	return ret;
}

// Adds *word* as the first element of list
// Returns pointer to new start
dictionary_node* add_to_list_at_start(string word, dictionary_node* list) {
	dictionary_node* new_list = new dictionary_node();
	new_list->value = word;
	new_list->next = list;
	return new_list;
}

// Adds word to dict if dict already contains a list for word[0]
// Returns true if word was added, false otherwise.
bool _add_to_dict(string word, dictionary* dict) {
	char binding = word[0];
	if (dict->binding == binding) {
		dict->data = add_to_list_at_start(word, dict->data);
		return true;
	} else if (dict->next == NULL){
		return false;
	} else {
		return _add_to_dict(word, dict->next);
	}
}

// Creates a new dictionary containing *word*
dictionary* new_dictionary(string word) {
	dictionary *new_dict = new dictionary();
	new_dict->binding = word[0];
	new_dict->data = new dictionary_node();
	new_dict->data->value = word;
	return new_dict;
}

// Adds *word* to *dict*
// If *dict* does not contain a list for word[0], new list is created at the end.
void add_to_dict_at_end(string word, dictionary* dict) {

	// Try adding word to existing lists in *dict*
	bool added_to_existing = _add_to_dict(word, dict);
	if (added_to_existing) return;

	// Find last element in the dict
	while (dict->next != NULL){
		dict = dict->next;
	}

	// Build new dict and add it to the end
	dict->next = new_dictionary(word);
}

// Adds *word* to *dict*
// If *dict* does not contain a list for word[0], new list is created at the beginning.
// Returns pointer to resulting dict
dictionary* add_to_dict_at_start(string word, dictionary* dict) {
	char binding = word[0];

	// Try adding word to existing lists in *dict*
	bool added_to_existing = _add_to_dict(word, dict);

	// If word was added to existing lists, we have nothing else to do.
	if (added_to_existing) return dict;

	// Build new dict
	dictionary *new_dict = new_dictionary(word);

	// Append old dictionary to it and return new start.
	new_dict->next = dict;
	return new_dict;
}

void print_list(dictionary_node* list) {
	while (list != NULL) {
		cout << list->value << " ";
		list = list->next;
	}
}

void print_dictionary(dictionary *dict) {
	cout << endl << "Skorowidz:" << endl;
	while (dict != NULL) {
		cout << "Lista " << dict->binding << ":" << endl;
		print_list(dict->data);
		cout << endl;
		dict = dict->next;
	}
}

void release_memory(dictionary* dict) {
	while (dict != NULL)
	{
		dictionary* next_dict = dict->next;
		dictionary_node* list = dict->data;
		while (list != NULL) {
			dictionary_node* next_list = list->next;
			delete list;
			list = next_list;
		}
		delete dict;
		dict = next_dict;
	}
}

//konstr i druk skorowidza z dopisywaniem na poczatku
void variant1() {
	int word_count = ask_for_word_count();
	if (word_count <= 0) return;
	dictionary* dict = new_dictionary(ask_for_word());
	word_count--;
	while (word_count > 0) {
		add_to_dict_at_end(ask_for_word(), dict);
		word_count--;
	}

	print_dictionary(dict);
	release_memory(dict);
}

//konstr i druk skorowidza z dopisywaniem na koncu
void variant2() {
	int word_count = ask_for_word_count();
	if (word_count <= 0) return;
	dictionary* dict = new_dictionary(ask_for_word());
	word_count--;
	while (word_count > 0) {
		dict = add_to_dict_at_start(ask_for_word(), dict);
		word_count--;
	}

	print_dictionary(dict);
	release_memory(dict);
}

//jak wariant 2 ale rowniez z dopisywaniem slow na koncu listy
void variant3() {
}

//jak wariant 3 ale czytanie danych z pliku tekstowego
void variant4() {
}

//czas sortowania na liscie poziomej, zadanie domowe
void variant5() {
	clock_t start_time = clock();
	//
	clock_t end_time = clock();
	cout << "czas: " << (1000 * (float)(end_time - start_time) / CLOCKS_PER_SEC) << " [ms]" << endl;
}

int main() {
	while (true) {
		int variant;
		cout << "Wariant: (0 - wyjdz/1/2/3/4/5)";
		cin >> variant;
		// clear cin
		cin.ignore(1000, '\n');
		switch (variant) {
		case 0:
			exit(EXIT_SUCCESS);
			break;
		case 1: //konstr i druk skorowidza z dopisywaniem na poczatku
			variant1();
			break;
		case 2: //konstr i druk skorowidza z dopisywaniem na koncu
			variant2();
			break;
		case 3:
			variant3();
			break;
		case 4:
			variant4();
			break;
		case 5:
			variant5();
			break;
		default:
			cout << "Taki wariant nie istnieje!";
		} // switch
	}

	return 0;
}
