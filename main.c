#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct series {
	char name[50 + 1];
	double rate;
	char genre[20 + 1];
	int length;
	char airing[10 + 1];
	int seasons;
	int beginning_year;
	int sign; //for quizz 

	struct series* next;
}series;


// write out only one serie
void kiir_decsakegyet(series* data) {

	printf("%s %.1lf %s %d %s %d %d\n", data->name, data->rate, data->genre, data->length, data->airing, data->seasons, data->beginning_year);
}

//add element
series* addelem(series* head, series* new_el) {

	new_el->next = head;
	head = new_el;


	return head;
}

//read from the file
series* addfromfile(FILE* file) {
	series* newseries = NULL;
	series* head = NULL;
	series* tmp = NULL;

	int i ,n = 0;
	//read to the end of line
	while (!feof(file)) {

		newseries = (series*)malloc(sizeof(series));

		i = fscanf(file, "%s %lf %s %d %s %d %d", newseries->name, &newseries->rate, newseries->genre, &newseries->length, newseries->airing, &newseries->seasons, &newseries->beginning_year);
		newseries->sign = 0;

		newseries->next = NULL;
 	
		if (head == NULL) {
			head = newseries;
			
		}
		else {
			tmp = head;

			while (tmp->next != NULL) {
				tmp = tmp->next;
			}
			tmp->next = newseries;
			
		}

		
	}

	if (i == -1) return NULL;  // if file is empty, do nothing

	return head;
}

//in title space ->  _
void manage_name(char* str) {

	for (int i = 0; str[i] != '\0'; i++) {

		if (str[i] == ' ') {
			str[i] = '_';
		}

	}

	return;
}


// menu choices
void menu_choosing(char* str) {

	while (strcmp(str, "List the series") && strcmp(str, "Add series") && strcmp(str, "Change series") && strcmp(str, "Delete series") && strcmp(str, "Quiz") && strcmp(str, "Quit")) {
		printf("Choose one:\n ");
		gets(str);
		printf("\n");
	}

	return;
}

//error treatment

void youcantwrite_gohome_rate(double* rate) {

	while (*rate > 10.0 || *rate < 5.0) {
		printf("Please give an answer (5.0 - 10.0): ");
		scanf("%lf", rate);

	}
}

void youcantwrite_gohome_genre(char* str) {

	while (strcmp(str, "adventure") != 0 && strcmp(str, "animation") != 0 && strcmp(str, "cartoon") != 0 && strcmp(str, "comedy") != 0 && strcmp(str, "crime") != 0 && strcmp(str, "drama") != 0 && strcmp(str, "dramedy") != 0 && strcmp(str, "fantasy") != 0 && strcmp(str, "horror") != 0 && strcmp(str, "documentary") != 0) {
		printf("Please give an answer:\n ");
		printf("adventure | animation | cartoon | comedy | crime | drama | dramedy | fantasy | horror | documentary\n");
		scanf("%s", str);
	}
}

void youcantwrite_gohome_length(int* length) {

	while (*length <= 0 || *length > 90) {
		printf("Please give an answer (1 - 90 min): ");
		scanf("%d", length);
	}

}

void youcantwrite_gohome_airing(char* s) {

	while (strcmp(s, "running") && strcmp(s, "ended")) {
		printf("Please enter your answer: ");
		scanf("%s", s);
	}
}

void youcantwrite_gohome_seasons(int* seas) {

	while (*seas <= 0 || *seas > 35) {
		printf("Please give an answer (1 - 35): ");
		scanf("%d", seas);
	}
}

void youcantwrite_gohome_by(int* by) {

	while (*by < 1950 || *by > 2020) {
		printf("Please give an answer (1950 - 2020): ");
		scanf("%d", by);
	}
}

//looks for a given series by name
series* searchforseries(series* head, char* name) {
	series* tmp;

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (strcmp(tmp->name, name) == 0) {
			return tmp;
		}
	}

	printf("Series not founded.\n");
	return NULL;
}

