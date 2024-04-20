#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int isWord; //0/1
    struct trie* next[26];
};

// Initializes a trie structure
struct Trie* createTrie()
{
    
    struct Trie* newNode = malloc(sizeof(struct Trie));
    newNode->isWord = 0;

    
    for (int i = 0; i < 26; i++) {
        newNode->next[i] = NULL;
    }

    //returns the new node
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
    int length = strlen(word);
    
    for (int i = 0; i < length; i++) {
        int wordIn = word[i] - 'a';

        if (i == length) {
            pTrie->isWord++;
            return;
        }
        if (!pTrie->next[wordIn]) {
            pTrie->next[wordIn] = createTrie();
        }
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
    int length = strlen(word);

    for (int i = 0; i < length; i++) {

        int nextWord = word[i] - 'a';
        if (i == length) {
            i = i - 1;
            return pTrie->next[i];
        }
    }
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
    if (!pTrie) {
        return NULL;
    }

    for (int i = 0; i < 26; i++) {
        if (pTrie->next[i])
        {
            //recursively delete
            deallocateTrie(pTrie->next[i]);
        }
    }
    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
    FILE* inputFile = fopen("dictionary-1.txt", "r");
    int words;
    fscanf(inputFile, "%d", &words);
    char word[21];

    for (int i; i < words; i++) {
        fscanf(inputFile, "%s", word);
        pInWords[i] = (char*)malloc(sizeof(char*));
        strcpy(pInWords[i], word);
    }
    return words;
}

int main(void)
{
    char* inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary-1.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie* pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}