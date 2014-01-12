//3.31 使用单项链表高效地实现栈类.要求不含头尾结点
#include <iostream>
using namespace std;

template<typename T>
class slist {
	struct node {
		T element;
		node* next;
		
		node(const T& x=0, node* N=0) : element(x),next(N) {}
	};
public:
	
	slist() : top(new node),currentSize(0) {}
	slist(const slist& rhs) : top(new node),currentSize(0) {
		node* p = top, *q = rhs.top;
		for(int i=0;i < rhs.currentSize; i++) { insert(p, new node(*(q=q->next))); p = p->next; }
	}
	
	// insert on the top.
	void push(const T& x) {
		if(currentSize == 0)       { top->element = x; currentSize++; }
		else if(currentSize > 0)  { node* newTop = new node(x); newTop->next = top; top = newTop; currentSize++; }
		else printf("something wrong!\n");
	}
	
	void pop() {
		if(currentSize == 0)       { printf("the list is empty.\n"); }
		else if(currentSize > 0)   { node* q = top; top = top->next; delete q; currentSize--; }
	}
	
	int Size() { return currentSize; }
	
	void printList() {
		int i=1; node* p=top; 
		while(i<=currentSize) { cout<<p->element<<" "; p=p->next; i++; } 
		cout<<endl;
	}

private:
	node* top;
	int currentSize;
    node* insert(node* p, node* q) { q->next = p->next; p->next = q; currentSize++; return q; }
    node* insert(node* p, const T& x) { return insert(p, new node(x)); }
    void  erase (node* p) { node* q = p->next; p->next = q->next; currentSize--; delete q;}
};

int main() {
	slist<int> a;
	printf("--------------------------------------------------\n");
	printf("push 1 to 10 into the stack made from slist.\n\n");
	for(int i=1;i<=10;i++) { a.push(i); a.printList(); }
	cout<<"\nsize:"<<a.Size()<<endl;
	
	printf("\n--------------------------------------------------\n");
	printf("pop 11 times to clear the stack. // the final pop is to ensure stack's empty.\n");
	for(int i=1;i<=11;i++) { a.pop(); a.printList(); } 
	cout<<"size:"<<a.Size()<<endl;
	
	
	return 0;
}