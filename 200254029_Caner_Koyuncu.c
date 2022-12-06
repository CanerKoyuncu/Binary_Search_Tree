/* Name: Caner Koyuncu Number: 200254029 COM_201_HW_2 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char word[10];
    int usedTimes;
    struct TreeNode *leftSubTree;
    struct TreeNode *rightSubTree;
} TreeNode;

typedef struct {
    struct TreeNode *TreeNode;
    struct StackTreeNode *nextStack;
} StackTreeNode;

TreeNode *CreateTree(char *);

TreeNode *SearchNode();

void PrintDifferentWords(TreeNode *);

TreeNode *CreateNode(char *);

void PrintTree(TreeNode *);

char *toLower(char *);

void Menu(TreeNode *);

int isUpperCase(char);

TreeNode *PrintAlphabeticOrder(TreeNode *root);

void SearchWordInTree(TreeNode *);

int main(int argc, char **argv) {
    TreeNode *rootNode = CreateTree("Words.txt");
    Menu(rootNode);
    return 0;
}

void Menu(TreeNode *treeRoot) {
    bool flag = true;
    int selected;
    while (flag) {
        selected = 0;
        printf("##################-Binary-Search-Tree-##################\n");
        printf("##  1-) Print different                               ##\n");
        printf("##  2-) Print different words in alphabetical order   ##\n");
        printf("##  3-) Search word                                   ##\n");
        printf("##  4-) Exit                                          ##\n");
        printf("########################################################\n");
        printf("Please select:");
        scanf(" %d", &selected);
        printf("\n");
        switch (selected) {
            case 1:
                PrintDifferentWords(treeRoot);
                break;
            case 2:
                PrintAlphabeticOrder(treeRoot);
                break;
            case 3:
                SearchWordInTree(treeRoot);
                break;
            case 4:
                flag = false;
                break;
        }
    }
}

void SearchWordInTree(TreeNode *treeRoot) {
    char word[10];
    bool flag = true;
    int depth = 0;
    printf("Please enter a word for search: ");
    scanf("%s", word);
    while (flag) {
        if (strcmp(treeRoot->word, word) == 0) {
            printf("%s        Depth %d     %d Time", treeRoot->word, depth, treeRoot->usedTimes);
            flag = false;
            break;
        } else if (strcmp(treeRoot->word, word) > 0) {
            treeRoot = treeRoot->rightSubTree;
            depth++;
        } else if (strcmp(treeRoot->word, word) < 0) {
            treeRoot = treeRoot->leftSubTree;
            depth++;
        }
    }
    printf("\n");
}

TreeNode *PrintAlphabeticOrder(TreeNode *treeRoot) {
    if (treeRoot == NULL) {
        return NULL;
    }
    PrintAlphabeticOrder(treeRoot->rightSubTree);
    printf("%s        ", treeRoot->word);
    printf("times %d\n", treeRoot->usedTimes);
    PrintAlphabeticOrder(treeRoot->leftSubTree);
}

void PrintDifferentWords(TreeNode *treeRoot) {

}

TreeNode *CreateTree(char *fileName) {
    TreeNode *rootTemp = NULL;
    TreeNode *temp = NULL;
    TreeNode *onThisNode = NULL;
    char *tempString;
    int i = 0;
    bool flag;
    char toLowed[10];
    FILE *file = fopen(fileName, "r");
    while (fscanf(file, "%s", tempString) != EOF) {
        temp = CreateNode(tempString);
//        printf("%s\n", tempString);
        onThisNode = rootTemp;
        if (rootTemp == NULL) {
            rootTemp = temp;
            onThisNode = rootTemp;
            continue;
        } else {
            flag = true;
            while (flag) {
//                printf("%s,%d--", onThisNode->word, onThisNode->usedTimes);
                i = strcmp(onThisNode->word, tempString);
//                printf("%d", i);
                if (i == 0) {
                    onThisNode->usedTimes += 1;
                    flag = false;
                    break;
                } else if (i < 0) {
                    if (onThisNode->leftSubTree != NULL) {
                        onThisNode = onThisNode->leftSubTree;
                        continue;
                    } else {
                        onThisNode->leftSubTree = temp;
                        flag = false;
                        break;
                    }
                } else if (i > 0) {
                    if (onThisNode->rightSubTree != NULL) {
                        onThisNode = onThisNode->rightSubTree;
                        continue;
                    } else {
                        onThisNode->rightSubTree = temp;
                        flag = false;
                        break;
                    }
                }

            }
//            printf("\n");

        }
    }
    return rootTemp;
}

//TODO: Not working, need fix
char *toLower(char string[10]) {
    int cursor = 0;
    int value;
    char text[10];
    strcpy(text, string);
    while (string[cursor] != '\0') {
        value = isUpperCase(string[cursor]);
        if (value == 1) {
            text[cursor] += 32;
        }
        cursor += 1;
    }
    text[cursor] = '\0';
    return text;
}

int isUpperCase(char letter) {
    if (letter >= 65 && letter <= 90) {
        return 1;
    } else {
        return 0;
    }
}

TreeNode *CreateNode(char word[10]) {
    TreeNode *treeNode;
    treeNode = malloc(sizeof(TreeNode));
    strcpy(treeNode->word, word);
    treeNode->usedTimes = 1;
    treeNode->leftSubTree = NULL;
    treeNode->rightSubTree = NULL;
    return treeNode;
}
