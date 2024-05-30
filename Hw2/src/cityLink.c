#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/** @brief Represents a city.
 *
 *   A city has a number assigned to it and points to the next city of the path.
 */
typedef struct city
{
    int number;
    struct city *next;
} CITY;

/** @brief Represents a path from a starting city to an end city.
 *
 *  Has a size corresponding to the number of cities in the path and
 *  a pointer head to the first city of the path.
 */
typedef struct
{
    int size;
    CITY *head;
} PATH;

/** @brief Starts executing all the procedures of the program.
 *
 *   Declares necessary variables and calls the functions for each procedure.
 *
 *   @param argc number of arguments in command line
 *   @param argv the arguments in command line
 *   @return void
 */
void start(int argc, char **argv);

/** @brief Reads the user input.
 *
 *   The input is given as command line arguments. Reads the desired options
 *   for output and the the filename for the cities.
 *
 *   @param argc     number of arguments in command line
 *   @param argv     the arguments in command line
 *   @param i_flag   flag for filename
 *   @param r_flag   flag possible path check
 *   @param p_flag   flag to print transitive closure
 *   @param o_flag   flag to print transitive closure in an output file
 *   @param filename the file to read the cities from
 *   @param cities   the cities to find the transitive closure of
 *   @return void
 */
void read_user_input(int argc, char **argv, int *i_flag, int *r_flag, int *p_flag, int *o_flag,
                     char **filename, char **cities);

/** @brief Reads the cities from specified input file.
 *
 *   Saves the input in a table and prints it in the console.
 *
 *   @param filename       the file to read the cities from
 *   @param N              the size of the table
 *   @param neighbor_table the table to save the input from the file
 *   @return void
 */
void read_neighbor_table(char *filename, int *N, int ***neighbor_table);

/** @brief Gets the starting and ending city from the input string.
 *
 *   If the format of the input string for the cities is invalid,
 *   the program is terminated.
 *
 *   @param cities     the string to extract the cities from
 *   @param start_city the starting city
 *   @param end_city   the ending city
 *   @return void
 */
void get_cities(char *cities, int *start_city, int *end_city);

/** @brief Initializes the transitive closure table.
 *
 *   Uses the neighbor table for the initialization.
 *
 *   @param transitive_closure the transitive closure table to initialize
 *   @param tc_size            the size of the transitive closure table
 *   @param neighbor_table     the table to use for the initialization
 *   @param N                  the size of the neighbor table
 *   @return void
 */
void init_transitive_closure(PATH **transitive_closure, int *tc_size, int **neighbor_table, int N);

/** @brief Inserts a new city in the specified Path of cities.
 *
 *   The new city has the specified city_number. If the city is the first of the path, the city
 *   becomes the head of the path.
 *
 *   @param path        the path of cities
 *   @param city_number the number of the new city
 *   @return void
 */
void insert_city(PATH *path, int city_number);

/** @brief Builds the transitive closure table.
 *
 *   Goes through all the existing Paths in the transitive closure table and
 *   builds new by comparing them to the ones in neighbor table.
 *
 *   @param transitive_closure the transitive closure table to build
 *   @param tc_size            the size of the transitive closure table
 *   @param neighbor_table     the table to compare the existing paths
 *   @param N                  the size of the neighbor table
 *   @return void
 */
void build_transitive_closure(PATH **transitive_closure, int *tc_size, int **neighbor_table, int N);

/** @brief Checks for repetition of paths in the transitive closure table.
 *
 *   Compares the specified starting and ending cities with the starting and ending cities 
 *   for each path in the transitive closure table.
 *  
 *   @param start              the starting city
 *   @param end                the ending city
 *   @param transitive_closure the transitive closure table to build
 *   @param tc_size            the size of the transitive closure table
 *   @return 1 if path already exists or 0 otherwise
 */
int check_repetition(int start, int end, PATH *transitive_closure, int tc_size);

/** @brief Copies the old path to the new path.
 *   
 *   Inserts each city one by one.
 *  
 *   @param new_path the new path
 *   @param old_path the old path to copy
 *   @return void
 */
