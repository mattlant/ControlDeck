// 
// 
// 

#include "LinkedList.h"

LinkedListItemBase::LinkedListItemBase() : next(nullptr)
{
}

LinkedListItem::LinkedListItem(void* data) : LinkedListItemBase(), data(data)
{
}

LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0)
{
}

void LinkedList::append(void* data)
{
	LinkedListItem* newItem = new LinkedListItem(data);
	count++;

	if (head == nullptr)
	{
		head = newItem;
		tail = newItem; // Set tail to newItem when list is empty
		newItem->next = head; // Point to itself making it circular
	}
	else
	{
		tail->next = newItem; // Link the current tail's next to the new item
		newItem->next = head; // Point the new item to the head, making it circular
		tail = newItem; // Update the tail to the new item
	}
}

void LinkedList::append(LinkedListItemBase* item)
{
	count++;

	if (head == nullptr)
	{
		head = item;
		tail = item; // Set tail to newItem when list is empty
		item->next = head; // Point to itself making it circular
	}
	else
	{
		tail->next = item; // Link the current tail's next to the new item
		item->next = head; // Point the new item to the head, making it circular
		tail = item; // Update the tail to the new item
	}
}

int LinkedList::getCount() const
{
	return count;
}

void LinkedList::remove(const LinkedListItemBase* item, const bool delete_item = false) {
    if (!head || !item) return; // empty list or null node

    // If the head node is the one to be removed
    if (head == item) {
        head = head->next;
		if(delete_item)
			delete item;
        return;
    }

    LinkedListItemBase* prev = nullptr;
    LinkedListItemBase* current = head;
    while (current && current != item) {
        prev = current;
        current = current->next;
    }

    if (current == item) { // node found
        prev->next = current->next;
		if(delete_item)
			delete item;
    }
}

LinkedListItemBase* LinkedList::getHead() const
{
	return head;
}

LinkedList::LinkedListIterator LinkedList::get_iterator()
{
	return LinkedListIterator(this);
}

LinkedList::LinkedListIterator::LinkedListIterator(LinkedList* list)
	: current(list->head), list_(list), hasStarted(false)
{
}

bool LinkedList::LinkedListIterator::has_next() const
{
	return current != nullptr && current != list_->tail;
}

bool LinkedList::LinkedListIterator::move_next()
{
	if(current == nullptr)
		return false;

	// If the iteration hasn't started, we set the flag and return the head item
	if (!hasStarted)
	{
		hasStarted = true;
		return true;
	}

	if (!has_next())
		return false;

	// Move to the next item
	previous = current;
	current = current->next;

	return true;
}

void LinkedList::LinkedListIterator::remove_current(bool delete_item)
{
	LinkedListItemBase* to_remove = current;

	if(current == list_->head)
		hasStarted = false;
	current = previous;

	list_->remove(to_remove, delete_item);
}


LinkedListItemBase* LinkedList::LinkedListIterator::get_current_item() const
{
	return current;
}

void LinkedList::set_head_to_next(LinkedListItemBase* item, bool update_tail)
{
	head = item->next;
	if(update_tail)
		tail = item;
}
