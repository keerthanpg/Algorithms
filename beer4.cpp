#include<iostream>
#include<vector>
#include<stack>
#include <unordered_map>
using namespace std;

vector< vector< pair<int, int> > > adj; //next node, edge num
vector<int> cap;
int r,c, num_vertices = 0;
char** board;
int **nodeid;
unordered_map< int, pair<int, int> > parent;


void printnodeids(){
	cout << "\nPrinting nodeids\n";
	for( int i =0; i < r ; i++){
		for(int j = 0; j < c; j++){
			cout << nodeid[i][j] << " ";
		}
		cout << "\n";
	}
}

void printcapacities(){
	cout << "\nPrinting capacities\n";
	int N = cap.size();
	for( int i =0; i < N ; i++){
			cout << cap[i] << " ";
	}
}


void printedges(){
	cout << "\nPrinting edges\n";
	int N = adj.size();
	for( int i =0; i < N ; i++){
		int M = adj[i].size();
		cout << i << " ";
		for(int j = 0; j < M; j++){
			cout << "(" << adj[i][j].first << "," << adj[i][j].second <<")" << " ";
		}
		cout << "\n";
	}
}


int addedge(int v1, int v2, int k){
	/* add edge between v1 and v2 with ID k*/
	adj[v1].push_back(make_pair(v2, k));		
	adj[v2].push_back(make_pair(v1, k+1));
	cap.push_back(1);
	cap.push_back(0);
	
	return k + 2;
}


void constructgraph(){	
	int k = 0;	
	for( int i = 0; i < r; i++){
		for( int j = 0; j < c ; j++){
			if(board[i][j] == '.') continue;
			else if (board[i][j] == 'b'){
				k = addedge(0, nodeid[i][j], k);
				if(j + 1 < c){
					if(board[i][j + 1] == 'e')
						k = addedge(nodeid[i][j], nodeid[i][j + 1], k);
				}
				if(i + 1 < r){
					if(board[i + 1][j] == 'e')
						k = addedge(nodeid[i][j], nodeid[i + 1][j], k);
				}				
			}
			else if (board[i][j] == 'r'){
				k = addedge(nodeid[i][j], 1, k);				
				if(j + 1 < c){
					if(board[i][j + 1] == 'e')
						k = addedge(nodeid[i][j + 1] + 1, nodeid[i][j], k);
				}
				if(i + 1 < r){
					if(board[i + 1][j] == 'e')
						k = addedge(nodeid[i + 1][j] + 1, nodeid[i][j], k);
				}
			}
			else{
				k = addedge(nodeid[i][j], nodeid[i][j] + 1, k);
				if(j + 1 < c){
					if(board[i][j + 1] == 'b')
						k = addedge(nodeid[i][j + 1], nodeid[i][j], k);
					else if(board[i][j + 1] == 'r')
						k = addedge(nodeid[i][j] + 1, nodeid[i][j + 1], k);
					else if(board[i][j + 1] == 'e'){
						k = addedge(nodeid[i][j] + 1, nodeid[i][j + 1], k);
						k = addedge(nodeid[i][j + 1] + 1, nodeid[i][j], k);
					}
				}
				if(i + 1 < r){
					if(board[i + 1][j] == 'b')
						k = addedge(nodeid[i + 1][j], nodeid[i][j], k);
					else if(board[i + 1][j] == 'r')
						k = addedge(nodeid[i][j] + 1, nodeid[i + 1][j], k);
					else if(board[i + 1][j] == 'e'){
						k = addedge(nodeid[i][j] + 1, nodeid[i + 1][j], k);
						k = addedge(nodeid[i + 1][j] + 1, nodeid[i][j], k);
					}
				}
			}
		}
	}
}

bool DFS(){
    vector<bool> visited(num_vertices, false);
    stack< pair<int,int> > stack; 
    stack.push(make_pair(0,-1)); 
    pair<int,int> s; 
    parent.clear();   
  
    while (!stack.empty()) 
    {         
        s = stack.top(); 
        stack.pop(); 
        if (!visited[s.first]) 
            visited[s.first] = true;

        for (auto i = adj[s.first].begin(); i != adj[s.first].end(); ++i){
        	if (i->first == 1 && cap[i->second] > 0){
        		parent.insert(make_pair(i->first, make_pair(i->second, s.first)));         		
        		return true;
        	}                 
  
            if (!visited[i->first] && cap[i->second] > 0){
                stack.push(*i);
                //store the destination mapped to the pair of edge that led to it and parent node 
                parent.insert(make_pair(i->first, make_pair(i->second, s.first)));                
            }
        }
    } 
    return false;
} 

int fordfulkerson(){
	int edge, node, f = 0;
	pair<int,int> caset;
	unordered_map< int, pair<int, int> >::const_iterator value;	
	while(1){
		bool dfs = DFS();
		//cout<<"\nDFS:" << dfs;
		//cout << "\n Edges: ";
		if(!dfs)
			break;
		else{	
			node = 1;		
			while(1){
				value = parent.find(node);
				edge = value->second.first;
				node = value->second.second;
				//cout << edge << " ";				
				cap[edge] -= 1;
				cap[edge ^ 1] += 1;
				if(node == 0)
					break;
			}
			//cout << endl;
			f += 1;
		}		
	}
	return f;
}

int main(){
	int k = 2;
	char character;
	cin >> r >> c;
	board = new char*[r];
	nodeid = new int*[r];  

	adj.push_back(vector<pair<int, int> >()); //for start and end nodes
	adj.push_back(vector<pair<int, int> >());  

	for( int i = 0; i < r; i++){
		board[i] = new char[c];
		nodeid[i] = new int[c];
		for( int j = 0; j < c ; j++){
			cin>>character;
			if(character!= '\n' && character!= '\0'){
				board[i][j] = character;
				if(character != '.'){
					if(character != 'e'){
						nodeid[i][j] = k++;
						adj.push_back(vector<pair<int, int> >());
					}
					else{						
						nodeid[i][j] = k;
						k += 2;
						adj.push_back(vector<pair<int, int> >());
						adj.push_back(vector<pair<int, int> >());
					}
				}
				else{
					nodeid[i][j] = -1;

				}
			}
			else break;
		}
	}
	/*
	for( int i = 0; i < r; i++){
		for( int j = 0; j < c ; j++){
			cout << board[i][j];
		}
		cout <<"\n";		
	}*/
	num_vertices = k;
	//cout <<"\nNum vertices =" << k;

	constructgraph();
	//printnodeids();
	//printedges();
	//printcapacities();
	int num = fordfulkerson();
	if(num == 1)
		cout << num << " beer\n";
	else
		cout << num << " beers\n";
	

}