#ifndef SLL_INL
#define SLL_INL

#include<SLL.hpp>
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

void StrToCharArr(char*& arr, const std::string& str, int len) {//count '\0' in len
    #pragma warning(suppress : 4996)
    strcpy(arr, str.c_str());
}
template<class T>
bool SLL<T>::saveSLLStr(const std::string& path) {

    fout.open(path, ios::binary);
    if (!fout.is_open()) {
        //cout << "Can't open the file for writing!";
        return false;
    }

    Node* cur = head;
    while (cur != nullptr) {
        std::string keyword = cur->data;
        int len = keyword.size()+1;
        char* arr = new char[len];
        StrToCharArr(arr, keyword, len);
        fout.write((char*)&len, sizeof(int));
        fout.write(arr, len);
        cur = cur->next;
    }

    char end = '\0';
    fout.write((char*)&end, 1);

    fout.close();
    if (fout.bad()) {
        //cout<<"Error occured in writing time
        return false;
    }
    return true;
}
#endif