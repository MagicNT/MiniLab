

//##################################//
//##################################//
//#@#//                        //#@#// 
//#@#//    TITLE:  MINILAB     //#@#// 
//#@#//    AUTHOR: TONY NASR   //#@#// 
//#@#//                        //#@#// 
//##################################//
//##################################//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define white   "\x1B[0m"
#define red     "\x1B[1;31m"
#define green   "\x1B[1;32m"
#define yellow  "\x1B[1;33m"
#define blue    "\x1B[1;34m"
#define magenta "\x1B[1;35m"
#define cyan    "\x1B[1;36m"    
#define L 19
#define N 200005
#define mod 1000000007
#define MAX_ARRAY_SIZE 100
#define NUMBER_OF_VARIABLES 20
#define VERIFY_FORWARD_SPACES(value) \
                    for (int j = (value); args[j] != '\n'; j++) { \
                        if (args[j] != ' ') {  check_comd = 1; error_msg (1); break; \
                        }                      \
                    }      
#define VERIFY_BACKWARD_SPACES \
                    for (int j = 0; j < i; j++) { \
                        if (args[j] != ' ') {  check_comd = 1; error_msg (1); break; \
                        }                      \
                    }  

char header_color [10] = cyan;
long long data [L][N];
long long Pascal [L][L];
long long count [N];

////////////////////////////////////////////////////////////////////////////////////////////////

void banner () {
    
    srand(time(NULL));
    int id = rand() % 4;
    switch (id) { 
        case 0: 
            printf ("\n");
            printf ("%s  __  __ ___ _   _ ___       %s_        _    ____          \n", header_color, yellow);
            printf ("%s |  \\/  |_ _| \\ | |_ _| %s _  %s| |      / \\  | __ )    \n", header_color, white, yellow);
            printf ("%s | |\\/| || ||  \\| || | %s (_) %s| |     / _ \\ |  _ \\   \n", header_color, white, yellow);
            printf ("%s | |  | || || |\\  || | %s  _  %s| |___ / ___ \\| |_) |    \n", header_color, white, yellow);
            printf ("%s |_|  |_|___|_| \\_|___|%s (_) %s|_____/_/   \\_\\____/    \n\n", header_color, white, yellow);    
            printf ("             %s ###> %sAuthor: %sTony Nasr                   \n", green, header_color, yellow);
            printf ("                                   \n\n%s", white);
            break;      
        case 1:
            printf ( "\n%s" \ 
"                        MINI%s                                 \n" \                    
"            _|          _|_|    _|_|_|                         \n" \
"            _|        _|    _|  _|    _|                       \n" \
"            _|        _|_|_|_|  _|_|_|                         \n" \
"            _|        _|    _|  _|    _|                       \n" \
"            _|_|_|_|  _|    _|  _|_|_|                         \n\n" \
"                %s###> %sAuthor: %sTony Nasr                   \n" \
"                               \n\n%s", yellow, header_color, green, header_color, yellow, white);
            break;        
        case 2:
            printf ( "\n%s" \
"              __  ___   ____   _   __   ____                   \n" \
"             /  |/  /  /  _/  / | / /  /  _/                   \n" \
"            / /|_/ /   / /   /  |/ /   / /                     \n" \
"           / /  / /  _/ /   / /|  /  _/ /                      \n" \
"          /_/  /_/  /___/  /_/ |_/  /___/                      \n" \ 
"                         %sLAB                                 \n\n"  \       
"                %s###> %sAuthor: %sTony Nasr                   \n" \                    
"                            \n\n%s", header_color, yellow, green, header_color, yellow, white);
            break;           
        case 3:
            printf ("\n");
            printf ("%s              __  __    %s   _                             \n", header_color, yellow);     
            printf ("%s             |  \\/  |  %s   | |                           \n", header_color, yellow); 
            printf ("%s             | |\\/| |  %s   | |                           \n", header_color, yellow); 
            printf ("%s             | |  | | %s _  %s| |___  %s _                 \n", header_color, white, yellow, white); 
            printf ("%s             |_|  |_|%s (_) %s|_____| %s(_)                \n\n", header_color, white, yellow, white); 
            printf ("%s              ###> %sAuthor: %sTony Nasr                   \n", green, header_color, yellow);
            printf ("%s                             \n\n", white);
            break;       
    }  
}

////////////////////////////////////////////////////////////////////////////////////////////////