void copy_path(PATH *new_path, PATH old_path);

/** @brief Checks the transitive closure table for possible path between specified cities.
 * 
 *   @param transitive_closure the transitive closure table 
 *   @param tc_size            the size of the transitive closure table 
 *   @param start_city         the starting city for the path to check
 *   @param end_city           the ending city for the path to check
 *   @return void
 */
void check_for_path(PATH *transitive_closure, int tc_size, int start_city, int end_city);

/** @brief Prints the transitive closure table.
 *
 *   @param transitive_closure the transitive closure table to print
 *   @param tc_size            the size of the transitive closure table
 *   @return void
 */
void print_transitive_closure(PATH *transitive_closure, int tc_size);

/** @brief Prints the successful path.
 *
 *   @param transitive_closure the transitive closure table to get the path from
 *   @param index              the index of the successful path
 *   @return void
 */
void print_successful_path(PATH *transitive_closure, int index);

/** @brief Saves the transitive closure table in an output file.
 * 
 *   Output file name uses input file name.
 *
 *   @param transitive_closure the transitive closure table to save
 *   @param tc_size            the size of the transitive closure table
 *   @param filename           the name of the input file
 *   @return void
 */
void save_transitive_closure(PATH *transitive_closure, int tc_size, char* filename);

/************************** Function definitions **************************/

void start(int argc, char **argv)
{
    int i_flag = 0, r_flag = 0, p_flag = 0, o_flag = 0; /* options the user chooses */
    char *filename = NULL;
    char *cities = NULL;
    int **neighbor_table = NULL;
    int N; /* the size of the neighbor table */
    int start_city, end_city;

    /* Transitive closure is a 1D array of Paths between cities. */
    PATH *transitive_closure = NULL;
    int tc_size = 0; /* size of transitive closure array */

    read_user_input(argc, argv, &i_flag, &r_flag, &p_flag, &o_flag, &filename, &cities);
    read_neighbor_table(filename, &N, &neighbor_table);

    init_transitive_closure(&transitive_closure, &tc_size, neighbor_table, N);
    build_transitive_closure(&transitive_closure, &tc_size, neighbor_table, N);

    if (p_flag == 1)
    {
        print_transitive_closure(transitive_closure, tc_size);
    }

    for (int i = 0; i < N; i++)
    {
        free((neighbor_table)[i]);
    }    
    free(neighbor_table);

    if (r_flag == 1)
    {
        get_cities(cities, &start_city, &end_city);        
        check_for_path(transitive_closure, tc_size, start_city, end_city);
    }    

    if (o_flag == 1)
    {
        save_transitive_closure(transitive_closure, tc_size, filename);
    }

    /* Goes through all the cities in the transitive closure table and frees them from memory. */
    for (int i = 0; i < tc_size; i++)
    {
        CITY *q = transitive_closure[i].head;
        CITY *tmp = NULL; /* to save the current city, in order to free it */

        while (q->next != NULL)
        {
            free(tmp);
            tmp = q;
            q = q->next;            
        }
        free(tmp);
    }
    free(transitive_closure);      
}

