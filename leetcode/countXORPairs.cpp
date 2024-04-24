#include<vector>
using namespace std;

struct TrieNode{
    TrieNode* children[2];
    int count;
    TrieNode():count(0), children({nullptr, nullptr}){};
};

struct Trie{
    TrieNode* root;
    int TOTALBITS;
    
    Trie(int TOTALBITS):TOTALBITS(TOTALBITS), root(new TrieNode()){};

    void insert(int number){
        TrieNode* current = root;
        for(int i = TOTALBITS-1; i >=0; i-- ){
            current->count++;
            int bit = (number>>i)&1;
            if(current->children[bit] == nullptr){
                current->children[bit] = new TrieNode();
            }
            current = current->children[bit];
        }
        current->count++;
    }

    int countXorLowerThanValue(int numberB, int value){
        int count = 0;
        TrieNode* current = root;
        for(int i = TOTALBITS-1; i>=0; i--){
            if(current == nullptr) break;
            int bitB = (numberB>>i)&1;
            int bitV = (value>>i)&1;

            int bitWant = bitB^0;
            TrieNode* childWant = current->children[bitWant];
            if(bitV == 1){
                // means whatever leads to bitV to be 0 , should be counted. cause that makes the xor smaller than v
                // a^b^b gives a
                // we want a^b to be zero
                // then 0^b gives us the bit we want from a or the trie
                if(childWant) count+= childWant->count;
                current = current->children[bitWant ^ 1];
            }
            // else| bitv is 0 then whatever will lead the bitv to be 1 shall be skipped cause the xor will be bigger than the value
            //       and the route which leads the bit to be 0 shall be explored
            else current = childWant;
        }
        return count;
    }
};

class Solution {
public:
    
    int countPairs(vector<int>& nums, int low, int high) {
        ++high;
        int count = 0;
        Trie myTrie(32);
        for(int num: nums){
            int x = myTrie.countXorLowerThanValue(num, high);
            count+=x;
            x =  myTrie.countXorLowerThanValue(num, low);
            count-=x;
            myTrie.insert(num);
        }
        return count;
    }
};