void error_msg (int code) {
    
    switch (code) {
        case 0: printf (" %s[%sX%s] Unknown Command%s.%s\n\n", white, red, white, red, white);                break;          
        case 1: printf (" %s[%sX%s] Invalid Usage%s.%s\n\n", white, red, white, red, white);                  break;         
        case 2: printf (" %s[%sX%s] Wrong Syntax%s.%s\n\n", white, red, white, red, white);                   break;            
        case 3: printf (" %s[%sX%s] Specified File Does Not Exist%s.%s\n\n", white, red, white, red, white);  break;    
        case 4: printf (" %s[%sX%s] Must Provide 2 Arguments%s.%s\n\n", white, red, white, red, white);       break; 
        case 5: printf (" %s[%sX%s] Invalid Command%s.%s\n\n", white, red, white, red, white);                break; 
        case 6: printf (" %s[%sX%s] Variable Does Not Exist%s.%s\n\n", white, red, white, red, white);        break; 
        case 7: printf (" %s[%sX%s] Matrix Dimension Mismatch%s.%s\n\n", white, red, white, red, white);      break;         
        case 8: printf (" %s[%sX%s] Invalid Matrix Operation%s.%s\n\n", white, red, white, red, white);       break; 
    } 
} 

////////////////////////////////////////////////////////////////////////////////////////////////

void help () {

    printf ("\n");
    printf ("  %sAvailable Commands%s:                                              \n", header_color, green);              
    printf ("  %s------------------                                               \n\n", yellow);           
    printf ("         %shelp     %s---%s  Display This Help Message                 \n", header_color, yellow, header_color);
    printf ("         %scolor    %s---%s  Change MiniLab Main Color                 \n", header_color, yellow, header_color);
    printf ("         %sbanner   %s---%s  Display Fun MiniLab Banners               \n", header_color, yellow, header_color);            
    printf ("         %sclean    %s---%s  Clean Screen                              \n", header_color, yellow, header_color);
//    printf ("         %serase    %s---%s  Erase All Saved Data                      \n", header_color, yellow, header_color); 
//    printf ("         %spyramid  %s---%s  Calculate Pyramid Combinations            \n", header_color, yellow, header_color);                 
    printf ("         %sexit     %s---%s  Exit MiniLab                          %s\n\n", header_color, yellow, header_color, white);
}

////////////////////////////////////////////////////////////////////////////////////////////////

void change_header (char *color) {
    
    for (int i = 0; i < strlen(color); i++)
        header_color[i] = color[i];
}

int verify_color_spaces (char *s, int start) {
    
    for (int i = start; s[i] != '\n'; i++)
        if (s[i] != ' ')
            return 0;
    return 1;
}

void color (char *s, int start) {
    
    if (cmp("red", s, start, start+2) && verify_color_spaces(s, start+3))
        change_header(red);
    else if (cmp("green", s, start, start+4) && verify_color_spaces(s, start+5))
        change_header(green);
    else if (cmp("yellow", s, start, start+5) && verify_color_spaces(s, start+6))
        change_header(yellow);
    else if (cmp("magenta", s, start, start+6) && verify_color_spaces(s, start+7))
        change_header(magenta);
    else if (cmp("cyan", s, start, start+3) && verify_color_spaces(s, start+4))
        change_header(cyan);
    else if (cmp("blue", s, start, start+3) && verify_color_spaces(s, start+4))
        change_header (blue);
    else
        error_msg (1);
}

////////////////////////////////////////////////////////////////////////////////////////////////

int cmp (char *s1, char *s2, int start, int end) {
    
    char *ptr = s1;
    for (int i = start; i <= end; i++, ptr++)
        if (s2[i] != *ptr)
            return 0;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct { int rows; int cols; int **data;    } matrix;
typedef union  { int n; matrix *mt;                 } Type;
typedef struct { char name[50]; int id; Type value; } var; 

int empty [MAX_ARRAY_SIZE];
var container [NUMBER_OF_VARIABLES];
int var_count = 0, nRows = 1, nCols = 0;

////////////////////////////////////////////////////////////////////////////////////////////////

double **create_array (int rows, int cols) {
    int **p = (int **)(malloc(rows * sizeof(int *)));
    if (!p)
        return NULL;
    int *q = (int *)(malloc(rows * cols *sizeof(int)));
    if (!q)
        return NULL;
    for (int i = 0; i < rows; i++, q += cols)
        p[i] = q;
    return p;
}

matrix *create_matrix (int rows, int cols, int *array) {
    
    matrix *m = (matrix *)(malloc (sizeof(matrix)));
    
    m->rows = rows;
    m->cols = cols;
    m->data = create_array (rows, cols);
    
    if (m->data) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                m->data[i][j] = array [j + (i*cols)];   
        return m;
    }
    return NULL;
}

