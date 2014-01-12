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
	class iterator {
		node* ptr;
	public:
		iterator(node *p=0) : ptr(p) {}
		iterator& operator++()    { ptr = ptr->next; return *this; } // itr++;
		friend class slist;
	};
	
	slist() : head(new node),currentSize(0) {}
	slist(const slist& rhs) : head(new node),currentSize(0) {
		node* p = head, *q = rhs.head;
		for(int i=0;i < rhs.currentSize; i++) { insert(p, new node(*(q=q->next))); p = p->next; }
	}
	
	iterator begin() { return iterator(head); }
	
	bool exist(const T& x) {
		int count = 0;
		node* it = head;
		for(node* it = head; it->next!=NULL; it=it->next) {
			if(it->next->element == x) count++;
		}
		return count>0;
	}
	
	void find(const T& x) {
		if(exist(x)) {
			printf("%d exist! Erase.\n",x);
			find_erase(x);
		}
		else {
			printf("%d not exist! Insert.\n",x);
			find_insert(x);
		}
	}
	
	void find_insert(const T& x) { insert(head,x); }
	void find_erase(const T& x) {
		for(node* it = head->next; it->next!=NULL; it=it->next) {
			if(it->next->element == x) erase(it);
		}
	}
	
	iterator insert(iterator pos, const T& x) { return insert(pos.ptr, new node(x)); }
	void push (const T& x) { insert(head, x); } // insert behind the head.
	
	bool remove(const T& x) { return remove(find(x)); }
	
    bool empty() const { return currentSize==0; }
	int Size() { return currentSize; }
	
	void printList() { int i=1; node* p=head->next; while(i<=currentSize) { cout<<p->element<<" "; p=p->next; i++; } }

private:
	node* head;
	int currentSize;
    node* insert(node* p, node* q) { q->next = p->next; p->next = q; currentSize++; return q; }
    node* insert(node* p, const T& x) { return insert(p, new node(x)); }
    void  erase (node* p) { node* q = p->next; p->next = q->next; currentSize--; delete q;}
};


// bugs infected. need more works to solve.
int main() {
	slist<int> a;
	printf("\n----------------------------------------\n");
	printf("Initialize a:\n");
	for(int i=1; i<11; i++ ) {
		a.push(i);
	}
	cout<<"a=["; a.printList(); cout<<"]"<<endl;
	cout<<"size:"<<a.Size()<<endl;
	
	printf("\n----------------------------------------\n");
	printf("erase the item if x exists, insert it otherwise:\n");
	int x;
	cout<<"x=";cin>>x;
	a.find(x);
	cout<<"a=["; a.printList(); cout<<"]"<<endl;
	cout<<"size:"<<a.Size()<<endl;
	
	return 0;
}