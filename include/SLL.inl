#ifndef SLL_INL
#define SLL_INL
#include"..\include\SLL.hpp"
template<class T>
SLL<T>::SLL(){
    head=nullptr;
    tail=nullptr;
}
template<class T>
void SLL<T>::push(const T & val){
}
template<class T>
void SLL<T>::pop(const T & key){
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
    if(head==nullptr)   //to be careful, the function still works if removing this condition
        tail=nullptr;
    delete dummy;
}


#endif