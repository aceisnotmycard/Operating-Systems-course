#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 1000

typedef struct node {
	char* text;
	struct node* next;
} Node;

Node* createNode(char* text) {
	Node* node = (Node *) malloc(sizeof(Node));
	node->text = text;
	node->next = NULL;
	return node;
}

int main(int argc, char** argv) {
	int i;
	char input[STRING_LENGTH];

	Node* bulba = createNode(NULL);
	Node* vasya = bulba;

	while(1) {
		gets(input);
		if ('.' == input[0]) {
			break;
		}

		vasya->text = (char*) malloc((strlen(input) + 1) * sizeof(char));
		strcpy(vasya->text, input);

		vasya->next = createNode(NULL);
		vasya = vasya->next;
 	}

 	vasya = bulba;
 	while (NULL != vasya->next) {
 		printf("%s\n", vasya->text);
 		vasya = vasya->next;
 	}

 	 while (NULL != bulba) {
 	 	vasya = bulba;
 		bulba = bulba->next;
 		free(vasya->text);
 		free(vasya);
 	}
}