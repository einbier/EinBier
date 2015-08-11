#include <Common/Message.h>

#include <Operator/Barman.h>
#include <Operator/CoreOperator.h>

#include <string>
#include <map>
#include <list>
#include <algorithm> //std::find

int Barman::m_max_id = -1;
std::list<Barman::element> Barman::m_list_of_element;
std::map<int, Barman::element*> Barman::m_id_to_element;


//Function quite useless, now...
void Barman::Init()
{
    Message::Info("Welcome to the tavern, Bro'!");
}

void Barman::Clear()
{
    m_id_to_element.clear();
    m_list_of_element.clear();
}


bool Barman::doesCoreOperatorExists(CoreOperator *op)
{
    int id = getIdOfCoreOperator(op);
    return (id > 0);
}

int Barman::getIdOfCoreOperator(CoreOperator *op)
{
    Barman::element el(op);
    //Find the element in the list
    std::list<Barman::element>::iterator it_find;
    it_find = std::find(m_list_of_element.begin(), m_list_of_element.end(), el);
    if(it_find != m_list_of_element.end())
        return it_find->m__id;
    else
        return -1;
}

CoreOperator* Barman::get_CoreOperator_ptr(int id)
{
    if ( m_id_to_element.find(id) == m_id_to_element.end() )
	return nullptr;
    else
    {
	Barman::element *el = nullptr;
	el = m_id_to_element[id];
	return el->m__ptr;
    }
}


int Barman::CreateCoreOperator(int row, int col)
{
    m_max_id++;
    int id = m_max_id;
    CoreOperator *coreop = new CoreOperator(id, row, col);
    Barman::element new_elem(coreop, id);
    m_list_of_element.insert(m_list_of_element.end(), new_elem);
    m_id_to_element[id] = &(m_list_of_element.back());
    Message::Info("Barman: I successfully created this guy: %d [%p]", id, op);
    new_elem.m__delete_ptr = false; //otherwise, trouble
    return id;
}

/*
int Barman::removeCoreOperator(int op_id)
{
    // check if an CoreOperator with this id exists
    std::map<int, Barman::element*>::iterator map_find;
    map_find = m_id_to_element.find(op_id);
    // if it does, remove it from the list and from the maps
    if (map_find != m_id_to_element.end()) {
        // The value *(map_find->second) is an Barman::element
        std::list<element>::iterator it_find;
        it_find = find(m_list_of_element.begin(),
                       m_list_of_element.end(),
                       *(map_find->second));
        if (it_find == m_list_of_element.end()) {
        Message::Info("Barman: I do not find this guy: %d", op_id);
            return -2;
        }
        m_list_of_element.erase(it_find);
        m_id_to_element.erase(map_find);
        Message::Info("Barman: I kicked this guy: %d", op_id);
        return 0;
    }
    Message::Info("Barman: I do not find this guy: %d", op_id);
    return -1;
}

int Barman::removeCoreOperator(CoreOperator *op_ptr)
{
    Barman::element el_aux(op_ptr);
    // check if an object with this name exists
    std::list<Barman::element>::iterator map_find;
    map_find = std::find(m_list_of_element.begin(), m_list_of_element.end(), el_aux);
    // if it does, remove it from the list and from the maps
    if (map_find != m_list_of_element.end()) {
        int id = map_find->m__id;
        m_list_of_element.erase(map_find);
        m_id_to_element.erase(id);
        Message::Info("Barman: I kicked this guy: %d", id);
        return 0;
    }
    return -1;
}
*/

int Barman::DecreaseNumberOfPointing(int op_id)
{
    // check if an CoreOperator with this id exists
    std::map<int, Barman::element*>::iterator map_find;
    map_find = m_id_to_element.find(op_id);
    // if it does, decreases the number of pointing Operator to this CoreOperator
    if (map_find != m_id_to_element.end()) {
        // The value *(map_find->second) is an Barman::element
        std::list<element>::iterator it_find;
        it_find = find(m_list_of_element.begin(),
                       m_list_of_element.end(),
                       *(map_find->second));
        if (it_find == m_list_of_element.end()) {
        Message::Info("Barman: I do not find this guy: %d", op_id);
            return -2;
        }
	int nPointer = it_find->DecreaseNumberOfPointing();
	if( nPointer == 0)
	{
	    m_list_of_element.erase(it_find);
	    m_id_to_element.erase(map_find);
	    Message::Info("Barman: I kicked this guy: %d", op_id);
	}
        return nPointer;
    }
    Message::Info("Barman: I do not find this guy: %d", op_id);
    return -1;
}


void Barman::Print()
{
    int n_operator = m_list_of_element.size();
    if(n_operator == 0)
	Message::Info("The tavern is empty!");
    else
    {
	Message::Info("Clients in the tavern:");
	for(std::map < int, Barman::element* >::const_iterator it = m_id_to_element.begin();
	    it != m_id_to_element.end(); ++it)
	{
	    Message::Info("Map(id,ptr,bool):%d %p %d",it->first, it->second->m__ptr, it->second->m__delete_ptr);
	}
    }
}
