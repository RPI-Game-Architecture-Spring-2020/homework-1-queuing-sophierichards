/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"
#include <mutex>
struct ga_queue_impl {
	std::mutex head_lock;
	std::mutex tail_lock;
	node* tail;
	node* head;
	int count;
};
//void* ga_queue::_impl = 0;
ga_queue::ga_queue(int node_count)
{
	//ga_queue_impl* impl = new ga_queue_impl();
	count = 0;
	node* hd = new node();
	hd->next_ptr = NULL;
	head = hd;
	tail = hd;
	// TODO:
	// Initialize the queue.
	// For extra credit, preallocate 'node_count' elements (instead of
	// allocating on push).
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

ga_queue::~ga_queue()
{
	// TODO:
	// Free any resources held by the queue.
	while (head != NULL) {
		node* new_head = head->next_ptr;
		delete(head);
		head = new_head;
	}
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

void ga_queue::push(void* data)
{
	node* new_node = new node();
	new_node->value = data;
	new_node->next_ptr = NULL;
	//ga_queue_impl* impl = static_cast<ga_queue_impl*>(_impl);
	tail_lock.lock();
	tail->next_ptr = new_node;
	tail = new_node;
	count++;
	tail_lock.unlock();
	// TODO:
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
}

bool ga_queue::pop(void** data)
{
	//ga_queue_impl* impl = static_cast<ga_queue_impl*>(_impl);
	head_lock.lock();
	node* old_head = head;
	node* new_head = old_head->next_ptr;
	if (new_head == NULL) {
		head_lock.unlock();
		return false;
	}
	*data = new_head->value;
	head = new_head;
	count--;
	head_lock.unlock();
	delete(old_head);
	// TODO:
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.
	// See https://www.research.ibm.com/people/m/michael/podc-1996.pdf
	return true;
}

int ga_queue::get_count() const
{
	//ga_queue_impl* impl = static_cast<ga_queue_impl*>(_impl);
	// TODO:
	// Get the number of elements currently in the queue.
	return count;
}
