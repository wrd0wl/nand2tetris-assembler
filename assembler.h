#define ROW 100

typedef struct list_symb{
	char symb [ROW];
	int address;
	struct list_symb* next;
}list;

long long int dec_to_bin(int val);

int char_to_int(int n, char *str);

void int_to_char(long long int val, char *string);

int bool_compare(char *str1, char *str2);

void copy_comp(char *str1, char *str2);

void copy_dest(char *str1, char *str2);

void copy_jump(char *str1, char *str2);

int bool_preset(char *str);

void find_preset(char *str1);

void push_symb(list** head, char *str, int n);

int bool_symb(list* head, char *str);

void find_address_symb(list* head, char *str);

void exchange(char *str1, char *str2);

void a_instr(char *str);

void c_instr(char *str);

void parse_symb(char *str);

void parse_label(char *str);

void cl_space(char *str);


