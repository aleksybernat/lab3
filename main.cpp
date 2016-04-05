// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void sortSlavsBySex(Slav *, int);
void showAns(); //funkcja wyswietla odpowiedz na ocene 5,5

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sortSlavsBySex(slavs, n);
	showAns();

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("\n# CONTAINERS\n\n");
	REPORT_CONTAINERS;
	printf("\n## vector\n");

	vectorOfSlavs.push_back(slavs);

	srand(time(NULL));

	for(int i=1; i<n; i++) //Umieszczam Slowian w wektorze "rozpychajac" go w roznych miejscach
	{
		int where=rand()%vectorOfSlavs.size();
		vectorOfSlavs.insert(vectorOfSlavs.begin()+where, slavs+i);
	}


	for(vector<Slav*>::iterator it=vectorOfSlavs.begin(); it!=vectorOfSlavs.end(); it++) //wyswietlanie zawartosci wektora za pomoca iteratora
	{
		cout << (*it)->description() << endl;
	}

	printf("\n");

	REPORT_CONTAINERS;
	printf("\n## set\n");

	for(int i=0; i<n; i++) //przenoszenie Słowian do zbioru (i czyszczenie wektora)
	{
		setOfSlavs.insert(vectorOfSlavs[i]);
		vectorOfSlavs.pop_back();
	}
	printf("\n");
	REPORT_CONTAINERS;
	printf("\n## map\n");

	//pomocne iteratorki:
	set<Slav*>::iterator it_set=setOfSlavs.begin();
	set<Slav*>::iterator it_set_h=setOfSlavs.begin();


	while(it_set!=setOfSlavs.end())  //wpisywanie Słowian do słownika i czyszczenie zbioru
	{
	mapOfSlavs[*it_set++]=*it_set++;
	setOfSlavs.erase(it_set_h++);
	setOfSlavs.erase(it_set_h++);
	}
	
	map<Slav*,Slav*>::iterator it_map;

	for(it_map=mapOfSlavs.begin(); it_map!=mapOfSlavs.end(); it_map++)  //wyświetlanie Słowian ze słownika
	{
		cout << "[ "<< (*it_map).first->description() << " | " << (*it_map).second->description() << " ]" << endl;
	}
	printf("\n");
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# ADAPTERS\n\n");
	REPORT_ADAPTERS;
	printf("\n## queue\n");

	for(int i=0; i<n; i++) //wpisywanie Słowian do kolejki
	{
		queueOfSlavs.push(slavs+i);
	}
	printf("\n");
	REPORT_ADAPTERS;

	printf("\n## stack\n");
	
	for(int i=0; i<n; i++)  //wrzucanie Słowian na stos i czyszczenie kolejki
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}
	printf("\n");
	REPORT_ADAPTERS;

	for(int i=0; i<n; i++)  //zdejmowanie Słowian ze stosu i wypisywanie
	{
		cout << (*stackOfSlavs.top()).description() << endl;
		stackOfSlavs.pop();
	}
	printf("\n");
	REPORT_ADAPTERS;
	printf("\n");
}

void sortSlavsBySex(Slav* slavs, int n) //sortowanie ze względu na płeć
{

	printf("# SORTING BY SEX\n");
	map<_sex , vector<Slav*> > mapOfSortedSlavs;


	for(int i=0; i<n; i++)  //wpisywanie Słowian do wektorów w zależności od płci
	{
		if ((slavs+i)->sex()==male) mapOfSortedSlavs[male].push_back(slavs+i);
		else mapOfSortedSlavs[female].push_back(slavs+i);
	}

	vector<Slav*>::iterator it_vec=mapOfSortedSlavs[male].begin();
	int counter=0;
	_sex slavSex;
	printf("\n# Men\n");

	while(it_vec!=mapOfSortedSlavs[male].end()) //wyswietlanie mężczyzn...
	{
		counter++;

		cout << (*it_vec++)->description() << endl;
	}
	if (counter==0) printf("<empty>\n");
	

	printf("\n# Women\n");

	it_vec=mapOfSortedSlavs[female].begin();
	counter=0;

	while(it_vec!=mapOfSortedSlavs[female].end()) //... i kobiet
	{

		counter++;

		cout << (*it_vec++)->description() << endl;

	}
	if (counter==0) printf("<empty>\n");

}

void showAns()
{
	printf("\n\n");
	cout << "Linijka 21 (u mnie 25) wykona sie raz (static). Zostanie w niej zailicjalizowana zmienna, ktora";
	cout << " policzy imiona zawarte w pliku names.dat. Inicjalizacja\nta wykona sie dopiero podczas pracy konstruktora";
	cout << " pierwszego obiektu (wtedy, gdy ma mu zostac nadane imie). Ten proces, odwzorowujacy funkcjonowanie\nwielu";
	cout << " studentow nazywa sie leniwa inicjalizacja." << endl;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
