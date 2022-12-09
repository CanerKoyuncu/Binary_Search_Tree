/* Name: Caner Koyuncu Number: 200254029 COM_201_HW_2 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <minmax.h>
#include <ctype.h>

typedef struct {
    char word[10];
    int usedTimes;
    struct TreeNode *leftSubTree;
    struct TreeNode *rightSubTree;
} TreeNode;

TreeNode *PrintAlphabeticOrder(TreeNode *rooAt);

TreeNode *CreateTree(char *);

TreeNode *TreeBalancer(TreeNode *);

char *toLower(char *);

int isUpperCase(char);

int TreeHeight(TreeNode *);

int BalanceValue(TreeNode *);

void SearchWordInTree(TreeNode *);

TreeNode *PrintDifferentWords(TreeNode *);

void Menu(TreeNode *);

int main() {
    TreeNode *rootNode;
    rootNode = CreateTree("Words.txt");
    // printf("Max = %d", TreeHeight(rootNode));
    Menu(rootNode);
    free(rootNode);
    return 0;
}

void Menu(TreeNode *treeRoot) {
    bool flag = true;
    int selected = 0;
    do {
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
            default:
                selected = 0;
                break;
        }
    } while (flag);
}

TreeNode *PrintDifferentWords(TreeNode *treeRoot) {
    if (treeRoot == NULL) {
        return NULL;
    }

    PrintDifferentWords((TreeNode *) treeRoot->rightSubTree);
    printf("%s, %d times\n", treeRoot->word, treeRoot->usedTimes);
    PrintDifferentWords((TreeNode *) treeRoot->leftSubTree);

}

TreeNode *PrintAlphabeticOrder(TreeNode *treeRoot) {
    if (treeRoot == NULL) {
        return NULL;
    }
    PrintAlphabeticOrder((TreeNode *) (TreeNode *) treeRoot->leftSubTree);
    printf("%s        ", treeRoot->word);
    printf("times %d\n", treeRoot->usedTimes);
    PrintAlphabeticOrder((TreeNode *) treeRoot->rightSubTree);

}

void SearchWordInTree(TreeNode *treeRoot) {
    char word[10];
    char *word1[10];
    char *word2[10];
    bool flag = true;
    int depth = 0;
    printf("Please enter a word for search: ");
    scanf(" %s", word);
    printf("\n");
    while (flag) {
        strcpy((char *) word1, toLower(treeRoot->word));
        strcpy((char *) word2, toLower(word));
        if (strcmp((const char *) word1, (const char *) word2) == 0) {
            printf("%s        Depth:%d     %d Time", treeRoot->word, depth, treeRoot->usedTimes);
            flag = false;
            break;
        } else if (strcmp(treeRoot->word, word) < 0) {
            if (treeRoot->rightSubTree != NULL) {
                treeRoot = (TreeNode *) treeRoot->rightSubTree;
                depth++;
            } else {
                flag = false;
                printf("Cannot found this word.\n");
                break;
            }
        } else if (strcmp(treeRoot->word, word) > 0) {
            if (treeRoot->leftSubTree != NULL) {
                treeRoot = (TreeNode *) treeRoot->leftSubTree;
                depth++;
            } else {
                flag = false;
                printf("Cannot found this word.\n");
                break;
            }
        }

    }
    strcpy(word, "");
    printf("\n");
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

TreeNode *CreateTree(char *fileName) {
    TreeNode *rootTemp = NULL;
    TreeNode *temp = NULL;
    TreeNode *onThisNode = NULL;
    char tempString[10];
    int i;
    bool flag;
    char word1[10];
    char word2[10];

    FILE *file = fopen(fileName, "r");
    while (fscanf(file, "%s", tempString) != EOF) {
        temp = CreateNode(tempString);
        onThisNode = rootTemp;
        if (rootTemp == NULL) {
            rootTemp = temp;
            onThisNode = rootTemp;
            continue;
        } else {
            flag = true;
            while (flag) {
                // printf("%s, ", onThisNode->word);
                strcpy(word1, toLower(onThisNode->word));
                strcpy(word2, toLower(tempString));
                i = strcmp(word1, word2);
                if (i == 0) {
                    onThisNode->usedTimes += 1;
                    flag = false;
                    break;
                } else if (i > 0) {
                    if (onThisNode->leftSubTree != NULL) {
                        onThisNode = (TreeNode *) onThisNode->leftSubTree;
                        continue;
                    } else {
                        onThisNode->leftSubTree = (struct TreeNode *) temp;
//                        printf("___LEFT___");
//                         printf(" %s", temp->word);
                        flag = false;
                        break;
                    }
                } else if (i < 0) {
                    if (onThisNode->rightSubTree != NULL) {
                        onThisNode = (TreeNode *) onThisNode->rightSubTree;
                        continue;
                    } else {
                        onThisNode->rightSubTree = (struct TreeNode *) temp;
//                        printf("___RIGHT___");
//                         printf(" %s", temp->word);
                        flag = false;
                        break;
                    }
                }
            }
            // printf("\n");
            rootTemp = TreeBalancer(rootTemp);
        }
    }
    return rootTemp;
}

TreeNode *TreeBalancer(TreeNode *tree) {
    int value;
    value = BalanceValue(tree);
    // printf("Value: %d", value);
    TreeNode *temp1;
    TreeNode *temp2;
    int lastValue = value;
    bool flag = true;
    //TODO: Infinity loop control and fix
    while (abs(value) < abs(lastValue) || flag) {
        flag = false;
        if (value < 0) {
            //if the right tree is 3 nodes deeper than the left tree
            temp1 = (TreeNode *) tree->rightSubTree;
            temp2 = (TreeNode *) temp1->leftSubTree;
            tree->rightSubTree = (struct TreeNode *) temp2;
            temp1->leftSubTree = (struct TreeNode *) tree;
            tree = temp1;

        } else {
            //if the left tree is 3 nodes deeper than the right tree
            temp1 = (TreeNode *) tree->leftSubTree;
            temp2 = (TreeNode *) temp1->rightSubTree;
            tree->leftSubTree = (struct TreeNode *) temp2;
            temp1->rightSubTree = (struct TreeNode *) tree;
            tree = temp1;
        }
        lastValue = value;
        value = BalanceValue(tree);

    }
    // printf("Root: %s", tree->word);
    // printf(", Height: %d\n", TreeHeight(tree));
    return tree;
}

int BalanceValue(TreeNode *treeRoot) {
    int left = TreeHeight((TreeNode *) treeRoot->leftSubTree);
    int right = TreeHeight((TreeNode *) treeRoot->rightSubTree);
    return left - right;
}

int TreeHeight(TreeNode *treeNode) {
    int height = 0;
    if (treeNode == NULL) {
        return 0;
    }
    height = height + max(TreeHeight((TreeNode *) treeNode->leftSubTree) + 1, 1 + TreeHeight((TreeNode *) treeNode->rightSubTree));
    return height;
}

int isUpperCase(char letter) {
    if (letter >= 65 && letter <= 90) {
        return 1;
    } else {
        return 0;
    }
}

char *toLower(char string[10]) {
    int cursor = 0;
    int value;
    static char text[10] = "";
    char letter;
    while (string[cursor] != '\0') {
        value = isUpperCase(string[cursor]);
        letter = string[cursor];
        if (value == 1) {
            letter = tolower(letter);
        }
        text[cursor] = letter;
        cursor += 1;
    }
    text[cursor] = '\0';
    return text;
}
