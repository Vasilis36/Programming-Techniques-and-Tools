#include "huffman_tree.h"

NODE *generate_huffman_tree(char *prob_file)
{
    int i = 0;
    float *prob_table = NULL;         /* Probability table to fill with prob_file values. */
    NODE **character_trees = NULL;    /* Trees that correspond to each character, as a root. */
    NODE* huffman_binary_tree = NULL; /* The root node to return. */
    /* 
     * Indices to keep track of the lowest probability characters in character_trees array.
     * Character at lowestIndex1 will have smaller probability than character at lowestIndex2.
     */
    int lowestIndex1 = -1, lowestIndex2 = -1;
    int trees_remaining = MAX_ASCII;

    prob_table = get_prob_table(prob_file);    
    /*
     * Allocates memory to an array that holds 128 pointers of type NODE.
     * Before building the huffman tree, each character is a tree on its own.
     */
    character_trees = (NODE **)malloc(MAX_ASCII * sizeof(NODE *));
    if (character_trees == NULL)
    {
        printf("Error: Could not allocate memory using malloc\n");
        exit(EXIT_FAILURE);
    }    

    /* Initializes all the nodes accordingly. */
    for (i = 0; i < MAX_ASCII; i++)
    {
        character_trees[i] = (NODE*) malloc(sizeof(NODE));
        if (character_trees[i] == NULL)
        {
            printf("Error: Could not allocate memory using malloc\n");
            exit(EXIT_FAILURE);
        }
        character_trees[i]->character = (char)i;        
        character_trees[i]->probability = prob_table[i];
        character_trees[i]->left = NULL;
        character_trees[i]->right = NULL;       
    }  
    free(prob_table);
    
    /* The final tree is the Huffman binary tree. */
    while (trees_remaining > 1)
    {
        /* Iterate through the whole array of trees each time. */
        for (i = 0; i < MAX_ASCII; i++)
        {            
            /* Only check for a lower probabilty, if current index of the array has a tree. */
            if (character_trees[i] != NULL)
            {
                if (lowestIndex1 == -1)
                {                    
                    lowestIndex1 = i;
                    continue;
                }
                if (lowestIndex2 == -1)
                {                                      
                    /*
                     * To make sure that the character at the lowestIndex1 has a lower probability than
                     * the character at lowestIndex2.
                     */
                    if (character_trees[i]->probability < character_trees[lowestIndex1]->probability)
                    {
                        lowestIndex2 = lowestIndex1;
                        lowestIndex1 = i;
                    }
                    else
                    {                        
                        lowestIndex2 = i;
                    }                  
                    continue;
                }
                /* If the character at i has lower probability from both characters at the two indices. */
                if (character_trees[i]->probability < character_trees[lowestIndex1]->probability)
                {                    
                    lowestIndex2 = lowestIndex1;
                    lowestIndex1 = i;                    
                    continue;
                }
                /*
                 * If the probability of the character at i is inbetween the probabilities of the
                 * characters at the two indices.
                 */
                if (character_trees[i]->probability < character_trees[lowestIndex2]->probability &&
                    character_trees[i]->probability > character_trees[lowestIndex1]->probability)
                {                    
                    lowestIndex2 = i;                    
                }
            }
        }
        /* New node to hold the two nodes at the two lowest probability indices. */
        NODE *new_node = (NODE *)malloc(sizeof(NODE));
        if (new_node == NULL)
        {
            printf("Error: Could not allocate memory using malloc\n");
            exit(EXIT_FAILURE);
        }

        /* 
         * New node does not have character, has a probability of the sum of two lowest probability
         * characters, and its left node points to the lowest probability character and the right node
         * to the second lowest probability character.
         */
        new_node->character = '\0';
        new_node->probability = character_trees[lowestIndex1]->probability + 
                                character_trees[lowestIndex2]->probability;
        new_node->left = character_trees[lowestIndex1];
        new_node->right = character_trees[lowestIndex2];

        /* Tree at old lowest probability character becomes the new node (it's a tree for now). */
        character_trees[lowestIndex1] = new_node;
        /* The node at the second lowest probability is no longer a tree and is removed from the array. */
        character_trees[lowestIndex2] = NULL;
        /* 
         * At the last iteration lowestIndex1 will point at the last root node
         * remaining in characters_trees, which will be the Huffman binary tree.
         */
        huffman_binary_tree = character_trees[lowestIndex1];        
        
        lowestIndex1 = -1;
        lowestIndex2 = -1;
        trees_remaining--;
    } 
   
    free(character_trees);
    return huffman_binary_tree;
}

float *get_prob_table(char *prob_file)
{
    int i = 0;
    float *prob_table = NULL;
    FILE *fp = NULL;

    prob_table = (float *)malloc(MAX_ASCII * sizeof(float));
    if (prob_table == NULL)
    {
        printf("Error: Could not allocate memory using malloc\n");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(prob_file, "r")) == NULL)
    {
        printf("\"%s\" file cannot be opened\n", prob_file);
        exit(EXIT_FAILURE);
    }

    /* Reads the probabilities and saves them in prob_table. */
    while (fscanf(fp, "%f", &prob_table[i++]) == 1);
    fclose(fp);
    return (prob_table);
}

