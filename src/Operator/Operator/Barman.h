#pragma once

#include<Common/Message.h>

#include<Operator/CoreOperator.h> // for the delete

#include<string>
#include <map>
#include <list>

/*class Barman
The Barman is the boss: he manages every CoreOperator.
Whenever an CoreOperator is created, it is recorded by the Barman
The Barman can also kick every CoreOperator he wants
Before closing a program, do not forget do clean the tavern by calling Barman::Clear();
Note: Barman is not instanciable. He is everywhere. No need to create him.
 */

class Barman
{
// This is the container of an CoreOperator in the handler
public:
    struct element {
        CoreOperator* m__ptr;   // pointer to the CoreOperator
        int m__id;          // id of the CoreOperator
	bool m__delete_ptr; // false if this element must NOT destroy the associated CoreOperator
        int m__pointing;    // number of objects pointing at this operator
	
        // constructor
    element():element(nullptr, -1, false){}
    element(CoreOperator *ptr, int id, bool delete_ptr):
	m__ptr(pr), m__id(id), m__delete_ptr(delete_ptr), m__pointing(1) {}
	
        // destructor
        ~element() { if(m__delete_ptr) {delete m__ptr;} }
        // copy constructor (useless I think)
        element(const element& rhs) {
            m__ptr = rhs.m__ptr;
            m__id = rhs.m__id;
            m__delete_ptr = rhs.m__delete_ptr;
	    m__pointing = rhs.m__pointing;
        }
	
        // overload the == operator (according to the id)
        bool operator==(const element& rhs) const {
            return (m__id == rhs.m__id);
        }
	
        // overload the < operator (according to the id)
        bool operator<(const element& rhs) const {
            return (m__id < rhs.m__id);
        }
	
        // copy operator
        element& operator=(const element& rhs) {
            m__ptr = rhs.m__ptr;
            m__id = rhs.m__id;
            m__pointing = rhs.m__pointing;
            return *this;
        }
	    
	//Reduce the number of pointing of 1 and return the number of pointing
	    int DecreaseNumberOfPointing(){m__pointing--; return m__pointing;}

	void Print(){
	    Message::Debug("Printing Element");
	    Message::Info("m__ptr         = %p", m__ptr);
	    Message::Info("m__id          = %d", m__id);
	    Message::Info("m__delete_ptr  = %d", m__delete_ptr);
	}
    };
    
private:
    static int m_max_id;
    /**@brief contains all the instances of the element objects (pointers to CoreOperator) */
    static std::list<element> m_list_of_element;
    static std::map<int, element*> m_id_to_element;
    static std::map<element*, int> m_element_to_id; //For reverse search (works ??)

// Remove a CoreOperator in the Barman. Warning, this DESTROYS the CoreOperator.
// Return 0 (ok) or 1 (error)
//    static int removeCoreOperator(int op_id);
//    static int removeCoreOperator(CoreOperator *op_ptr);

public:
    Barman(){}
    ~Barman(){}
    static void Init();
    static void Clear();
// Add an CoreOperator to the Barman.
// Return the id of the operator (will be set to the operator)
// destroyIt precises whether the Barman must destroy it or not
    static int CreateCoreOperator(CoreOperator *op, int row, int col);
//Return the id of an CoreOperator (in fact, its pointer)
//return -1 if not found
    static int getIdOfCoreOperator(CoreOperator *op);
//Return the pointer to CoreOperator
    static CoreOperator* get_CoreOperator_ptr(int id);
//Check if an operator already exist (in fact, check the pointers!!)
    static bool doesCoreOperatorExists(CoreOperator *op);
    static void Print();

    int DecreaseNumberOfPointing(int id);
};
