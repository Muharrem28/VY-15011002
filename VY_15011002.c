#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack_index = 0;
char stack[200];

void postfix(char*, char*);
int is_empty();
int is_full();
void push(char);
void read_file(char*); 
char pop();
int control_marks(char, char);
char top_element();
                   
int main() {
	int i;
	char file_array[200] = "\0";
	char postfix[200] = "\0";	
	read_file(file_array);
	postfix(file_array, postfix);
	return 0;
}
   	
void read_file(char* file_array) {
	FILE* fp = fopen("input.txt","r");
	char ch;
	int i=0;
	while(!feof(fp)) {
		ch = fgetc(fp);
		file_array[i] = ch;
		i++;
	   	if(ch == ';') {
			file_array[i] = ' ';
			i++;
			fgetc(fp);
		}
   	}
   	printf("File Array: %s\n", file_array);
   	fclose(fp);
}

int is_empty() {
	return stack_index == 0;
}

int is_full() {
	return stack_index == 200;
}

void push(char new_element) {
	if(is_full(stack))
		return;
	stack[stack_index] = new_element;
	stack_index++;
}

char pop()
{
	if(is_empty(stack))
		return -1;
	stack_index--;
	return stack[stack_index];
}

char top_element()   
{
	if(is_empty(stack))
		return -1;
	return stack[stack_index-1];
}

int control_marks(char sign1, char sign2) {						// '*' and '/' is 1. in ascii table '*' is 42 and '/' is  47.
	static int signs[] = {1, 0, 0, 0, 0, 1};					// so we can put them to an six elements array.
	if(signs[sign1-42] < signs[sign2-42])
		return -1;
	return signs[sign1-42] > signs[sign2-42];
}

void postfix(char* in, char* post)  {
	int i;
	int j=0;
	char temp_char;
	char temp_pop;
	for(i=0 ; in[i] != '\0' ; i++) {
		if(in[i] == ';') {
		    while(!is_empty(stack)) {
		    	post[j++] = pop(stack);
		    	post[j++] = ' ';
			}
			post[j++] = '\n';
			post[j++] = ' ';
			post[j] = '\0';
		} else if(in[i]!=' ') {
			temp_char = in[i]; 
			if(temp_char == '(')
				push(stack, temp_char);
			else if(temp_char == ')') {
				temp_pop = pop(stack);
				while(temp_pop != '(') {
					 post[j++] = temp_pop;
					 post[j++] = ' ';
					 temp_pop = pop(stack);
				}
			}
			else if(isalnum(temp_char) || temp_char == '=') { 
				post[j++] = temp_char;
				post[j++] = ' ';
			} else {
				if(top_element(stack) != '(' && control_marks(temp_char, top_element(stack)) < 1) {
					while(control_marks(temp_char, top_element(stack)) > 0)  {
						temp_pop = pop(stack);
						post[j++] = temp_pop;
					 	post[j++] = ' ';	
					}
				}
				push(stack, temp_char);
			}
		}
	}
	printf("%s", post);
}
