//Assignment 3 
//Shubham gupta
// Following code is not entirely my own work, parts of it have been taken directly from StackOverflow for references.
// MY OUTPUT OF TEST CASE 9 SEEMS TO BE CORRECT, BUT NOT PASSING IN WEB SUBMISSION.  
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int T_S = 26;
class HashTable {
   public:
      string k;
      char v;
      HashTable(string k, char v) {
         this->k = k;
         this->v = v;
      }
};
class DelNode:public HashTable {
   private:
      static DelNode *en;
      DelNode():HashTable("Shubham", '#') {}
   public:
      static DelNode *getNode() {
         if (en == NULL)
            en = new DelNode();
         return en;
      }
};
DelNode *DelNode::en = NULL;
class HashMapTable {
   public:
      HashTable **ht;
   public:
      HashMapTable() {
         ht = new HashTable* [T_S];
         for (int i = 0; i < T_S; i++) {
            ht[i] = NULL;
         }
      }
      int HashFunc(string k) {

      	int len = 0; 
		len = k.length();
		char ind =  k[len-1];
		int index = int(ind)-97;
		return index;

      }
      int HashFunc(int k) {

      	
		return k%T_S;

      }
      void Insert(string k, char v) {
         int hash_val = HashFunc(k);
         int init = -1;
         int delindex = -1;
         while (hash_val != init && (ht[hash_val]  == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k != k)) {
            if (init == -1)
               init = hash_val;
            if (ht[hash_val] == DelNode::getNode())
               delindex = hash_val;
               hash_val = HashFunc(hash_val + 1);
         }
         if (ht[hash_val] == NULL || hash_val == init) {
            if(delindex != -1)
               ht[delindex] = new HashTable(k, v);
            else
               ht[hash_val] = new HashTable(k, v);
         }
         if(init != hash_val) {
            if (ht[hash_val] != DelNode::getNode()) {
               if (ht[hash_val] != NULL) {
                  if (ht[hash_val]->k== k)
                     ht[hash_val]->v = v;
               }
            } else
            ht[hash_val] = new HashTable(k, v);
         }
      }
      void display()
      	{
      for (int i = 0; i < T_S; i++) 
      		{
      			if(ht[i] != NULL && ht[i]->k != "Shubham")
            		{	
            			if(i < T_S)
            			{
            				cout<<ht[i]->k<<" ";
            			}
            			else
            			{
            				cout<<ht[i]->k;
            			}
           			}
            }
        cout<<endl;
        }
     

      void Remove(string k) {
         int hash_val = HashFunc(k);
         int init = -1;
         while (hash_val != init && (ht[hash_val] == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k!= k)) {
            if (init == -1)
               init = hash_val;
               hash_val = HashFunc(hash_val + 1);
         }
         if (hash_val != init && ht[hash_val] != NULL) {
            delete ht[hash_val];
            ht[hash_val] = DelNode::getNode();
         }
      }
      ~HashMapTable() {
         delete[] ht;
      }
};

int main()
{
   HashMapTable hash;
   string k;
   char v;
   int len_key = 0;
   string new_k;
   //This will keep taking input until there is no input 
   while(cin >> k) 
   {   
      len_key = k.length();
      //last letter of word being our value
		v = k[len_key-1];
		//our key without the first letter of ADD(A) or DELETE(D)
		new_k = k.substr(1, len_key);

		if(k[0]=='A')
		{
			hash.Insert(new_k, v);
		}          
		if(k[0]=='D')
		{
			hash.Remove(new_k);
		}
   }
   //displaying from a to z 
   hash.display();
   return 0;
}