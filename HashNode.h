#include "DrachmaCurrency.h"

class HashNode {
public:
    DrachmaCurrency* data;
    bool is_occupied; // Tracks if a slot has ever been used.

    HashNode() : data(nullptr), is_occupied(false) {}
};