//user gives an element to the list
series* new_fromuser(series* head) {
	series* new_elem = (series*)malloc(sizeof(series));
	new_elem->next = NULL;

	printf("Please give the title of the series:\n"); 
	gets(new_elem->name);
	manage_name(new_elem->name);
	if (searchforseries(head, new_elem->name) != NULL) {
		printf("It is already existing...\n");
		return head;
	}
	printf("\n");

	printf("Rate:\n "); //double rate
	youcantwrite_gohome_rate(&new_elem->rate); //scanf 
	printf("\n");

	printf("What its genre?\n "); //char genre ??
	youcantwrite_gohome_genre(new_elem->genre);
	printf("\n");

	printf("How long is an episode?\n"); //int length
	youcantwrite_gohome_length(&new_elem->length);
	printf("\n");

	printf("Is it still airing? (running or ended)\n"); 
	youcantwrite_gohome_airing(new_elem->airing);
	printf("\n");

	printf("How many seasons does it have?\n");//int seasons
	youcantwrite_gohome_seasons(&new_elem->seasons);
	printf("\n");

	printf("When did it begin?\n");//int beginning_year
	youcantwrite_gohome_by(&new_elem->beginning_year);
	printf("\n");

	new_elem->sign = 0;

	head = addelem(head, new_elem);

	if (head == NULL) printf("Adding new series was not successful\n."); // cannot return NULL because the linked list will be lost

	return head;
}

series* delete_series(series* head, char* name) {
	series* tmp;
	series* to_delete = NULL;

	
	printf("Which series do you want to delete?\n");
	
	while (to_delete == NULL) {

		gets(name);
		manage_name(name);
		to_delete = searchforseries(head, name);

		if (to_delete == NULL) {
			printf("Please give another try:\n");
	
		}
	}

	//if the searched series is the first element of the list
	if (to_delete == head) {
		head = to_delete->next;
		to_delete->next = NULL;
		free(to_delete);
		return head;
	}

	for (tmp = head; tmp->next != to_delete; tmp = tmp->next) {

	}

	tmp->next = to_delete->next;
	to_delete->next = NULL;
	free(to_delete);

	return head;
}

char* change_title() {
	char nombre[50 + 1];

	printf("Please enter the new title: ");
	scanf("%s", nombre);

	manage_name(nombre);

	return nombre;
}

double change_rate() {
	double num;

	printf("Rate:\n ");
	youcantwrite_gohome_rate(&num);

	return num;
}

char* change_genre() {
	char g[20 + 1];

	printf("What its genre?\n");
	youcantwrite_gohome_genre(g);

	return g;
}

int change_length() {
	int lange;

	printf("How long is an episode?\n");
	youcantwrite_gohome_length(&lange);

	return lange;
}

char* change_airing() {
	char air[10 + 1];

	printf("Is it still airing? (running / ended)\n ");
	youcantwrite_gohome_airing(air);

	return air;
}

int change_seasons() {
	int saison;

	printf("How many seasons does it have?\n ");
	youcantwrite_gohome_seasons(&saison);

	return saison;
}

int change_beginning_year() {
	int erste_jahr;

	printf("When it started?\n");
	youcantwrite_gohome_by(&erste_jahr);
	return erste_jahr;
}


//change the data of elements
void change_data(series* head) {
	int change;
	char title[50 + 1];
	series* series_change = NULL;

	printf("Which series do you want to change?\n");

	while (series_change == NULL) {

		gets(title);
		manage_name(title);
		series_change = searchforseries(head, title);

		if (series_change == NULL) {
			printf("Please give another try:\n");
		}
	}

	printf("\n");
	kiir_decsakegyet(series_change);
	printf("\n");

	printf("Which data do you want to change?\n");
	printf(" 1:title\n 2:rate\n 3:genre\n 4:length\n 5:airing\n 6:seasons\n 7:beginnig year\n");
	scanf("%d", &change);

	switch (change) {
	case 1:strcpy(series_change->name, change_title()); break; //name
	case 2:series_change->rate = change_rate(); break; //rate
	case 3:strcpy(series_change->genre, change_genre()); break; //genre
	case 4:series_change->length = change_length(); break; //length
	case 5:strcpy(series_change->airing, change_airing()); break; //airing
	case 6:series_change->seasons = change_seasons(); break; //seasons
	case 7:series_change->beginning_year = change_beginning_year(); break; //beginning year
	default:printf("You can't write, go home.\n");
	}

	return;
}

//the "gui" (on command line) quiz 
void start() {

	printf("Hi there.\n");
	getchar();

	printf("So you have a plenty of time to waste your time and you can't decide which series you want to watch.\n");
	getchar();

	printf("Well, it's your lucky day. This program helps to desperared souls like you in the decision.\n");
	getchar();

	printf("You just need to answer a few question. \n");
	getchar();

	printf("Let's begin.\n");
	getchar();

	return;
}

