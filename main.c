#include "stdio.h"
#include "string.h"
#define BIT 17
#define ROW 100

#include "assembler.h"

int main(int argc, char *argv[]){
	char str[BIT], aux[ROW];
	list* list_lable=NULL;
	list* list_var=NULL;
	int address=0;

	FILE  *hack, *bin;
	
	if(argc > 3){
		printf("Error!");
	}
	
	else{
		hack = fopen(argv[1], "r");

		//reads file stream line by line, parses and pushes labels into the list
		while(fgets(aux, ROW, hack)!=NULL){
			if(aux[0]!='/'&&aux[0]!='\r'){
				if(aux[0]=='('){
					parse_label(aux);
					push_symb(&list_lable, aux, address);
				}
				else{
					address++;
				}
			}
		}

		fclose(hack);

		hack = fopen(argv[1], "r");
		bin = fopen(argv[2], "w");

		address = 16;

		//reads file stream line by line, gets hack instructions and converts into binary code
		while(fgets(aux, ROW, hack)!=NULL){
			
			//cleans from useless spaces from the beginning of the string
			cl_space(aux);
			
			//defines type of instruction
			if(aux[0]=='@'){
				parse_symb(aux);
					
				//A-instruction
				if(aux[0]>=48&&aux[0]<=57){			
					a_instr(aux);
					strcpy(str, aux);
				}

				//preset symbol table
				else if(bool_preset(aux)){			
					find_preset(aux);
					strcpy(str, aux);
				}

				//labels
				else if(bool_symb(list_lable, aux)){			
					find_address_symb(list_lable, aux);
					strcpy(str, aux);

				}

				//variables
				else{						
					if(bool_symb(list_var, aux) && !bool_symb(list_lable, aux)){
						find_address_symb(list_var, aux);
						strcpy(str, aux);
					}
					else if(!bool_symb(list_var, aux) && !bool_symb(list_lable, aux)){
						push_symb(&list_var, aux, address);
						int_to_char(dec_to_bin(address), str);
						address++;
					}
				}
			}
			else{	

				//C-instruction							
				if(aux[0]!='/'&&aux[0]!='\r'){
					parse_symb(aux);
					c_instr(aux);
					strcpy(str, aux);
				}
			}

			//prints only binary code into .hack file
			if(str[0]==48||str[0]==49){
				fprintf(bin, "%s\n", str);
			}

		}
	fclose(hack);
	fclose(bin);
	}
	return 0;
}