void read_user_input(int argc, char **argv, int *i_flag, int *r_flag, int *p_flag, int *o_flag,
                     char **filename, char **cities)
{
    int option; /* to save the command line options */

    /* If argc == 1(the program name), then no arguments have been given. */
    if (argc == 1)
    {
        printf("No command line arguments given!\n");
        printf("Usage: <executable> -i <inputfile> [-r <source >,<destination> -p -o]\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Scans the command line arguments and searches for options 'i', 'r', 'p' and 'o'.
     */
    while ((option = getopt(argc, argv, "i:r:po")) != -1)
    {
        switch (option)
        {
        case (int)'i':
            /* iFlag is used to just make sure the input file has been provided. */
            *i_flag = 1;
            *filename = optarg;
            break;
        case (int)'r':
            *r_flag = 1;
            *cities = optarg;
            break;
        case (int)'p':
            *p_flag = 1;
            break;
        case (int)'o':
            *o_flag = 1;
            break;

        /* Case when an unrecognized option is given or there is a missing argument. */
        case (int)'?':
            /*
             * Case '?' means there is an error with arguments, therefore the program
             * needs to be terminated.
             */
            printf("Usage: <executable> -i <inputfile> [-r <source >,<destination> -p -o]\n");
            exit(EXIT_FAILURE);
        }
    }
    /* Checks whether the input file has been provided. */
    if (*i_flag == 0)
    {
        printf("No input file given!\n");
        exit(EXIT_FAILURE);
    }
}

void read_neighbor_table(char *filename, int *N, int ***neighbor_table)
{
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Input file cannot be read!\n");
        exit(EXIT_FAILURE);
    }

    /* Reads N from input file. */
    fscanf(fp, "%d", N);

    /* Reserves space for N pointers that point to integer pointers. */
    *neighbor_table = (int **)malloc(*N * sizeof(int *));

    if (*neighbor_table == NULL)
    {
        printf("Error: Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    /* For each pointer i reserves space for N integers. */
    for (int i = 0; i < *N; i++)
    {
        (*neighbor_table)[i] = (int *)malloc(*N * sizeof(int));

        if ((*neighbor_table)[i] == NULL)
        {
            printf("Error: Could not allocate memory\n");
            exit(EXIT_FAILURE);
        }
    }

    /* Reads the input file and saves the values in the neighbor_table. */
    for (int i = 0; i < *N; i++)
    {
        for (int j = 0; j < *N; j++)
        {
            fscanf(fp, "%d", &((*neighbor_table)[i][j]));
        }
    }
    fclose(fp);

    printf("Neighbor table\n");

    /* Prints the neighbor_table. */
    for (int i = 0; i < *N; i++)
    {
        for (int j = 0; j < *N; j++)
        {
            printf("%d ", (*neighbor_table)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void get_cities(char *cities, int *start_city, int *end_city)
{
    int comma_index = 0;
    int error = 0;
    char *start_city_str = NULL;
    char *end_city_str = NULL;

    for (int i = 0; i < strlen(cities); i++)
    {
        /* If a character is the first comma save its index. */
        if (*(cities + i) == ',')
        {
            if (comma_index == 0)
            {
                comma_index = i;
            }
            /* If it is a comma, but not the first one, the argument is invalid. */
            else
            {
                error = 1;
                break;
            }
        }
        /* If a character is not a comma and not a number argument is invalid. */
        else if (*(cities + i) < '0' || *(cities + i) > '9')
        {
            error = 1;
            break;
        }
    }

    /* If there is no comma, the argument is invalid. */
    if (comma_index == 0)
    {
        error = 1;
    }

    /* 
    * If the character right after the comma is the null character, then no second 
    * number has been provided.
    */
    if (*(cities + comma_index + 1) == '\0')
    {
        error = 1;
    }

    if (error == 1)
    {
        printf("Invalid destination argument\n");
        printf("Destination format: -r number1,number2\n");
        exit(EXIT_FAILURE);
    }

    start_city_str = (char *)malloc(comma_index + 1);
    end_city_str = (char *)malloc(strlen(cities) - comma_index + 1);

    if (start_city_str == NULL || end_city_str == NULL)
    {
        printf("Error: Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    /* In order to not lose the starting address of the strings. */
    char *temp_start_city = start_city_str;
    char *temp_end_city = end_city_str;

    /* Saves the first number in start_city_str. */
    for (; *(cities) != ','; cities++, temp_start_city++)
    {
        *temp_start_city = *cities;
    }
    *temp_start_city = '\0';

    cities++; /* To skip the ','. */

    /* Saves the second number in end_city_str. */
    for (; *(cities) != '\0'; cities++, temp_end_city++)
    {
        *temp_end_city = *cities;
    }
    *temp_end_city = '\0';

    *start_city = atoi(start_city_str);
    *end_city = atoi(end_city_str);

    free(start_city_str);
    free(end_city_str);
}

void init_transitive_closure(PATH **transitive_closure, int *tc_size, int **neighbor_table, int N)
{
    /* Initialize table with malloc, so realloc can be used later. */
    *transitive_closure = (PATH *)malloc(sizeof(PATH));

    if (*transitive_closure == NULL)
    {
        printf("Error: Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            /* Ignore self-references. */
            if (i == j)
            {
                continue;
            }
            /* If a value in the table is 1, then city i connects with city j. */
            if (neighbor_table[i][j] == 1)
            {
                (*tc_size)++;

                /* Increase the transitive closure array to new size. */
                PATH *tmp = (PATH *)realloc(*transitive_closure, (*tc_size) * sizeof(PATH));

                if (tmp == NULL)
                {
                    printf("Error: Unable to Allocate Memory using realloc\n");
                    exit(EXIT_FAILURE);
                }

                *transitive_closure = tmp;

                /* Initial values for Paths. */
                (*transitive_closure)[*tc_size - 1].head = NULL;
                (*transitive_closure)[*tc_size - 1].size = 0;

                /* Insert first city in the new Path. */
                insert_city(&((*transitive_closure)[*tc_size - 1]), i);

                /* Insert second city in the new Path. */
                insert_city(&((*transitive_closure)[*tc_size - 1]), j);
            }
        }
    }
}

void insert_city(PATH *path, int city_number)
{
    CITY *q = NULL; /* helping pointer to go through the list */
    CITY *new_city = (CITY *)malloc(sizeof(CITY));

    if (new_city == NULL)
    {
        printf("Error: Unable to Allocate Memory \n");
        exit(EXIT_FAILURE);
    }

    new_city->next = NULL;
    new_city->number = city_number;

    /* If path is empty, add the new city as the head of the path. */
    if (path->head == NULL)
    {
        path->head = new_city;
    }
    /* If path is not empty, go through the list and add the new city at the end. */
    else
    {
        q = path->head;

        while (q->next != NULL)
        {
            q = q->next;
        }

        q->next = new_city;
    }
    (path->size)++;
}

void build_transitive_closure(PATH **transitive_closure, int *tc_size, int **neighbor_table, int N)
{
    /* Iterates through the transitive closure table. */
    for (int i = 0; i < *tc_size; i++)
    {        
        CITY *q = (*transitive_closure)[i].head; /* helping pointer to go through the list */
        
        /* q gets the poiner of the last city of the current path. */
        while (q->next != NULL)
        {               
            q = q->next;           
        }    

        /* Iterates through the elements of neighbor table. */
        for (int k = 0; k < N; k++)
        {             
            for (int l = 0; l < N; l++)
            {        
                /* Ignore self-references. */
                if ((*transitive_closure)[i].head->number == l)
                {
                    continue;
                }   
                
                /* 
                * If k is mutual for current path and neighbor path, then add the
                * combined path to the transitive closure if it has not already been added.          
                */
                if (q->number == k && neighbor_table[k][l] == 1)
                {                      
                    if (check_repetition((*transitive_closure)[i].head->number, l,
                                          *transitive_closure, *tc_size) == 1)
                    {
                        continue;
                    }

                    (*tc_size)++;

                    /* Increase the transitive closure array to new size. */
                    PATH *tmp = (PATH *)realloc(*transitive_closure, (*tc_size) * sizeof(PATH));

                    if (tmp == NULL)
                    {
                        printf("Error: Unable to Allocate Memory using realloc\n");
                        exit(EXIT_FAILURE);
                    }

                    *transitive_closure = tmp;
                     
                    /* Initial values for Paths. */
                    (*transitive_closure)[*tc_size - 1].head = NULL;
                    (*transitive_closure)[*tc_size - 1].size = 0;

                    /* Copies old path to the new one, before adding the last city. */
                    copy_path(&((*transitive_closure)[*tc_size - 1]), (*transitive_closure)[i]);

                    /* Insert last city in the new Path. */
                    insert_city(&((*transitive_closure)[*tc_size - 1]), l);                    
                }
            }
        }
    }
}

int check_repetition(int start, int end, PATH *transitive_closure, int tc_size)
{
    CITY *q = NULL; /* helping pointer to go through the list */

    /* Iterates through the transitive closure table. */
    for (int i = 0; i < tc_size; i++)
    {
        q = transitive_closure[i].head;

        /* Makes q point at the last city of each path. */
        while (q->next != NULL)
        {
            q = q->next;
        }
        /* 
        * If the starting cities are equal and the ending cities are equal, then the 
        * repetition is true. 
        */
        if (start == transitive_closure[i].head->number && end == q->number)
        {
            return 1;
        }
    }
    return 0;
}

void copy_path(PATH *new_path, PATH old_path)
{
    CITY *q = old_path.head; /* helping pointer to go through the list */

    /* For each city number in the old path, insert a new city in the new path. */
    for (int i = 0; i < old_path.size; i++)
    {
        insert_city(new_path, q->number);
        q = q->next;
    }
}

void check_for_path(PATH *transitive_closure, int tc_size, int start_city, int end_city)
{
    CITY *q = NULL; /* helping pointer to go through the list */
    
    /* Iterates throug the transitive closure table. */
    for (int i = 0; i < tc_size; i++)
    {     
        q = transitive_closure[i].head;

        /* Makes q point to the last city of each path. */
        while (q->next != NULL)
        {
            q = q->next;
        }

        /* 
        * If the start city equals the city of the current i path and the end city
        * equals the last city of the current i path then the path exists.
        */
        if (start_city == (transitive_closure[i].head->number) && end_city == (q->number))
        {
            printf("Yes Path Exists!\n");
            print_successful_path(transitive_closure, i);
            return;
        }       
    }
    printf("No Path Exists!\n");
}

void print_transitive_closure(PATH *transitive_closure, int tc_size)
{
    CITY *q = NULL; /* helping pointer to go through the list */

    printf("R* table\n");

    /* Goes through all the paths in the transitive closure table. */
    for (int i = 0; i < tc_size; i++)
    {
        q = transitive_closure[i].head;
        printf("%d -> ", q->number);

        /* Makes q point to the last city of the current path. */
        while (q->next != NULL)
        {            
            q = q->next;
        }
        printf("%d\n", q->number);
    }
}

void print_successful_path(PATH *transitive_closure, int index)
{
    CITY *q = NULL; /* helping pointer to go through the list */
    
    q = transitive_closure[index].head;

    /* q goes through the cities of the successful path.*/
    while (q->next != NULL)
    {
        printf("%d => ", q->number);
        q = q->next;
    }
    printf("%d\n", q->number);
}

void save_transitive_closure(PATH *transitive_closure, int tc_size, char *filename)
{
    CITY *q = NULL; /* helping pointer to go through the list */
    char *output_filename = (char *)malloc((strlen(filename) + 10) * sizeof(char));

    if (output_filename == NULL)
    {
        printf("Error: Unable to Allocate Memory \n");
        exit(EXIT_FAILURE);
    }

    /* Builds the output file name. */
    strcpy(output_filename, "out-");
    strcat(output_filename, filename);  

    FILE *fp = NULL;

    if ((fp = fopen(output_filename, "w")) == NULL)
    {
        printf("Error: Unable to create \"%s\" output file\n", output_filename);
        exit(EXIT_FAILURE);
    }

    printf("Saving %s...\n", output_filename);

    fprintf(fp, "R* table\n");

    /* Goes through all the paths in the transitive closure table. */
    for (int i = 0; i < tc_size; i++)
    {
        q = transitive_closure[i].head;
        fprintf(fp, "%d -> ", q->number);

        /* Makes q point to the last city of the current path. */
        while (q->next != NULL)
        {            
            q = q->next;
        }
        fprintf(fp, "%d\n", q->number);
    }
    
    free(output_filename);
    fclose(fp);
}

/** @brief Program entrypoint.
 * 
 *   Calls start(argc, argv).
 * 
 *   @param argc number of arguments in command line
 *   @param argv the arguments in command line
 */
int main(int argc, char **argv)
{
    start(argc, argv);
    return 0;
}