//counts how many series fit to user's choice
int count_signs(series* head) {
	int num = 0;
	series* tmp;

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (tmp->sign == 1) {
			num++;
		}
	}
	
	return num;
}

//if filtering is less than 0
int picky_user(series* head) {

	if (count_signs(head) == 0) {
		printf("Sorry, you are too picky... Maybe next time :( \n");
		return 0;
	}

	return count_signs(head);
}

void q_airing(series *head) {
	series* tmp;
	char s[10 + 1];

	printf("Do you wanna watch a running or an ended show?\n");
	youcantwrite_gohome_airing(s);

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (strcmp(tmp->airing, s) == 0) {
			tmp->sign = 1;
		}
	}

	return;
}

void q_genre(series* head) {
	int sign_num = count_signs(head);
	if (sign_num <= 5)return;

	char s[10 +1];
	series* tmp;

	printf("Which genre do you prefer?\n");
	youcantwrite_gohome_genre(s);

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (strcmp(tmp->genre, s) != 0 && tmp->sign == 1 ) {
			tmp->sign = 0;
		}
	}

	return;
}

void q_length(series* head) {
	int sign_num = count_signs(head);
	if (sign_num <= 5)return;

	int num;
	series* tmp;

	printf("How long should be an episode?\n");
	youcantwrite_gohome_length(&num);

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (num > 0 && num <= 30) {
			if ( tmp->length >30 && tmp->sign == 1) {
				
				tmp->sign = 0;
			}
		}
		else if (num > 30 && num <= 59) {
			if ((tmp->length <= 30 || tmp->length > 59) && tmp->sign == 1) {

				tmp->sign = 0;
			}
			
		}
		else if (num > 59 && num <= 90 ) {
			if (tmp->length <= 59 && tmp->sign == 1) {

				tmp->sign = 0;
			}

		}

	}

	return;
}

void q_seasons(series* head) {
	int sign_num = count_signs(head);
	if (sign_num <= 5)return;

	int s;
	series* tmp;

	printf("How much time do you wanna spend to watch it? \n");
	printf("1: Just an evening/a day. \n");
	printf("2: Maybe a weekend? \n");
	printf("3: It should be the new meaning of my life!!negy! \n");

	printf("Please enter 1, 2 or 3: ");
	scanf("%d", &s);

	while (s != 1 && s != 2 && s != 3) {
		printf("Please enter 1, 2 or 3: ");
		scanf("%d", &s);
	}

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (s == 1) {
			if (tmp->seasons > 3 && tmp->sign == 1) {

				tmp->sign = 0;
			}
		}
		else if (s == 2) {
			if ((tmp->seasons <= 3 || tmp->seasons > 7) && tmp->sign == 1) {

				tmp->sign = 0;
			}

		}
		else if (s == 3) {
			if (tmp->seasons <= 7 && tmp->sign == 1) {

				tmp->sign = 0;
			}
		}
	}

	return;
}

void q_rate(series* head) {
	int sign_num = count_signs(head);
	if (sign_num <= 5)return;

	double rate_num;
	series* tmp;

	printf("How much should be the IMDB rating? \n");
	youcantwrite_gohome_rate(&rate_num);

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (rate_num >= 5.0 && rate_num < 8.0) { // v�laszt�s kateg�ri�ja
			if (tmp->rate > 8.0 && tmp->sign == 1) { //can list element go in

				tmp->sign = 0;
			}
		}
		else if (rate_num >= 8.0 && rate_num < 9.0) {
			if ((tmp->rate < 8.0 || tmp->rate >= 9.0) && tmp->sign == 1) {

				tmp->sign = 0;
			}

		}
		else if (rate_num >= 9.0 && rate_num < 10.0) {
			if (tmp->rate < 9.0 && tmp->sign == 1) {

				tmp->sign = 0;
			}
		}
	}

	return;
}

