/* 	Date: 15.10.2019 */ 

#include <iostream>
#include <fstream>										//file operations
#include <cmath>										//abs function

using namespace std;

struct node{     
	int size;     
	int quant;     
	node* next; 
};

struct stock{    
	node* headptr;     									//head pointer of the linked list
	int node_count;										//keeps the number of nodes
	void create();										//creates the linked list
	node* create_node(int shoe_size);					//creates a node if it is necessary   
	void add_stock(int shoe_size);     					//adds the shoe to the linked list
	void sell(int shoe_size);     						//sells the shoe
	void current_stock();     							//prints the whole linked list	
	void clear(); 										//deletes all nodes from the linked list
}; 

node* stock::create_node(int shoe_size){				//creates a new node then initializes its size with shoe_size paramaeter	
	
	node* new_node = new node;						
	new_node->size = shoe_size;
	new_node->quant = 1;								//initializes the quantity of the new node with 1
	new_node->next = NULL;	
	
	return new_node;
}

void stock::create(){									//creates the linked list
	headptr = NULL;
	this->node_count = 0;								//Initially there is no node in the linked list
}

void stock::add_stock(int shoe_size){
	node* temp = headptr;
	bool found = false;									//I've created a boolean variable to check whether the shoe I want to add is in the list or not.
	while(temp){										//I am visiting all nodes until temp becomes NULL.
		if(temp->size == shoe_size){					//If the size of the node is equal to size of shoe I want to add I incremented quant of this node then return 
			found = true;								//I've founded the node I am looking for.
			temp->quant += 1;
			return;
		}else{
			temp = temp->next;							//If the size of the node is not equal to shoe size I want to add then I moved to the next node.
		}
	}
	if(!found){											//If I don't find the node that is corresponding to parameter value to the function, I will create a new node and place it with suitable order in the list
		if(this->node_count == 0){						//And the linked list is empty that means I create a new node as the first node in the linked list 
			node* nn = create_node(shoe_size);		
			headptr = nn;								//I assign nn to headptr because it is the first node in the list
			this->node_count++;							//I incremented node counted because I've created a new node
			return;
		}else{											//If the linked list is not empty I will search suitable location for the node I want to add
			node* temp = headptr;						//Temp pointer simply starts from headptr and goes until the end of the linked list if it does'nt find the suitable order
			node* tail = NULL;							//Tail pointer points the node that is previous node temp points
			int position = 1;							//keeps the suitable order for the node.
			while(temp && shoe_size > temp->size){		//this while loop finds correct place for the newcoming node and it increases current position by 1 as long as shoe_size > temp->size
				tail = temp;						
				temp = temp->next;
				position++;
			}
			if(position == 1){							//If correct position for the newcoming node is 0, it means I will add new node as the first node
				node* nn = create_node(shoe_size);
				nn->next = headptr;						//First node in the list is the second node after we add the new node
				headptr = nn;							//Now headptr points the new node because first node is the new node
				this->node_count++;
				return;
			}
			else if(position == this->node_count+1){	//If correct position for the newcoming node is equal to the number of nodes in the list, it means I will add new node as the last node
				node* nn = create_node(shoe_size);	
				tail->next = nn;						//Tail->next should be nn because the tail points the last node before the addition operation
				nn->next = NULL;
				this->node_count++;
				return;
			}else{										//If none of the above if statements executes, it means that new coming node shoul de be placed anywhere between the first and the last node
				node* nn = create_node(shoe_size);	
				tail->next = nn;						//tail->next should be nn because tail points previous node from the correct place
				nn->next = temp;						//nn->next should points the temp, because new coming node is placed between tail and temp
				this->node_count++;
				return;
			}
		}
	}
}
void stock::sell(int shoe_size){					
	node* temp = headptr;
	node* deletingnode = NULL;							//It points the node that will be deleted
	bool found = false;
	int position = 1;

	while(temp){										//I am going to search for the shoe size I will sell with this while loop
		if(temp->size == shoe_size){					//If I've found
			found = true;
			temp->quant--;								//I've decreased the quantity of this shoe
			if(temp->quant != 0){						//If current quantity is not 0, I can finish this loop
				break;
			}
			if(position == 1){							//But if the current quantity is 0, that means I have to delete this node from the list
				deletingnode = temp;					//If the node I will delete is the first node I should change headptr with headptr->next
				headptr = headptr->next;
				this->node_count--;
				delete deletingnode;
				return;
			}else if(position == this->node_count){		//If the node I will delete is the last node,so I need to a tail pointer
				node* tail = NULL;							
				deletingnode = headptr;
				int counter = 1;	
				while(counter < position){				//I am sliding tail pointer position-1 times
					tail = deletingnode;
					deletingnode = deletingnode->next;
					counter++;
				}
				tail->next = NULL;						//Because tail points the last node tail->next should be NULL
				this->node_count--;		
				delete deletingnode;
				return;
			}else{										//If none of the above is statements executes, that means node that will be deleted is anywhere between first and the last node
				node* tail = NULL;		
				deletingnode = headptr;
				while(deletingnode != temp){			//I am sliding tail pointer as long as deletingnode is not equal to the temp, so tail points to previous node from the deleting node.
					tail = deletingnode;
					deletingnode = deletingnode->next;
				}
				tail->next = deletingnode->next;		//Because tail points previous node from the deleting node tail->next points deletingnode->next
				this->node_count--;
				delete deletingnode;
				return;
			}
		}else{
			temp = temp->next;							//If temp->size is not equal to shoe size I want to sell, I slide the temp and I also increase position by 1					
			position++;
		}
	}
	
	if(!found){
		cout<<"NO_STOCK"<<endl;							//If the shoe I search is not in the list I should print "NO_STOCK"
		return;
	}
}
void stock::current_stock(){							//Prints whole linked list
	node* temp = headptr;
	while(temp){
		cout<<temp->size<<":"<<temp->quant<<endl;
		temp = temp->next;
	}
}
void stock::clear(){									//Deletes whole linked list
	node* temp;
	while(headptr){
		temp = headptr;
		headptr = headptr->next;
		delete temp;
	}
	this->node_count = 0;
}

int main(int argc, char* argv[]){
	char* file = argv[1]; 
	
	FILE* fptr;
	struct stock mystock;
	mystock.create();
	int num;
	
	if( (fptr = fopen(file,"r") ) == NULL ){
		cout<<"File could not be opened!"<<endl;
	}else{
		
		while(!feof(fptr)){
			fscanf(fptr,"%d",&num);
			if(num > 0){
				mystock.add_stock(num);
			}else if(num < 0){
				mystock.sell(abs(num));
			}else{
				mystock.current_stock();
			}
		}
	}
	fclose(fptr);
	mystock.clear();	
	return 0;
}