int convert_to_int (char c) {
    char a = '0';
    for (int i = 0; a < '10'; i++, a++)
        if (a == c)
            return i; 
}

void print_matrix (matrix *mt) {

    int rows = mt->rows;
    int cols = mt->cols;
    printf ("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf ("  %d   ", mt->data[i][j]);
        printf ("\n\n");  
    }
    printf ("\n");
}

void print_array (int *ar, int  rows, int cols)  {
    if (!ar[0])
        goto NOA;
    printf ("\n");
    for (int i = 1; i < rows*cols+1; i++) {
        printf ("  %d   ", ar[i-1]);
        if (i%cols==0)
            printf ("\n\n");            
    }
    printf ("\n");
    NOA: printf ("");
}

////////////////////////////////////////////////////////////////////////////////////////////////

matrix *multiply_matrices (matrix *mt1, matrix *mt2) {

    int r1 = mt1->rows, c1 = mt1->cols, r2 = mt2->rows, c2 = mt2->cols;
    int array [r1*c2], ar_count = 0, temp = 0;
    
    for (int row = 0; row < r1; row++) {
        for (int col = 0; col < c2; col++) {
            for (int index = 0; index < r2; index++) {
                temp += mt1->data[row][index] * mt2->data[index][col];
            }
            array [ar_count++]= temp;
            temp = 0;
        }
    }
    
    
    return create_matrix (r1, c2, array); 
}

matrix *sum_sub_matrices (matrix *mt1, matrix *mt2, int op) {
    
    int rows = mt1->rows, cols = mt1->cols; 
    int array [rows*cols], ar_count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (op == 0)
                array [ar_count++] = (mt1->data[i][j]+mt2->data[i][j]);
            else
                array [ar_count++] = (mt1->data[i][j]-mt2->data[i][j]); 
        
    return create_matrix (rows, cols, array);
}

////////////////////////////////////////////////////////////////////////////////////////////////

