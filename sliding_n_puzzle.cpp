#include <iostream>
#include <queue>
#include <list>
using namespace std;

#define N 3

class node{

	public :

	int a[N][N];
	node *parent;
	int level;
	int zx,zy;
	node(int x[N][N], node *p, int l){

		for(int i=0;i<N;i++){

			for(int j=0;j<N;j++){

				this->a[i][j] = x[i][j];
				if(x[i][j]==0){

					zx=i;
					zy=j;
				}
				
			}
		}

			this->parent = p;
			this->level = l;

	}

	void printnode();
	bool match(int b[][N]);
	void swapzero(int m,int n);
	

};

void node::printnode(){

	cout<<endl;
	cout<<"level: "<<level<<endl;
	for(int i=0;i<N;i++){

		for(int j=0;j<N;j++){

			cout<<this->a[i][j];
			cout<<' ';
		}
		cout<<'\n';
	}
	cout<<endl;
}


bool node::match(int b[][N]){
	int c;
	for(int i=0;i<N;i++){

		for(int j=0;j<N;j++){

			c=this->a[i][j];
			if(c!=b[i][j]) 
				return false;
		}
	}
	return true;
}


void node::swapzero(int m,int n){

	int temp = a[m][n];
	a[zx][zy] = temp;
	a[m][n] = 0;

	//updating the new zero coordinates
	zx=m;
	zy=n;
}


bool seenbefore(list<node> slist,node x){

	for(list<node>::iterator list_iter = slist.begin();list_iter!=slist.end();
		list_iter++){

		if((*list_iter).match(x.a))
			return true;

	}

	return false;

}



int main(){


	int goal[N][N]={{2,4,0},{7,5,6},{8,3,1}};
	int start[N][N] = {{7,2,4},{5,0,6},{8,3,1}};
	list<node> seenlist;
	queue<node> actions;

	node source(start,NULL,0);

	//pushing source onto queue
	actions.push(source);
	

	while(!actions.empty()){

		node temp = actions.front();
		cout<<"currtent/parent node : ";
		cout<<" zero coordinates : ("<<temp.zx<<","<<temp.zy<<")";		
		temp.printnode();
		
		if(!temp.match(goal)){

			int x = temp.zx;
			int y = temp.zy;
			
			int level = temp.level;

			if(!seenbefore(seenlist,temp)){

				//adding the current node to seen list
				seenlist.push_back(temp); 

				if(x-1>=0){
					//while assigning the parent to the child,i'm referencing the last
					//element in the list that we just added
					//becuse in the next iteration of the loop, the list memory will
					//still persist, whereas temp will be popped off the queue
					node way1(temp.a,&seenlist.back(),level+1);
					way1.swapzero(x-1,y);
					actions.push(way1);
					cout<<"possible child :";
					way1.printnode();
					
				}
				if(x+1<=2){
				
					node way2(temp.a,&seenlist.back(),level+1);
					way2.swapzero(x+1,y);
					actions.push(way2);
					cout<<"possible child :";
					way2.printnode();
					
				}
				if(y-1>=0){
					node way3(temp.a,&seenlist.back(),level+1);
					way3.swapzero(x,y-1);
					actions.push(way3);
					cout<<"possible child :";
					way3.printnode();
					
				}
				if(y+1<=2){
					node way4(temp.a,&seenlist.back(),level+1);
					way4.swapzero(x,y+1);
					actions.push(way4);
					cout<<"possible child :";
					way4.printnode();
					
				}


			}
			cout<<"---------------------------------"<<endl;			
			actions.pop();
			
		}
		else{
			cout<<endl<<endl<<"/********************************/"<<endl;
			cout<<"PRINTING REVERSE PATH (goal -> source) : "<<endl;
			cout<<"/********************************/"<<endl;
			temp.printnode();
			node* p=temp.parent;

			while(p!=NULL){

				p->printnode();
				p=p->parent;

			} 

			break;
		}

	}
	return 0;
}
