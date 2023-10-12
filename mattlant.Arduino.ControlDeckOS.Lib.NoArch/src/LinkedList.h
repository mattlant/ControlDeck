// LinkedList.h

#ifndef LINKEDLIST_h
#define LINKEDLIST_h


class LinkedListItemBase
{
public:
	LinkedListItemBase* next;

	LinkedListItemBase();
};

class LinkedListItem : public LinkedListItemBase
{
public:
	void* data;
	LinkedListItem(void* data);
};


class LinkedList
{
private:
	LinkedListItemBase* head;
	LinkedListItemBase* tail;
	int count;

public:
	LinkedList();

	class LinkedListIterator
	{
	private:
		LinkedListItemBase* previous;
		LinkedListItemBase* current;
		LinkedList* list_;
		bool hasStarted;

	public:
		LinkedListIterator(LinkedList* list);
		bool has_next() const;
		bool move_next();
		//Need to call this remove when using iterator to ensure safe remove/delete
		void remove_current(bool delete_item = false);
		LinkedListItemBase* get_current_item() const;
	};


	void append(void* data);
	void append(LinkedListItemBase* item);
	int getCount() const;
	void remove(const LinkedListItemBase* item, bool delete_item);
	LinkedListItemBase* getHead() const;
	LinkedListIterator get_iterator();
	void set_head_to_next(LinkedListItemBase* item, bool update_tail = true);

};

#endif
