#ifndef KEYVALUESTORECHALLENGE_KEYVALUESTORE_H
#define KEYVALUESTORECHALLENGE_KEYVALUESTORE_H


#include <string>


/**
 * Key Value Store with an in-memory storage limit of entries.
 * If the limit is reached, the Key Value Store should employ a smart strategy to swap out data to disk.
 */
class key_value_store {

public:

    explicit key_value_store(int storage_size) : storage_size(storage_size) {

    }

    /**
     * Insert a key value pair to the store
     * @param key
     * @param value
     */
    void insert(const std::string &key, const std::string &value);

    /**
     * Remove the key value pair, with the given key
     * @param key
     */
    void remove(const std::string &key);

    /**
     * Retrieves the value of the given key.
     * @param key
     * @return Returns a pair. The first value signals if an entry for the given key was found.
     * The second value, is the found value. If no entry was found, the returned value is undefined.
     */
    std::pair<bool, std::string> get(const std::string &key);

private:
    /**
     * Maximum number of entries
     */
    const int storage_size;

};


#endif //KEYVALUESTORECHALLENGE_KEYVALUESTORE_H
