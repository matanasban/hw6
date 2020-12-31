#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Defining the Linked list*/
struct node {
    int data;
    char *key;
    struct node *next;
};
struct node *head_1;
struct node *head_2;

/*Functions Declaration*/
char* readline();
char** split_string(char*);
void magazine_count_appear(char** magazine ,
                           int magazine_count,int *words_count);
void note_aount_appear(char** note ,
                       int note_count,int *words_count);
void magazine_map(struct node *temp_magazine,char** magazine,int n);
void note_Map(struct node *temp_note,char** note,int n);
void checkMagazine(int magazine_count,
                    char** magazine, int note_count, char** note);
bool in_list(struct node *head, char *word_to_search);
bool check_data(struct node *head,char *key_to_cmp,int data_to_cmp);
bool Contained();
void free_list(struct node *head);
/*End of Functions Declarations*/

/** Check if the number of appears of a certain word is the same in both lists
   * head - the list that we are searching in
   * key_to_cmp - the word that we want to check the number of occurrences
   * data_to_cmp - the number of occurrences of the word
   * return - returns true if the number of occurrences is the same and no
    otherwise.**/

bool check_data(struct node *head,char *key_to_cmp,int data_to_cmp){
    struct node *current = head;  /*Initialize current*/
    while (current != NULL){
        char *temp_word = current -> key;
        if (!(strcmp(key_to_cmp,temp_word))){/*found the key*/
            int temp_data = current -> data;
            if (temp_data < data_to_cmp){
                /*number of appearences is lower in magazine*/
                return false;
            }
        }
        current = current->next;
    }
    return true;
}
/** Checks if a certain key is in the list
   * head - the list that we are searching in
   * word_to_search - the word that we want to check the number of occurrences**/

bool in_list(struct node *head, char *word_to_search){
    struct node *current = head;  /* Initialize current*/
    while (current != NULL){
        char *temp_word = current -> key;
        if (!(strcmp(temp_word,word_to_search))){/*key found*/
            return true;
        }
        current = current -> next;
    }
    return false;
}
/** Free the nodes of a linked list
   * head - the list that we want to free**/
void free_list(struct node *head){
    struct node *tmp;
    while (head != NULL){
       tmp = head;
       head = head -> next;
       free(tmp);
    }
}
/** Creates an array with with the appearences of each word in magazine
   * magazine - the array of strings of the magazine
   * magazine_count - the number of strings in magazine
   * words_count the number of occurrences of each word in magazine **/
void magazine_count_appear(char** magazine ,
                           int magazine_count,int *words_count){
    int count = 0,j,i;
    for(j = 0 ; j < magazine_count ; j++){
            count = 0;
            for(i = 0 ; i < magazine_count ; i++){
                if(!(strcmp(magazine[i],magazine[j]))){
                    count++;
                }
            }
            words_count[j] = count;
        }
    }
/**  Creates an array with with the appearences of each word in note
   * note - the array of strings of the magazine
   * note_count - the number of strings in magazine
   * words_count the number of occurrences of each word in magazine **/
void note_count_appear(char** note ,int note_count,int *words_count){
    int count = 0,i,j;
    for(j = 0 ; j < note_count ; j++){
        count = 0;
            for(i = 0 ; i < note_count ; i++){
                if(!(strcmp(note[i],note[j]))){
                    count++;
                }
            }
            words_count[j] = count;
        }
    }
/**  Creates the magazine map(converting from array to linked list)
   * temp_magazine - helper pointer to create the linked list
   * magazine - the array of strings of the magazine
   * n - the number of strings in magazine **/
void magazine_map(struct node *temp_magazine,char** magazine,int n){
    int *words_count = malloc(n * sizeof(int));
    int i;
    if(words_count == NULL){
   		fprintf(stderr,"Failed to Allocate Bytes");
   	 	abort();
    }
    magazine_count_appear(magazine,n,words_count);
    temp_magazine -> key=magazine[0];
    temp_magazine -> data=words_count[0];
    temp_magazine -> next=(NULL);
    head_1 = temp_magazine;
    for(i=1;i<n;i++){
         if(in_list(head_1,magazine[i])){
                /*Key already exist , skip adding it to the list.*/
            continue;
        } else {
        struct node *temp_magazine2= malloc(sizeof(struct node));
        /*Add the key to the list*/
        if(temp_magazine2 == NULL){
        	fprintf(stderr,"Failed to Allocate Bytes");
   	 		abort();
   	 	}
        temp_magazine -> next = temp_magazine2;
        temp_magazine2 -> key = magazine[i];
        temp_magazine2 -> data = words_count[i];
        temp_magazine2 -> next = NULL;
        temp_magazine = temp_magazine2;
        }
     }

     free(words_count); /* Free the count array.*/
}
/**  Creates the note map(converting from array to linked list)
   * temp_note - helper pointer to create the linked list
   * note - the array of strings of the magazine
   * n - the number of strings in note **/
void note_map(struct node *temp_note,char** note,int n){
    int *words_count = malloc(n * sizeof(int));
    int i;
    if(words_count == NULL){
    	fprintf(stderr,"Failed to Allocate Bytes");
   		abort();
   		}
    note_count_appear(note,n,words_count);
    temp_note -> key =note[0];
    temp_note -> data= words_count[0];
    temp_note -> next=NULL;
    head_2 = temp_note;
    for(i=1;i<n;i++){
        if(in_list(head_2,note[i])){
            /*Key already exist , skip adding it to the list.*/
            continue;
        }
        else{
        struct node *temp_note2 = malloc(sizeof(struct node));
        /*add new key to the list.*/
        if(temp_note2 == NULL){
           	fprintf(stderr,"Failed to Allocate Bytes");
   	 		abort();
   	 	}
        temp_note -> next= temp_note2;
        temp_note2 -> key=note[i];
        temp_note2 -> data = words_count[i];
        temp_note2 -> next = NULL;
        temp_note = temp_note2;
        }
    }
    free(words_count);/* Free the count array.*/
}
/** * Checks if the input satisfies the demands
    * Function was given by course staff , no need to detail about params.**/
void checkMagazine(int magazine_count, char** magazine,
                    int note_count, char** note) {
    struct node *temp_magazine = malloc(sizeof(struct node));
    if(temp_magazine == NULL){
	   	fprintf(stderr,"Failed to Allocate Bytes");
   		abort();
   	}
    struct node *temp_note = malloc(sizeof(struct node));
    if(temp_note == NULL){
       	fprintf(stderr,"Failed to Allocate Bytes");
   		abort();
   	}
    magazine_map(temp_magazine,magazine, magazine_count);
    note_map(temp_note,note, note_count);
    if(Contained()){
        printf("Yes");
    }
    else{
        printf("No");
    }
    free_list(head_1);/*Freeing all the nodes of the magazine list*/
    free_list(head_2);/*Freeing all the nodes of the note list*/
}
/** * Checks if note array contained in magazine array **/
bool Contained(){
	struct node *tmp_2 = head_2;
    while (tmp_2 != NULL){
          /*word in note doesnt exist in magazine.*/
          if(!(in_list(head_1,(tmp_2 -> key)))){
                return false;
          }
          /*word in note  appears more than it does in magazine.*/
          else if (!check_data(head_1,tmp_2->key,tmp_2->data)){
              return false;
          }

          tmp_2 = tmp_2->next;
    }
    /*all the words of the note contained in the magazine.*/
    return true;
}
int main()
{
    char** mn = split_string(readline());
    int i;
    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
