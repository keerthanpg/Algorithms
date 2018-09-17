#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node Tree;
struct tree_node{
	Tree * left, * right, * parent;
	int item;
};

Tree * createSplayTree(int n){
	int i;
	Tree * splayTree = malloc(sizeof(Tree));
	Tree * root = splayTree;
	splayTree->parent = NULL;
	for( i = n - 1; i > 0; i--){
		//cout << i;
		splayTree->item = i;
		splayTree->right = NULL;
		splayTree->left = malloc(sizeof(Tree));
		splayTree->left->parent = splayTree;		
		splayTree = splayTree->left;
	}
	splayTree->item = 0;
	splayTree->right = NULL;
	splayTree->left = NULL;

	return root;
}

Tree * splayTestMyTree(Tree* splayTree, int key){	
	int depth = 0;
	Tree * root = splayTree;
	while(1){		
		if (splayTree != NULL){
			if (splayTree->item == key){
				printf("depth = %d \n", depth);
				break;			
			}
			else if(splayTree->item < key){
				splayTree = splayTree->right;
				depth ++;
			}
			else{
				splayTree = splayTree->left;
				depth ++;
			}
		}	
		else{
			printf("splaytree is null\n");
			return splayTree;
		}	
	}
	

	while(depth){		
		Tree * parent = splayTree->parent;		

		if(parent == NULL){
			printf("Parent is null\n");
			break;
		}
		// zig case
		if(splayTree->item > parent->item){
			// so the splay element is the right child of parent									
			parent->right = splayTree->left;
			splayTree->left = parent;				
		}
		else{
			// here the splay element is the left child of parent
			parent->left = splayTree->right;
			splayTree->right = parent;	
		}
		splayTree->parent = parent->parent;
		if(parent->parent != NULL){
			if(parent->parent->left == parent){
				parent->parent->left = splayTree;
			}
			else{
				parent->parent->right = splayTree;
			}
		}
		parent->parent = splayTree;	
		depth --;		
	}

	return splayTree;

}
/*
void printSplayTree(Tree * splayTree){	
	queue<Tree*> levelQ;
	levelQ.push(splayTree);
	Tree * node;
	while(!levelQ.empty()){		
		node = levelQ.front();
		if (node != NULL){
			cout << node->item << " ";
			levelQ.push(node->left);
			levelQ.push(node->right);
		}
		levelQ.pop();
	}	
}*/




int main(){
int n, m, i;
scanf("%d %d\n", &n, &m);

printf("first:line %d, %d\n", n, m);

Tree * splayTree = createSplayTree(n);
printf("created splay tree\n");

int key;


for( i = 0; i < m; i = i + 1 ){
   	scanf("%d", &key);
   	splayTree = splayTestMyTree(splayTree, key);
  }


return 0;
}

/*

int main(){
	int n, m;
	scanf("%d, %d\n", &n, &m);		
	
	Tree * splayTree = createSplayTree(n);
	printf("created splay tree\n");

	char buffer[32];
    char *b = buffer;
    size_t bufsize = 32;
    size_t characters;
    int num, k;
    char key[100];
    
    characters = getline(&b,&bufsize,stdin);
    printf("%zu characters were read.\n",characters);
    printf("You typed: '%s'\n",buffer);


    k = 0;
	for (int i=0; i < characters; i++){
        if (isdigit(buffer[i])){       
            key[k++] = buffer[i];
        }
        else{
        	key[k] = '\0';
        	num = atoi (key);
        	printf("%d ", num);
        	k = 0;
        	splayTestMyTree(splayTree, num);
        	key[0] = "\0";

        }
    }
    

	return 0;
}*/



