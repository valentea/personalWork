#include <iostream>
#include "delist.h"

using namespace std;

DEList::DEList() {
    listSize = 0;
    DEHead = NULL;
    DETial = NULL;
}

DEList::~DEList() {
    while (listSize != 0) {
        pop_back();
    }
}

bool DEList::empty() {
    return listSize == 0;
}

int DEList::size() {
    return listSize;
}

int DEList::front() {
    if (DEHead == NULL) {
        return -1;
    }
    return DEHead->val;
}

int DEList::back() {
    if (DETial == NULL) {
        return -1;
    }
    return DETial->val;
}

void DEList::push_front(int new_val) {
    DEItem *mNode = new DEItem;
    mNode->val = new_val;
    mNode->prev = NULL;
    if (listSize == 0) {
        mNode->next = NULL;
        DEHead = mNode;
        DETial = mNode;
        listSize++;
    }
    else {
        mNode->next = DEHead;
        DEHead->prev = mNode;
        DEHead = mNode;
        listSize++;
    }
}

void DEList::push_back(int new_val) {
    DEItem *mNode = new DEItem;
    mNode->val = new_val;
    mNode->next = NULL;
    if (listSize == 0) {
        mNode->prev = NULL;
        DEHead = mNode;
        DETial = mNode;
        listSize++;
    }
    else {
        mNode->prev = DETial;
        DETial->next = mNode;
        DETial = mNode;
        listSize++;
    }
}

void DEList::pop_front() {
    if (listSize == 0) { ;
        return;
    }
    else if (listSize == 1) {
        delete DEHead;
        DEHead = NULL;
        DETial = NULL;
        listSize--;
    }
    else if (listSize > 1) {
        DEItem *temp = DEHead->next;
        temp->prev = NULL;
        delete DEHead;
        DEHead = temp;
        listSize--;
    }
}

void DEList::pop_back() {
    if (listSize == 0) {
        return;
    }
    else if (listSize == 1) {
        delete DETial;
        DEHead = NULL;
        DETial = NULL;
        listSize--;
    }
    else if (listSize > 1) {
        DEItem *temp = DETial->prev;
        temp->next = NULL;
        delete DETial;
        DETial = temp;
        listSize--;
    }
}
