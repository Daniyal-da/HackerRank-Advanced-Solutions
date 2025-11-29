#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

//استفاده از struct چون یه data bag هستش
struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;// برای وقتی که میخوایم از روی خود node به map برسیم مثل موقع حذف کردن
    Node(Node* p, Node* n, int k, int val) : prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {
protected: 
    map<int, Node*> mp; 
    int cp;             // Capacity
    Node* head;         // Most recently used
    Node* tail;         // Least recently used
    virtual void set(int, int) = 0;
    virtual int get(int) = 0;
};



class LRUCache : public Cache {
public:
    
    LRUCache(int capacity) {
        cp = capacity;
        head = NULL;
        tail = NULL;
    }

    //اضافه کردن نوده جدید به اول لیست
    void insert_head(Node* node) {
        node->next = head;
        node->prev = NULL;
        
        //اگر لیست خالی نبود نود قبلی که head بود  باید prev به نود جدید اشاره بکنه
        if (head != NULL) {
            head->prev = node;//[N] ⇄ [A]
        }
        
        head = node;
        
        // اگر لیست خالی بود، این نود هم head میشه هم tail
        if (tail == NULL) {
            tail = node;
        }
    }

    // تابع حذف یک نود از هر جای لیست
    void remove_node(Node* node) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            // یعنی نود ما head بوده
            head = node->next;
        }

        if (node->next != NULL) {
            node->next->prev = node->prev;
        } else {
            // یعنی نود ماtail بوده
            tail = node->prev;
        }
    }

    void set(int key, int value) override {
        //1.اگر این key از قبل توی کش هست فقط مقدار value رو اپدیت بکن و بیارش اولش لیست
        //اگه کلید پیدا نشه map.end رو بر میگردونه
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            node->value = value;
            
            // جابجایی به اول لیست
            if (node != head) {
                remove_node(node);
                insert_head(node);
            }
        } 
        // 2. اگر کلید وجود ندارد (باید جدید بسازیم)
        else {
            Node* newNode = new Node(key, value);
            
            // اگر ظرفیت پر است، باید tail را حذف کنیم
            if (mp.size() == cp) {
                Node* oldTail = tail;
                mp.erase(oldTail->key);//حذف از map اون kay که نگه داخله node ساختیم اینجا به درد خورد
                remove_node(oldTail);
                delete oldTail; // آزادسازی حافظه
            }
            
            // اضافه کردن نود جدید
            insert_head(newNode);
            mp[key] = newNode;
        }
    }

    int get(int key) override {
        // اگر کلید پیدا نشد
        if (mp.find(key) == mp.end()) {
            return -1;
        }
        
        // اگر پیدا شد، باید بیاد اول لیست (چون الان استفاده شد)
        Node* node = mp[key];
        if (node != head) {
            remove_node(node);
            insert_head(node);
        }
        
        return node->value;
    }
};



int main() {
    // تست LRU Cache
    LRUCache* l = new LRUCache(2); // ظرفیت 2
    
    l->set(1, 10); 
    l->set(2, 20); 
    
    cout << l->get(1) << endl; //10
    
    l->set(3, 30); //ظرفیت پره پس 2 حذف میشه
    
    cout << l->get(2) << endl; //-1
    cout << l->get(3) << endl; //30
    
    return 0;
}
/*
تویه این کد باید یک LRU Cache بسازیم
LRU (Least Recently Used)
از map برایه پیدا کردن سریع node بر اساس کلید استفاده کردم
و از doubly linked list برایه نگه داشتن ترتیب

*/