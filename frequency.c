#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0,TRUE=1} boolean;

//node in a trie 
typedef struct node {
char letter;
long unsigned int count;
boolean wordIsDone;
boolean isLeaf;
struct node* children[NUM_LETTERS];
} node;

// trie structure 

typedef struct trie {
node* children[NUM_LETTERS];
node* curr;
boolean treeIsEmpty;
int len;
char* word;
} trie;

//init node
node* init(node* new_node,char c) {
new_node->letter = c;
new_node->count = 0;
new_node->wordIsDone =FALSE;
new_node->isLeaf = TRUE;
for(int i=0; i<NUM_LETTERS;i++) {
(new_node->children)[i] = NULL;
}
return new_node;
}

// generate memory for the node 
node* generate_memory_node() {
node* new_node=(node*)malloc(sizeof(node));

if (new_node==NULL){
printf("memory error");
}
return new_node;
}

// create node and init 
node* new_node(char c) {
node* new=generate_memory_node();
return init(new,c);
}

//free node memory
void free_node_memory(node* f_node) {
if (f_node==NULL) {
return;//dont do anything
}
if(f_node->isLeaf==TRUE){// can free the node 
free(f_node);
} else {// free the childs first
for (int i=0;i<NUM_LETTERS;i++) {
free_node_memory((f_node->children)[i]);
}
}
return;
}

// init trie 
trie* init_trie(trie* new) {
new->curr=NULL;
new->treeIsEmpty=TRUE;
new->len=0;
for(int i=0;i<NUM_LETTERS;i++) {
new->children[i]=NULL;
}
return new;
}
//same procces for trie 
trie* generate_memory_trie() {
trie* new_trie=(trie*)malloc(sizeof(trie));
if (new_trie==NULL){// memory has not found 
printf("memory error");
}
return new_trie;
}


//create and init new trie 
trie* new_trie() {
trie* new=generate_memory_trie();
return init_trie(new);
}

//the word is done 
void the_word_is_done(trie* root) {
if(root->curr == NULL){
return;}//dont do anything
else{
root->curr->count++;
root->curr->wordIsDone = TRUE;
root->curr=NULL;
}
}

//----------------------------//
int get_word(trie* root,char c) {
int i=0;
int length=0;
if(isalpha(c)==0) {
the_word_is_done(root);
return length;
}
length++;
c=tolower(c);
i= c- 'a';
if (root->curr==NULL) { 

if (root->children[i] == NULL)
root->children[i] = new_node(c);
root->curr = root->children[i];
root->treeIsEmpty=FALSE;
} 
else{  
root->curr->isLeaf = TRUE;
if (root->curr->children[i] == NULL)
root->curr->children[i] = new_node(c);
root->curr=root->curr->children[i];
}
return length;
}

void generate_memory_word(trie* root) {
root->word=(char*)malloc(1+sizeof(char)*(root->len));
if(root->word==NULL){
printf("memory error");
}
}

//

trie* text() {
char input;
int len=0;
trie* root;
root = new_trie();
while( scanf("%c", &input)==1 &&input!=EOF){
len=get_word(root,input);
if (len>root->len)
root->len=len;
}
generate_memory_word(root);
return root;
}
void print_r(trie* root) {
static int tr=0;
char space=' ';
node* current;
root->word[tr]=root->curr->letter;
tr++;
if (root->curr->isLeaf) {
for(int i=NUM_LETTERS-1; i>=0; i--) {
if (root->curr->children[i] == NULL)
continue;
current = root->curr; 
root->curr = root->curr->children[i];
print_r(root);
root->curr = current; 
}
} else {
if (root->curr->wordIsDone) {
root->word[tr]='\0';
printf("%s %c %ld \n",root->word,space,root->curr->count);
}
tr--;
return;
}
if (root->curr->wordIsDone) {
root->word[tr]='\0';
printf("%s %c %ld \n",root->word,space,root->curr->count);
}
tr--;
}

//
void print_tree_r(trie* root) {
if (root == NULL)
return;
if (root->treeIsEmpty==TRUE){
return;}
for (int i=NUM_LETTERS-1; i>=0; i--) {
if (root->children[i] == NULL)
continue;
root->curr = root->children[i];
print_r(root);
}
}

///


void print(trie* root) {
static int tr=0;
char space= ' ';
node* current;
root->word[tr]=root->curr->letter;
tr++;
if (root->curr->wordIsDone) {
root->word[tr]='\0';
printf("%s %c %ld \n",root->word,space,root->curr->count);
}
if (root->curr->isLeaf) {
for(int i=0; i<NUM_LETTERS;i++) {
if (root->curr->children[i] == NULL)
continue;
current = root->curr; 
root->curr = root->curr->children[i];
print(root);
root->curr = current; 
}
} else {
tr--;
return;
}
tr--;
}

void print_tree(trie* root) {
if (root == NULL)
return;
if(root->treeIsEmpty==TRUE){
return;}
for(int i=0; i<NUM_LETTERS; i++) {
if (root->children[i] == NULL)
continue;
root->curr = root->children[i];
print(root);
}
}
void free_tree(trie* t) {
int i;
if (t == NULL)
return;
for(i=0;i<NUM_LETTERS; ++i) {
free_node_memory(t->children[i]);
}
free(t);
}

int main(int argc, char* argv[]) {
trie* root=text();
if(argc>1){
if(*argv[1]=='r'){
print_tree_r(root);
free_tree(root);
}
}
else{
print_tree(root);
free_tree(root);
}
return 0;
}