int is_number (char * str) {
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void main (int argc, char** argv) {

    int argn = 0;
    if (argc != 0)
        argn = argc - 1;
       
    if (argc == -1 || argn == 1 && !strcmp(argv[1], "--start")) {

        if (argn == 1 && !strcmp(argv[1], "--start")) {
            banner();
            printf ("\n %sType %s\'help\' %sTo See Available Commands.\n\n", magenta, yellow, magenta);
        }
        
        int check_equal = 0,
            check_first_bracket = 0,
            check_second_bracket = 0,
            check_end_line = 0,    
            check_comd = 0,
            equal_location = 0;
        
        char args [100];
        
        printf ("%s#%sMini%sLab%s#%s>%s ", yellow, header_color, yellow, header_color, green, header_color);
 
        if (fgets(args, 100, stdin)) {
            
            for (int i = 0; args[i] != '\n'; i++) {

                if (cmp("help", args, i, i+3)) {
                    VERIFY_FORWARD_SPACES(i+4)
                    VERIFY_BACKWARD_SPACES                            
                    if (!check_comd)
                        help();
                    break;
                }
                else if (cmp("color", args, i, i+4)) {
                    color(args, i+6);
                    break;
                }
                else if (cmp("clean", args, i, i+4)) {
                    VERIFY_FORWARD_SPACES(i+5)
                    VERIFY_BACKWARD_SPACES 
                    if (!check_comd)
                        system("reset");
                    break;
                }               
                else if (cmp("banner", args, i, i+5)) {
                    VERIFY_FORWARD_SPACES(i+6)
                    VERIFY_BACKWARD_SPACES 
                    if (!check_comd)
                        banner();
                    break;
                }
//                else if (cmp("erase", args, i, i+4)) {
//                    VERIFY_FORWARD_SPACES(i+5)
//                    VERIFY_BACKWARD_SPACES 
//                    if (!check_comd) {
//                        erase();
//                        printf ("%s[%sV%s] %sAll Saved Data Got Erased%s", white, header_color, white, magenta, white);
//                        var_count = 0;
//                    }
//                    break;
//                }
                else if (cmp("exit", args, i, i+3)) {
                    VERIFY_FORWARD_SPACES(i+4)
                    VERIFY_BACKWARD_SPACES 
                    if (!check_comd);
                       goto END;
                    break;
                }                 
                else if (args[i] == '=') {
                    if (!check_equal) {                 
                        check_equal = 1;
                        equal_location = i;
                        int var_name_start_1, var_name_start_2, var_name_end_1, var_name_end_2, op = 0, op_location, loc1, loc2;

                        for (int j = i; args[j] != '\n'; j++)
                            if (isalpha(args[j])) {
                                var_name_start_1 = j;
                                var_name_end_1 = j;
                                break;
                            }
                            else if (args[j] == '[') {
                                goto START;
                            }
                        for (int j = var_name_start_1+1; args[j] != '\n'; j++) {
                            if (isalpha(args[j]))
                                var_name_end_1++;
                            else 
                                break;
                        }

                        for (int u = 0; u < var_count; u++) {                                   
                            if (cmp(container[u].name, args, var_name_start_1, var_name_end_1)) {    
                                loc1 = u;

                                for (int j = var_name_end_1+1; args[j] != '\n'; j++) {
                                    if (args[j] == '*') {
                                        op = 2;
                                        op_location = j;
                                        break;
                                    }
                                    else if (args[j] == '-') {
                                        op = 1;
                                        op_location = j;
                                        break;
                                    }
                                    else if (args[j] == '+') {
                                        op = 0;
                                        op_location = j;
                                        break;
                                    } 
                                    else if (args[j] == ' ')
                                        continue;
                                    else {
                                        error_msg(8);
                                        goto HERE;
                                    }
                                }
                                

                                for (int p = op_location; args[p] != '\n'; p++) {
                                    if (isalpha(args[p])) {
                                        var_name_start_2 = p;
                                        var_name_end_2 = p;
                                        break;
                                    }
                                }
                                
                                for (int p = var_name_start_2+1; args[p] != '\n'; p++) {
                                    if (isalpha(args[p]))
                                        var_name_end_2++;
                                    else 
                                        break;
                                }   
                                
                                for (int w = 0; w < var_count; w++) {    
                                    if (cmp(container[w].name, args, var_name_start_2, var_name_end_2)) { 
                                        loc2 = w;    
                                        
                                        int var_name_end = 0, var_name_start = 0;                           
                                        for (int x = equal_location-1; x > 0; x--) {                              
                                            if (isalpha(args[x])) {                                  
                                                var_name_end = x;
                                                var_name_start = x;
                                                break;                               
                                            }                           
                                        }                         
                                        for (int y = 0; y < var_name_end; y++) {                            
                                            if (isalpha(args[y])) {                              
                                                var_name_start = y;                              
                                                break;                             
                                            }                         
                                        }

                                        container [var_count].id = 1;   
                                        
                                        if ((op == 0 || op == 1) && container[loc1].value.mt->rows == container[loc2].value.mt->rows && \
                                                container[loc1].value.mt->cols == container[loc2].value.mt->cols)
                                            container [var_count].value.mt = sum_sub_matrices (container[loc1].value.mt, container[loc2].value.mt, op);
                                        else if (op == 2 && container[loc1].value.mt->cols == container[loc2].value.mt->rows)
                                            container [var_count].value.mt = multiply_matrices (container[loc1].value.mt, container[loc2].value.mt);                        
                                        else {
                                            error_msg(7);
                                            goto HERE;
                                        }
                                                                              
                                        for (int s = 0, t = var_name_start;  t <= var_name_end; s++, t++)                              
                                            container [var_count].name[s] = args[t];                              
                                        printf ("\n %s%s%s = %s\n", header_color, container [var_count].name, yellow, header_color);                          
                                        print_matrix (container [var_count].value.mt);                          
                                        var_count++;                          
                                        memset(empty, 0, sizeof(empty)), equal_location = 0, op = 0;
                                        goto HERE;
                                    }                                    
                                }
                                error_msg(2);
                                goto HERE;
                            }                              
                        }                       
                    }
                    else {                       
                        error_msg (2);                   
                        break;              
                    }          
                }
                else if (args[i] == '[') {         
                    if (!check_first_bracket) {                 
                        check_first_bracket = 1;
                        int check_first_row = 0, col_counter = 0, index = 0;
                        for (int j = i+1; args[j] != '\n' && args[j] != ']'; j++) {                            
                            if (isdigit(args[j])) {
                                empty [index] = convert_to_int (args[j]);
                                col_counter++, index++; 
                            }
                            if (args[j] == ';') {                            
                                if (!check_first_row) {                                  
                                    check_first_row = 1;                                 
                                    nCols = col_counter;
                                }
                                if (check_first_row && col_counter != nCols) {   
                                    memset (empty, 0, sizeof(empty));
                                    nRows = 1;
                                    nCols = 0;
                                    error_msg(2); 
                                    goto JUMP;
                                }                                  
                                nRows++;                                
                                col_counter = 0;                               
                            }                                  
                        }
                        if (check_first_row && col_counter != nCols) {   
                            memset (empty, 0, sizeof(empty));
                            nRows = 1;
                            nCols = 0;
                            error_msg(2);
                            goto JUMP;
                        }                            
                        if (check_equal == 0) {
                            print_array (empty, nRows, nCols);
                        }              
                        else {
                            int var_name_end = 0, var_name_start = 0;
                            for (int x = equal_location-1; x > 0; x--) {
                                if (isalpha(args[x])) {
                                    var_name_end = x;
                                    break;
                                }
                            }
                            for (int y = 0; y < var_name_end; y++) {
                                if (isalpha(args[y])) {
                                    var_name_start = y;
                                    break;
                                }
                                    
                            }
                            
                            container [var_count].id = 1;
                            container [var_count].value.mt = create_matrix (nRows, nCols, empty); 
                            for (int s = 0, t = var_name_start;  t <= var_name_end; s++, t++)
                                container [var_count].name[s] = args[t];
                                printf ("\n %s%s%s = %s\n", header_color, container [var_count].name, yellow, header_color); 
                            print_array (empty, nRows, nCols);
                            var_count++;
                            nRows = 1, nCols = 0, memset(empty, 0, sizeof(empty)), equal_location = 0;
                        }
                        
                        JUMP: printf ("");
                    }
                    else {                 
                        error_msg (2);                   
                        break;              
                    }                  
                }                
                else if (args[i] == ']') {             
                    if (check_first_bracket && !check_second_bracket) {                 
                        check_second_bracket = 1;
                        for (int j = i + 1; args[j] != '\n'; j++) {
                            if (args[j] != ' ' && args[j] != ';') {                           
                                check_end_line = 1;  
                                error_msg (2);
                                break;
                            }
                        }                    
                    }
                    else {                   
                        error_msg(2);                   
                        break;   
                    }
                } 
                else if (args[i] == ';') {
                    for (int j = i+1; args[j] != '\n'; j++) {
                        if (args[j] == ';'){
                            for (int m = j; m >= (i+1); m--) {
                                if (args[m] != ' ') {
                                    goto JUMP;
                                }
                            }
                        }   
                    }
                }
                else if (isalpha(args[i])) {
                    int var_name_end = i, var_name_start = i, permission = 1;
                    for (int d = i+1; isalpha(args[d]); d++)
                        var_name_end++;
                    
                    for (int k = var_name_end+1; args[k] != '\n'; k++)
                        if (args[k] != ' ')
                            permission = 0;
                    
                    if (permission) {                 
                        for (int u = 0; u < var_count; u++)                  
                            if (cmp(container[u].name, args, var_name_start, var_name_end)) {                        
                                printf ("\n %s%s%s = %s\n", header_color, container [u].name, yellow, header_color);                       
                                print_matrix(container[u].value.mt);                            
                                goto HERE;               
                            }     
                        error_msg(6);
                        goto HERE;
                    }
                    continue;
                    
                }
                START:
                if (check_end_line || check_comd)
                    break;               
            }
            HERE:
            main (-1, NULL);
        }   
    }
    else {
               
        unsigned int num;
        
        if (argn > 4 || argn == 0){
            printf ("\n %s[%sM%sL%s] ERROR%s: Invalid Number Of Argument(s) %s!%s", red, cyan, yellow, red, magenta, red, white);     
            goto USAGE;                 
        }
        
        goto END;
        
        USAGE: 
        banner();
        printf ("                                                   \n" \ 
" %s[%sM%sL%s] %sUsage%s: %s%s %s<%sOPTIONS%s>                      \n" \
"      %s-----                                                    \n\n" \
" %s[%sM%sL%s] %sOPTIONS%s:                                       \n\n" \     
"           %s--%sstart   %s(%sStart MiniLab Console%s)             \n", red, cyan, yellow, red, yellow, red, cyan, argv[0], yellow, magenta, yellow, red, \
                                                              red, cyan, yellow, red, magenta, red, yellow, green, yellow, cyan, yellow, white);  

        END: printf ("");    
    }   
    
}

////////////////////////////////////////////////////////////////////////////////////////////////


