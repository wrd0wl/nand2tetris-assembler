#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assembler.h"
#define BIT 17
#define ROW 100

struct compdec{
	char symb[4];
	char bin[8];
}comp[28]={{"0", "0101010"}, {"1", "0111111"}, {"-1", "0111010"}, {"D", "0001100"}, {"A", "0110000"},
		{"!D", "0001101"}, {"!A", "0110001"}, {"-D", "0001111"}, {"-A", "0110011"}, {"D+1", "0011111"},
		{"A+1", "0110111"}, {"D-1", "0001110"}, {"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
		{"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"}, {"M", "1110000"}, {"!M", "1110001"},
		{"-M", "1110011"}, {"M+1", "1110111"}, {"M-1", "1110010"},{"D+M", "1000010"}, {"D-M", "1010011"},
		{"M-D", "1000111"}, {"D&M", "1000000"}, {"D|M", "1010101"}};

struct destdec{
	char symb[4];
	char bin[4];
}dest[7]={{"M", "001"}, {"D", "010"}, {"MD", "011"}, {"A", "100"}, {"AM", "101"},
		{"AD", "110"}, {"AMD", "111"}};

struct jumpdec{
	char symb[4];
	char bin[4];
}jump[7]={{"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"}, {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}};

struct presetdec{
	char symb[8];
	char bin[BIT];
}preset[23]={{"R0", "0000000000000000"}, {"R1", "0000000000000001"}, {"R2", "0000000000000010"},
		{"R3", "0000000000000011"}, {"R4", "0000000000000100"}, {"R5", "0000000000000101"},
		{"R6", "0000000000000110"}, {"R7", "0000000000000111"}, {"R8", "0000000000001000"},
		{"R9", "0000000000001001"}, {"R10", "0000000000001010"}, {"R11", "0000000000001011"},
		{"R12", "0000000000001100"}, {"R13", "0000000000001101"}, {"R14", "0000000000001110"},
		{"R15", "0000000000001111"}, {"SCREEN", "0100000000000000"}, {"KBD", "0110000000000000"},
		{"SP", "0000000000000000"}, {"LCL", "0000000000000001"}, {"ARG", "0000000000000010"},
		{"THIS", "0000000000000011"}, {"THAT", "0000000000000100"}};


//converts decimal number into binary
long long int dec_to_bin(int val){
	long long int r=0, i=1;;

	while (val!=0) {
		if (val%2==1) r=r+i;
		i=i*10;
		val=val/2;
	}
	return r;
}

//converts string into integer
int char_to_int(int n, char *str){
	while((*str!='\0')&&(*str!=' ')&&(*str!='/')&&(*str!='\n')&&(*str!='\r')&&(*str!='\t')){
			n=n*10 + (*str - '0');
			str++;
		}
	return n;
}

//converts integer into string
void int_to_char(long long int val, char *string){
	int n[BIT], i=0;
	do{
		n[i]=val%10;
		val=val/10;
		i++;
	}while(val!=0);

	while(i<BIT){
		n[i]=0;
		i++;
	}

	for(int j=BIT-2; j>=0; j--){
		*string=n[j]+48;
		string++;
	}
	*string='\0';
}

//compares two strings. returns 1 if they are equal, otherwise 0
int bool_compare(char *str1, char *str2){
	int flag = 0;
	int i, j;
	i=strlen(str1);
	j=strlen(str2);
	if(i==j){
		flag=1;
		while(*str1!='\0' && *str2!='\0'){

			if(*str1 != *str2){
				flag = 0;
			}
			str1++;
			str2++;
		}
	}

	return flag;
}

//finds in struct compdec type of computing operation and copies it's corresponding binary code into computing field of C-instruction
void copy_comp(char *str1, char *str2){
	char aux1[ROW], aux2[ROW];
	int j=0, k=0;

	for(int i=0; i<28; i++){
		while(comp[i].symb[j]!='\0'){
			aux1[j]=comp[i].symb[j];
			j++;
		}
		aux1[j]='\0';
		j=0;

		while(comp[i].bin[k]!='\0'){
			aux2[k]=comp[i].bin[k];
			k++;
		}
		aux2[k]='\0';
		k=0;

		if(bool_compare(aux1, str1)){
			strcat(str2, aux2);
		}
	}
}

//finds in struct destdec type of register and copies it's corresponding binary code into destination field of C-instruction
void copy_dest(char *str1, char *str2){
	char aux1[ROW], aux2[ROW];
	int j=0, k=0;

	for(int i=0; i<7; i++){
		while(dest[i].symb[j]!='\0'){
			aux1[j]=dest[i].symb[j];
			j++;
		}
		aux1[j]='\0';
		j=0;

		while(dest[i].bin[k]!='\0'){
			aux2[k]=dest[i].bin[k];
			k++;
		}
		aux2[k]='\0';
		k=0;

		if(bool_compare(aux1, str1)){
			strcat(str2, aux2);
		}
	}
}

//finds in struct jumpdec type of jump and copies it's corresponding binary code into jump field of C-instruction
void copy_jump(char *str1, char *str2){
	char aux1[ROW], aux2[ROW];
	int j=0, k=0;

	for(int i=0; i<7; i++){
		while(jump[i].symb[j]!='\0'){
			aux1[j]=jump[i].symb[j];
			j++;
		}
		aux1[j]='\0';
		j=0;

		while(jump[i].bin[k]!='\0'){
			aux2[k]=jump[i].bin[k];
			k++;
		}
		aux2[k]='\0';
		k=0;

		if(bool_compare(aux1, str1)){
			strcat(str2, aux2);
		}
	}
}

//finds preset symbols in struct presetdec. returns 1 if it was found, otherwise 0
int bool_preset(char *str){
	int flag=0, j=0;
	char aux[ROW];
	for(int i=0; i<23; i++){
			while(preset[i].symb[j]!='\0'){
				aux[j]=preset[i].symb[j];
				j++;
			}
			aux[j]='\0';
			j=0;

			if(bool_compare(aux, str)){
					return flag = 1;
				}
		}

	return flag;
}

//finds preset symbol in struct presetdec and copies it's corresponding binary code
void find_preset(char *str){
	char aux1[ROW], aux2[BIT];
	int j=0, k=0;

	for(int i=0; i<23; i++){
		while(preset[i].symb[j]!='\0'){
			aux1[j]=preset[i].symb[j];
			j++;
		}
		aux1[j]='\0';
		j=0;

		while(preset[i].bin[k]!='\0'){
			aux2[k]=preset[i].bin[k];
			k++;
		}
		aux2[k]='\0';
		k=0;

		if(bool_compare(aux1, str)){
			strcpy(str, aux2);
		}
	}
}

//pushes symbol to the list
void push_symb(list** head, char *str, int n){
		list* tmp;
		int i = 0;
		tmp = malloc(sizeof(list));

		while(*str!='\0'){
			tmp->symb[i]=*str;
			str++;
			i++;
		}
		tmp->symb[i]='\0';
		tmp->address = n;
		tmp->next = *head;
		*head = tmp;
}

//searches demanded string in list. returns 1 if it was found, otherwise 0 
int bool_symb(list* head, char *str){
	int flag = 0;
	while(head!=NULL){
		if(strcmp(head->symb, str)==0){
			flag = 1;
		}
		head=head->next;
	}
	return flag;
}

//finds address of symbol from list and converts it into binary code
void find_address_symb(list* head, char *str){
	while(head!=NULL){
		if(strcmp(head->symb, str)==0){
			int_to_char(dec_to_bin(head->address), str);
		}
		head=head->next;
	}
}

//makes exchange of strings
void exchange(char *str1, char *str2){
	while(*str2!='\0'){
		*str1=*str2;
		str1++;
		str2++;
	}
	*str1='\0';
}

//converts a-instruction into binary code
void a_instr(char *str){
	char *tmp;
	tmp=str;
	int num=0;
	num=char_to_int(num, tmp);
	int_to_char(dec_to_bin(num), tmp);
	strcpy((str), (tmp));
}

//converts C-instruction and converts in into binary code
void c_instr(char *str){
	char *tmp;
	char aux1[ROW], aux2[ROW];
	char aux_c[BIT]={"111"};
	int i=0, j=0;
	tmp = str;

	while((*tmp!='\0')&&(*tmp!=' ')&&(*tmp!='/')&&(*tmp!='\n')&&(*tmp!='\r')&&(*tmp!='\t')){
		
		//dest=comp
		//defines assignment of computing operation to destination
		if(*tmp=='='){									
			aux1[i]='\0';
			tmp++;
			while((*tmp!='\0')&&(*tmp!=' ')&&(*tmp!='/')&&(*tmp!='\n')&&(*tmp!='\r')&&(*tmp!='\t')){
				aux2[j]=*tmp;
				tmp++;
				j++;
			}
			aux2[j]='\0';

			copy_comp(aux2, aux_c);
			copy_dest(aux1, aux_c);
			strcat(aux_c, "000");
			exchange(str, aux_c);
		}
		
		//comp;jump
		//defines jump instruction
		else if(*tmp==';'){								
			aux1[i]='\0';
			tmp++;
			while((*tmp!='\0')&&(*tmp!=' ')&&(*tmp!='/')&&(*tmp!='\n')&&(*tmp!='\r')&&(*tmp!='\t')){
				aux2[j]=*tmp;
				tmp++;
				j++;
			}
			aux2[j]='\0';

			copy_comp(aux1, aux_c);
			strcat(aux_c, "000");
			copy_jump(aux2, aux_c);

			exchange(str, aux_c);
		}

		aux1[i]=*tmp;
		tmp++;
		i++;
	}
}

//parses lable from file stream
void parse_label(char *str){
	char *tmp;
	tmp = str;
	tmp++;

	while(*tmp!=')'){
		*str=*tmp;
		str++;
		tmp++;
	}
	*str='\0';
}

//cleans string from useless spaces
void cl_space(char *str){
	char *tmp;
	tmp = str;
	while((*tmp!='\0')&&(*tmp!='/')&&(*tmp!='\n')&&(*tmp!='\r')&&(*tmp!='(')&&(*tmp!='\t')){
		if(*tmp!=' '){
			*str=*tmp;
			str++;
		}
		tmp++;
	}
	*str = '\0';
}

//parses symbols from file stream
void parse_symb(char *str){
	char *tmp;
	tmp = str;
	if(*tmp == '@'){
		tmp++;
	}

	while(*tmp != '\0'){
		*str = *tmp;
		str++;
		tmp++;
	}
	*str = '\0';
}
