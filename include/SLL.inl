#ifndef SLL_INL
#define SLL_INL
#include"..\include\SLL.hpp"
template<class T>
SLL<T>::SLL(){
    head=nullptr;
    tail=nullptr;
}


template<class T>
void SLL<T>::pop(const T& key){
    Node* dummy=new Node;
    dummy->next=head;
    Node* cur=dummy;
    while(cur->next!=nullptr){
        if(cur->next->data==key){
            Node* del=cur->next;
            cur->next=del->next;
            if(del==tail)
                tail=cur;
            delete del;
            break;
        }
        cur=cur->next;
    }
    head=dummy->next;
    if(head==nullptr)   //to be careful through the function still works if removing this condition
        tail=nullptr;
    delete dummy;
}

template<class T>
void SLL<T>::clearHistory(){
    while(head!=nullptr){
        Node* del=head;
        head=head->next;
        delete del;
    }
    tail=nullptr;
}

template<class T>
int SLL<T>::countNodes(Node* head){
    int ans=0;
    while(head!=nullptr){
        ++ans;
        head=head->next;
    }
    return ans;
}
template<class T>
void SLL<T>::push(const T& key){
    Node* pNew=new Node(key);
    if(head==nullptr){
        head=pNew;
        tail=head;
        return;
    }
    tail->next=pNew;
    tail=pNew;  
    if(countNodes(head)>20){
        pop(head->data);
    }
}


#endif