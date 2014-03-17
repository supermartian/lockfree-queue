/*
 * Copyright (C) 2014 Yuzhong Wen<supermartian@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PKT_QUEUE_H
#define PKT_QUEUE_H

#include <pthread.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/*
 * Here we implement a lock-free queue for buffering the
 * packets that come out from multiple filters.
 *
 * */

struct queue_root {
	struct queue_node *head;
	struct queue_node *tail;
	volatile unsigned int size;
};

struct queue_node {
	void *n;
	struct queue_node *next;
};

void init_queue(struct queue_root **root);
int queue_add(struct queue_root *root, void *val);
void *queue_get(struct queue_root *root);

#endif /* !PKT_QUEUE_H */