void q_beginning(series* head) {
	int sign_num = count_signs(head);
	if (sign_num <= 5)return;

	int n;
	series* tmp;

	printf("How old series do you wanna watch?\n");
	printf("1:Gimme some oldie ones.\n");
	printf("2:Not to be older than me.\n");
	printf("3:I want to watch one of the newest.\n");
	printf("Please enter 1, 2 or 3: ");
	scanf("%d", &n);

	while (n != 1 && n != 2 && n != 3) {
		printf("Please enter 1, 2 or 3: ");
		scanf("%d", &n);
	}

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		if (n == 1) {
			if (tmp->beginning_year > 2005 && tmp->sign == 1) {

				tmp->sign = 0;
			}
		}
		else if (n == 2) {
			if ((tmp->beginning_year <= 2005 || tmp->beginning_year > 2014) && tmp->sign == 1) {

				tmp->sign = 0;
			}
		}
		else if (n == 3) {
			if (tmp->beginning_year <= 2014 && tmp->sign == 1) {

				tmp->sign = 0;
			}
		}
	}

	return;
}

void lets_do_quizz(series* head, FILE *file) {

	start();
	q_airing(head);
	if (picky_user(head) == 0)return;

	q_genre(head);
	if (picky_user(head) == 0)return;

	q_length(head);
	if (picky_user(head) == 0)return;

	q_seasons(head);
	if (picky_user(head) == 0)return;

	q_seasons(head);
	if (picky_user(head) == 0)return;

	q_rate(head);
	if (picky_user(head) == 0)return;

	q_beginning(head);
	if (picky_user(head) == 0)return;

	series* tmp;
	printf("You should watch: \n");
	for (tmp = head; tmp != NULL; tmp = tmp->next) {
		
		if (tmp->sign == 1) {
			printf("%s\n", tmp->name);
			fprintf(file, "%s\n", tmp->name);
		}
	}
	printf("\n");
	return;
}

//write out series to a file which are in the linked list
void backtofile(FILE* file, series* head) {
	series* tmp;

	for (tmp = head; tmp != NULL; tmp = tmp->next) {

		//if (tmp == NULL) return;
		if (tmp->next == NULL) {
			fprintf(file, "%s %.1lf %s %d %s %d %d", tmp->name, tmp->rate, tmp->genre, tmp->length, tmp->airing, tmp->seasons, tmp->beginning_year);
		}
		else {
			fprintf(file, "%s %.1lf %s %d %s %d %d\n", tmp->name, tmp->rate, tmp->genre, tmp->length, tmp->airing, tmp->seasons, tmp->beginning_year);
		}

	}

	return;
}


//free linked list 
void letitgo(series* head) {
	series* tmp = head;

	while (tmp != NULL) {
		head = tmp->next;
		free(tmp);
		tmp = head;
	}

	return;
}


//write out to command line
void kiir(series* head) {
	series* tmp = head;

	while (tmp != NULL) {
		printf("%s %.1lf %s %d %s %d %d\n", tmp->name, tmp->rate, tmp->genre, tmp->length, tmp->airing, tmp->seasons, tmp->beginning_year);
		tmp = tmp->next;
	}

	return;
}


int main(void) {
	series* list = NULL;

	FILE* all_series = fopen("sorozatok.txt", "r");
	FILE* quizz_file = fopen("quizz.txt", "w");

	char menu[20];
	char searched[50 + 1];

	if (all_series == NULL) {
		printf("opening sorozatok.txt was not succeeded\n");
	}

	list = addfromfile(all_series);

	if (list == NULL ) {
		printf("No datas, no work.\n");

	}
	else {

		fclose(all_series);
		all_series = fopen("sorozatok.txt", "w");

		
		//eddig fix
		while (strcmp(menu, "Quit")) {

			strcpy(menu, "blank");

			printf("Menu\n\n");
			printf("List the series\n");
			printf("Add series\n");
			printf("Change series\n");
			printf("Delete series\n");
			printf("Quiz\n");
			printf("Quit\n\n");

			menu_choosing(menu);

			if (strcmp(menu, "List the series") == 0) {

				kiir(list);
				printf("\n");

			}
			else if (strcmp(menu, "Add series") == 0) {

				list = new_fromuser(list);

			}
			else if (strcmp(menu, "Change series") == 0) {

				change_data(list);
				

			}
			else if (strcmp(menu, "Delete series") == 0) {

				list = delete_series(list, searched);
				
			}
			else if (strcmp(menu, "Quiz") == 0) {

				lets_do_quizz(list,quizz_file);

				series* tmp;
				for (tmp = list; tmp != NULL; tmp = tmp->next) {
					tmp->sign = 0;
				}

			}
			

		}


		backtofile(all_series, list);
	}


	letitgo(list);

	fclose(all_series);
	fclose(quizz_file);

	return 0;
}