char **generate_huffman_table(NODE *root)
{
    /* Huffman table is an array of 128 pointers to strings. Each string represents a binary code. */
    char **huffman_table = NULL; 
    /* The string of 0s and 1s characters to build the huffman codes for each character. */   
    char *code = NULL;

    huffman_table = (char **) malloc(MAX_ASCII * sizeof(char *));
    if (huffman_table == NULL)
    {
        printf("Error: Could not allocate memory using malloc\n");
        exit(EXIT_FAILURE);
    }

    code = (char*) malloc(MAX_ASCII);
    if (code == NULL)
    {
        printf("Error: Could not allocate memory using malloc\n");
        exit(EXIT_FAILURE);
    }
    /* 
     * Traversing starts at the root of the binary tree, 
     * where the code binary should just be the null character. 
     */
    *code = '\0'; 

    build_codes(huffman_table, root, code);      

    free(code);
    return huffman_table;
}

void build_codes(char **huffman_table, NODE *current_node, char *code)
{     
    /* Base case if node is a leaf. */
    if (current_node->left == NULL && current_node->right == NULL)
    {          
        /* Character specifies the index of the Huffman table. */
        int index = (int) (current_node->character);                
        
	    huffman_table[index] = (char*) malloc(strlen(code) + 1);
        if (huffman_table[index] == NULL)
        {
            printf("Error: Could not allocate memory using malloc\n");
            exit(EXIT_FAILURE);
        }
        /* Copies the binary string in proper index in the Huffman table. */
        strcpy(huffman_table[index], code);
        
        /* 
         * Returning means going closer to the root by 1, 
         * therefore 1 bit needs to be removed from the binary code. 
         */
	    code[strlen(code) - 1] = '\0';             
	    return;
    }  
    
    /* First traverse towards the left subtree and add one 0 bit at the end of the binary. */
    if (current_node->left != NULL)
    {          
        int current_size = strlen(code);       
        
	    code[current_size] = '0';      /* Adds one 0 bit at the end of the binary. */    
        code[current_size + 1] = '\0'; /* Last character of string is the null character. */       
                
	    build_codes(huffman_table, current_node->left, code);
    }
    
    /* Same as going to the left, but the bit added is 1 instead of 0. */
    if (current_node->right != NULL)
    {
        int current_size = strlen(code);
               
	    code[current_size] = '1';      /* Adds one 1 bit at the end of the binary. */    
        code[current_size + 1] = '\0'; /* Last character of string is the null character. */  
              
	    build_codes(huffman_table, current_node->right, code);
    }    
    /* 
     * Returning means going closer to the root by 1, 
     * therefore 1 bit needs to be removed from the binary code.
     * On the first function frame though, the binary is just the null character,
     * therefore just for that occasion do not remove a bit. 
     */  
    if (strlen(code) != 0)
    {
	code[strlen(code) - 1] = '\0';
    }    
}

void export_huffman_codes(char **huffman_table)
{
    int i = 0;
    FILE *fp = NULL;

    /* Prints characters from 32 to 126 on screen. */
    for (i = 32; i <= 126; i++)
    {
        printf("  %c : %s\n", (char) i , huffman_table[i]);
    }

    if ((fp = fopen("codes.txt", "w")) == NULL)
    {
        printf("Error: Unable to create \"%s\" output file\n", "codes.txt");
        exit(EXIT_FAILURE);
    }

    /* Saves all the codes in "codes.txt. "*/
    for (i = 0; i < MAX_ASCII - 1; i++)
    {
        fprintf(fp, "%s\n", huffman_table[i]);
    }
    fprintf(fp, "%s", huffman_table[i]);
    printf("Huffman codes saved in \"%s\"\n", "codes.txt");

    fclose(fp);
}

void free_huffman_tree(NODE *current_node)
{
    /* Free current node if it is a leaf. */
    if (current_node->left == NULL && current_node->right == NULL)
    {
        free(current_node);
        return;
    }

    if (current_node->left != NULL)
    {
        free_huffman_tree(current_node->left);
    }

    if (current_node->right != NULL)
    {
        free_huffman_tree(current_node->right);
    }

    /* 
     * Returning here means leaves at bigger height have been freed, 
     * therefore this is a leaf as well now and needs to be freed.
     */
    free(current_node);
    return;
}

void free_huffman_table(char **huffman_table)
{
    int i = 0;
    /* Frees memory reserved for each code. */
    for (i = 0; i< MAX_ASCII; i++)
    {
        free(huffman_table[i]);
    }
    /* Frees memory reserved for array of pointers. */
    free(huffman_table);
}

#ifdef TEST_S
int const MAX_ASCII = 128;

int main(int argc, char **argv)
{
    char *prob_file = argv[1];

    NODE *huffman_tree_root = generate_huffman_tree(prob_file);
    char **huffman_table = generate_huffman_table(huffman_tree_root);
    export_huffman_codes(huffman_table);
    free_huffman_tree(huffman_tree_root);
    free_huffman_table(huffman_table);
    return 0;
}
#endif