/*
Name: Gilbert Grundy
Assignment: Lab #1
*/

#include <iostream>
#include <cstring>


using namespace std;

//node to a LLL, used for the different sets
struct node
{
	node(); //constructor
	char * element; //element in a set
	node * next; //to the next set
};

//set which deals with the sets
class set
{
	public:
	set();		//constructor
	~set();		//destructor
	int add_A(char * source);	//add element to set A
	int display(node * head);	//display function, given a set
	int add_B(char * source);	//add element to set B
	int intersection(node * head);	//recursive function to build intersection
	int display_inter();		//display intersection of set A & B
	int uni();			//build union of set A & B
	int uni(node * head);		//recursive function to buildunion of A & B
	int display_uni();		//display the Union of set A & B
	int comp_AminusB();		//build compliment of A - B
	int comp_AminusB(node *& head);	//build compliment of A - B recursively
	int display_compA_B();		// display compliment of A - B
	int comp_BminusA();		// build compliment of B - A
	int comp_BminusA(node *& head);	// build compliment of B - A recursively
	int display_compB_A();		// display compliment of B -A	
	int cross_product(node * one);	//build cross product, go through A iteratively
	int cross_product(node * one, node * two); //build cross product, going through B for an element A
	int display_cross_product();	//display cross product
	long long power_set_cardinality_AXB(int num_elements); //calcularte and display the cardinality of power set of AXB
	int find(node * head, char * index);	//find a node, given an argument
	int copy(node *& destination, node *& source);	//copy a given node into a list
	int set_up();			//set up all LLL
	int display_all();		//display all LLL
	void destroy(node *& head);	//deallocate memory for a LLL
	private:
	node * headA;		//LLL for Set A
	node * headB;		//LLL for Set B
	node * head_inter;	//LLL for Set A-Intersect-B
	node * head_uni;	//LLL for Set A-Union-B
	node * head_AminusB;	//LLL for Set A-B
	node * head_BminusA;	//LLL for Set B-A
	node * headAXB;		//LLL for Set AXB
};

void clear(char * source); //clear an array

int main()
{
	set function; 	//object for the sets
	char tempA [1000];	//temp to capture set A from user
	char tempB [1000];	//temp to capture set B from user
	char temp_element[20];	//temp element to grab elements
	int k = 0;		//k used to load temp element with chars
	int j = 0;		//j used to grab value from user input, might not stictly be needed


	cout << "Gilbert Grundy CS251 Lab #1 \n\n";

	cout << "Please enter your elements for set A: ";

	cin.getline(tempA, 1000, '\n');

	cout << "Please enter your elements for set B: ";

	cin.getline(tempB, 1000, '\n');

	clear(temp_element); //clear temp element

	if(tempA[0])
	{
		for(int i = 0; i < (strlen(tempA) + 1); i++)
		{	//build Set A
			j = tempA[i];
			if((j == 32) || (j == 0)) // does the next element equal a space or NULL?
			{
				temp_element[k+1] = '\0';
				function.add_A(temp_element);
				k = 0;
				clear(temp_element);
			}
			else
			{
				temp_element[k] = j;
				k++;
			}
		}
	}
	clear(temp_element); // clear temp element

	cout << endl;
	
	if(tempB[0])
	{
		for(int i = 0; i < (strlen(tempB) + 1); i++)
		{	//build set B
			j = tempB[i];
			if((j == 32) || (j == 0))
			{
				temp_element[k+1] = '\0';
				function.add_B(temp_element);
				k = 0;
				clear(temp_element);
			}
			else
			{
				temp_element[k] = j;
				k++;
			}
		}
	}

	cout << endl;

	function.set_up();	//build different sets
	function.display_all();	//display all sets

	return 0;
}

//clear an array completely
void clear(char * source)
{
	for(int i = 0; i < 20; i++)
	{
		source[i] = '\0';
	}
}

//consructor for a node
node::node()
{
	element = NULL;
	next = NULL;
}

//constructor the set class
set::set()
{
	headA = NULL;
	headB = NULL;
	head_inter = NULL;
	head_uni = NULL;
	head_AminusB = NULL;
	head_BminusA = NULL;
	headAXB = NULL;
}

//destructor for set class
set::~set()
{
	destroy(headA);
	destroy(headB);
	destroy(head_inter);
	destroy(head_uni);
	destroy(head_AminusB);
	destroy(head_BminusA);
	destroy(headAXB);
}


//add element to set A
int set::add_A(char * source)
{
	node * temp = new node;
	temp->element = new char[strlen(source) + 1];
	strcpy(temp->element, source);
	
	temp->next = headA;
	headA = temp;

	if(headA) return 1;
	else return 0;
}


//gerneral display function given a node
int set::display(node * head)
{
	int success = 0;
	if(!head) return success;
	success += display(head->next);

	cout << head->element << " ";
	++success;
	return success;
}

//add an element to B
int set::add_B(char * source)
{
	node * temp = new node;
	temp->element = new char[strlen(source) + 1];
	strcpy(temp->element, source);
	
	temp->next = headB;
	headB = temp;

	if(headB) return 1;
	else return 0;
}


//build A intersect B
int set::intersection(node * head)
{
	int success = 0;
	if(!head) return success;
	success += intersection(head->next);

	if(find(headB, head->element)) //check if they match, then add
	{
		node * temp = new node;
		temp->element = new char[strlen(head->element) + 1];
		strcpy(temp->element, head->element);

		temp->next = head_inter;
		head_inter = temp;

		++success;
	}

	return success;
}


//display A intersect B 
int set::display_inter()
{
	cout << "The roster of the intersection is: ";

	int success = display(head_inter);

	if(!success) cout << "{ }";
	
	cout << "\n";

	cout << "And the cardinality of the intersection is: " << success << endl;	

	return success;
}


