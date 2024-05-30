#include "prob_table.h"

int const MAX_ASCII = 128;

void generate_prob_table(char *sample_file, char *prob_file)
{
    int i = 0;
    /* 
     * Array for the count of each character. Each index of the array corresponds to
     * the ASCII value of each character and each element to the count of each character.
    */
    int *count_char = (int*) malloc(MAX_ASCII * sizeof(int)); 
    float *prob_table = (float*) malloc(MAX_ASCII * sizeof(float));
    int count_total = 0;  /* Counter for the sum of counts of all the characters. */ 

    if (count_char == NULL || prob_table == NULL)
    {
        printf("Error: Could not allocate memory using malloc\n");
        exit(EXIT_FAILURE);
    }

    /* Initializes countar_char and prob_table arrays to 0. */
    for (i = 0; i < MAX_ASCII; i++)
    {
        count_char[i] = 0;
        prob_table[i] = 0.0;
    }

    count_characters(sample_file, count_char, &count_total);  
    calc_probability(count_char, count_total, prob_table);  
    export_prob_table(prob_table, prob_file);  
    
    free(count_char); 
    free(prob_table);   
}

void count_characters(char *sample_file, int *count_char, int *count_total)
{    
    char character = 0;
    FILE *fp = NULL;
    if ((fp = fopen(sample_file, "r")) == NULL)
    {
        printf("\"%s\" file cannot be opened\n", sample_file);
        exit(EXIT_FAILURE);
    }

    while ((character = fgetc(fp)) != EOF)
    {        
        /* Checks if a character is within the ASCII range specified by MAX_ASCII constant. */
        if (character >= MAX_ASCII)
        {
            printf("File cannot have ASCII characters with value above 127\n");
            exit(EXIT_FAILURE);
        }
        
        count_char[(int) character]++;
        (*count_total)++;
    }
    fclose(fp);
}

void calc_probability(int *count_char, int count_total, float *prob_table)
{
    int i = 0;
    /* 
    * Calculates the probability of each character appearing by dividing the count
    * of its appearances with the total amount of characters.
    */
    for (i = 0; i < MAX_ASCII; i++)
    {
        prob_table[i] = ((float)count_char[i]) / ((float)count_total);
    }
}

void export_prob_table(float *prob_table, char *prob_file)
{
    int i = 0;
    FILE *fp = NULL;

    if ((fp = fopen(prob_file, "w")) == NULL)
    {
        printf("Error: Unable to create \"%s\" output file\n", prob_file);
        exit(EXIT_FAILURE);
    }

    /* Iterates through the probability table and saves each value in prob_file. */
    for (i = 0; i < MAX_ASCII - 1; i++)
    {
        fprintf(fp, "%.10f\n", prob_table[i]);
    }
    printf("Character probabilities saved in \"%s\"\n", prob_file);
    fprintf(fp, "%.10f", prob_table[i]);
    fclose(fp);
}

#ifdef TEST_P
int main(int argc, char **argv)
{
    char *sample_file = argv[1];
    char *prob_file = argv[2];

    generate_prob_table(sample_file, prob_file);
    return 0; 
}
#endif