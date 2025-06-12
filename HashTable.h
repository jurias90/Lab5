#include "HashNode.h"

#define TABLE_SIZE 29

class HashTable {
public:
    HashTable() : count(0), numCollisions(0) {
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i].data != nullptr) {
                delete table[i].data;
                table[i].data = nullptr;
            }
        }
    }

    void insert(DrachmaCurrency* data);
    void deleteData(const DrachmaCurrency& target);
    int search(const DrachmaCurrency& target);
    int getNumItems() const { return count; }
    int getNumCollisions() const { return numCollisions; }
    double getLoadFactor() const { return static_cast<double>(count) / TABLE_SIZE; }
    void print() const;

private:
    HashNode table[TABLE_SIZE];
    int count; // Number of actual items in the table
    int numCollisions; // Total collisions during insertion


    int hashFunc(const DrachmaCurrency& data) {
        int M = 2;
        int N = 3;
        int w = data.getWholeValue();
        int f = data.getFractionalValue();
        return (M * w + N * f) % TABLE_SIZE;
    }

    // Private method to clean and rebuild the table
    void rehash();
};

/**
   Method insert(data)
       -This method will add a new node to the hash table
       Pre: data - the currency data to be added
       Post: add the data into the hash table if it's not in the table yet and the table is not full
       Return: N/A
   **/
inline void HashTable::insert(DrachmaCurrency* data) {
    if (!data) {
        throw std::invalid_argument("Cannot insert a NULL pointer.");
    }

    int index = hashFunc(*data);
    int i = 0;
    bool collisionOccurred = false;

    // Probe to find an available slot.
    int probeIndex = index;
    while (table[probeIndex].is_occupied && table[probeIndex].data != nullptr) {
        if (table[probeIndex].data->isEqual(*data)) {
            // return if data is already in the table
            return;
        }
        if (!collisionOccurred) {
            numCollisions++;
            collisionOccurred = true;
        }
        i++;
        probeIndex = (index + i * i) % TABLE_SIZE;

        if (i >= TABLE_SIZE) {
            // Check if the table is truly full of data.
            if (count == TABLE_SIZE) {
                throw std::length_error("The hash table is completely full of data.");
            }

            // Rehash to clean up the placeholders.
            rehash();

            // retry to insert
            insert(data);
            return;
        }
    }

    // Insert the data into the found slot
    table[probeIndex].data = data;
    table[probeIndex].is_occupied = true;
    count++;
}

/**
   Method deleteData(target)
       -This method will delete the target currency from the table
       Pre: target - the currency target to be removed
       Post: remove the target from the table if found, but keep the node occupied as a placeholder for probe chain search
       Return: N/A
   **/
inline void HashTable::deleteData(const DrachmaCurrency& target) {
    if (count == 0) return; // Table is empty

    int index = search(target);

    if (index != -1) {
        // Found the item. Delete the data and leave a empty place holder to keep the probe chain.
        delete table[index].data;
        table[index].data = nullptr;
        // table[index].is_occupied remains true.
        count--;
    }
}

/**
   Method search(target)
       -This method will search the target currency from the table
       Pre: target - the currency target to be searched
       Post: return the index of the target if found or -1
       Return: index of hash node holding the target or -1
   **/
inline int HashTable::search(const DrachmaCurrency& target) {
    if (count == 0) return -1;

    int index = hashFunc(target);
    int i = 0;

    // The loop must continue as long as the slot has been occupied,
    // because it could contain a valid item or a placeholder.
    // The loop terminates only when we find a never-occupied slot.
    int probeIndex = index;
    while (table[probeIndex].is_occupied) {
        // Check if the current slot contains the target item
        if (table[probeIndex].data != nullptr && table[probeIndex].data->isEqual(target)) {
            return probeIndex; // Found it
        }

        i++;
        probeIndex = (index + i * i) % TABLE_SIZE;

        if (i >= TABLE_SIZE) {
            return -1;
        }
    }

    return -1;
}

/**
   Method rehash()
       -This method will empty the hash table and recreate it to remove all the placeholders to make up space
       Pre: the hash table
       Post: the hash table with all placeholder removed
       Return: N/A
   **/
inline void HashTable::rehash() {
    // Create a temporary vector to hold the pointers to the actual data.
    DrachmaCurrency** oldData;
    oldData = new DrachmaCurrency*[count];
    int j = 0;

    for (int i = 0; i < TABLE_SIZE && j < count; ++i) {
        if (table[i].data != nullptr) {
            oldData[j++] = table[i].data;
        }
    }

    // Reset the current table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i].data = nullptr;
        table[i].is_occupied = false;
    }
    count = 0;
    numCollisions = 0;

    // Re-insert the data
    for (int i = 0; i < count; i++) {
        insert(oldData[i]);
    }
    delete [] oldData;
}

/**
   Method print()
       -This method will print the hash table data and its load factor and number of collisions
       Pre: the hash table
       Post: standard output of the hash table data and its load factor and number of collisions
       Return: N/A
   **/
inline void HashTable::print() const {
    std::cout << "The hash table data:" << std::endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].data != nullptr) {
            table[i].data->print();
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Loaded: " << count << " items" << std::endl;
    std::cout << "The load factor: " << getLoadFactor() << std::endl;
    std::cout << "The number of collisions: " << getNumCollisions() << std::endl;
}