//Build A union B, call recursive function after copying A
int set::uni()
{
	int success = copy(head_uni, headA);
	return success + uni(headB);
}


//build A union B recursively, add elements from B if not already in A
int set::uni(node * head)
{
	int success = 0;
	if(!head) return success;
	success += uni(head->next);

	if(!find(head_uni, head->element)) //check if there is a match
	{
		node * temp = new node;
		temp->element = new char[strlen(head->element) + 1];
		strcpy(temp->element, head->element);

		temp->next = head_uni;
		head_uni = temp;

		++success;
	}

	return success;
}

//display the union
int set::display_uni()
{
	cout << "The roster of the union is: ";

	int success = display(head_uni);
	
	if(!success) cout << "{ }";

	cout << "\n";

	cout << "And the cardinality of the union is: " << success << endl;

	return success;
}


//build the complement A-B, first copy A, then delete elements that match
int set::comp_AminusB()
{
	int success = copy(head_AminusB, headA);
	return success - comp_AminusB(head_AminusB);
}


//find matches, then delete to build A-B
int set::comp_AminusB(node *& head)
{
	int success = 0;
	if(!head) return success;
	success += comp_AminusB(head->next);

	if(find(headB, head->element)) //match, then delete
	{
		node * temp = head->next;
		delete head->element;
		head->element = NULL;
		delete head;
		head = NULL;
		head = temp;	
		++success;
	}

	return success;
}


//display complement A-B
int set::display_compA_B()
{
	cout << "The roster of the complement A - B is: ";

	int success = display(head_AminusB);
	
	if(!success) cout << "{ }";

	cout << "\n";

	cout << "And the cardinality of the complement A - B is: " << success << endl;

	return success;

}

//Build complement B-A, first copy set B, then find matches to delete
int set::comp_BminusA()
{
	int success = copy(head_BminusA, headB);
	return success - comp_BminusA(head_BminusA);
}


//find matches between set B & A, then delete
int set::comp_BminusA(node *& head)
{
	int success = 0;
	if(!head) return success;
	success += comp_BminusA(head->next);

	if(find(headA, head->element)) //find match, then delete
	{
		node * temp = head->next;
		delete head->element;
		head->element = NULL;
		delete head;
		head = NULL;
		head = temp;	
		++success;
	}

	return success;
}


//Display commplement B-A
int set::display_compB_A()
{
	cout << "The roster of the complement B - A is: ";

	int success = display(head_BminusA);
	
	if(!success) cout << "{ }";

	cout << "\n";

	cout << "And the cardinality of the complement B - A is: " << success << endl;

	return success;

}


//Build AXB, first grab an element in Set A, then get cross product going through elements of Set B
int set::cross_product(node * one)
{
	int success = 0;
	if(!one) return success;

	node * temp = headA;
	
	while(temp)
	{
		success += cross_product(temp, headB);
		temp = temp->next;
		++success;
	}
	return success;
}

//recursively go through Set B with an element of A
int set::cross_product(node * one, node * two)
{
	int success = 0;
	if(!two) return success;

	char open_bracket[2] = "(";
	char comma[2] = ",";
	char close_bracket[2] = ")";
	node * temp = new node;
	temp->element = new char[strlen(one->element) + strlen(two->element) + 4];
	strcpy(temp->element, open_bracket);
	strcat(temp->element, one->element);
	strcat(temp->element, comma);
	strcat(temp->element, two->element);
	strcat(temp->element, close_bracket);

	temp->next = headAXB;
	headAXB = temp;
	++success;
	success += cross_product(one, two->next);

	return success;
}

//Display AXB
int set::display_cross_product()
{
	cout << "The roster of AXB is: ";

	int success = display(headAXB);
	
	if(!success) cout << "{ }";

	cout << "\n";

	cout << "And the cardinality of AXB is: " << success << endl;

	cout << "\nThe cardinality of the power set of AXB is: 2^" << success << endl;
//	cout << power_set_cardinality_AXB(success) << endl;

	return success;
}

//find the cardinality of a sets power set
long long set::power_set_cardinality_AXB(int num_elements)
{
	if(num_elements == 0) return 1;
	long long power = 1;
	for(int i = 0; i < num_elements; ++i)
	{
		power = power * 2;
	}

	return power;
}

//find a element in a set
int set::find(node * head, char * index)
{
	int success = 0;
	if(!head) return success;
	success += find(head->next, index);

	if(!strcmp(head->element, index)) ++success;
	
	return success;
}

//copy an element from one set to another
int set::copy(node *& destination, node *& source)
{
	int success = 0;
	if(!source) return success;

	node * temp = new node;
	temp->element = new char[strlen(source->element) + 1];
	strcpy(temp->element, source->element);

	temp->next = destination;
	destination = temp;
	++success;

	success += copy(destination, source->next);

	return success;
}

//build function
int set::set_up()
{
	int success = 0;

	success += intersection(headA);

	success += uni();

	success += comp_AminusB();

	success += comp_BminusA();

	success +=cross_product(headA);

	return success;
}


//display all of the sets
int set::display_all()
{
	int success = 0;
	
	success += display_inter();

	cout << endl;

	success += display_uni();

	cout << endl;

	success += display_compA_B();

	cout << endl;

	success += display_compB_A();

	cout << endl;

	success += display_cross_product();

	cout << endl;

	return success;
}


//deallocate the memory of one of the sets
void set::destroy(node *& head)
{
	if(!head) return;

	delete head->element;
	head->element = NULL;
	delete head;
	head = NULL;
	return;
}
