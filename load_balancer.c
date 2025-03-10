/* Copyright 2023 <> */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "load_balancer.h"

struct load_balancer {
	unsigned int *array;
	unsigned int *serverlabel;
	server_memory *servers;
	int num_servers;
	int labels;
};

unsigned int hash_function_servers(void *a) {
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

load_balancer *init_load_balancer() {
	load_balancer *mainload = malloc(sizeof(load_balancer));
	mainload->servers = malloc(sizeof(server_memory) * 100000);
	mainload->labels = 0;
	mainload->serverlabel = malloc(30000 * sizeof(unsigned int));
	mainload->num_servers = 0;
	mainload->array = malloc(10000 * sizeof(unsigned int));
	for (int i = 0; i < 100000; i++)
		mainload->servers[i].ht = NULL;
	return mainload;
}

void remove_number(unsigned int arr[], int *n, unsigned int num) {
	int i, j;
	for (i = 0, j = 0; i < *n; i++)
		if (arr[i] != num)
			arr[j++] = arr[i];
	(*n)--;
}

void insert(unsigned int arr, int number,
			unsigned int new, unsigned int *serv, int label) {
	if (*number == 0) {
		arr[0] = new;
		serv[0] = label;
		*number = 1;
		return;
	}
	int i;
	for (i = *number - 1; i >= 0; i--) {
		if (arr[i] > new) {
			arr[i + 1] = arr[i];
			serv[i + 1] = serv[i];
		} else {
			arr[i + 1] = new;
			serv[i + 1] = label;
			break;
		}
	}
	if (i == -1) {
		arr[0] = new;
		serv[0] = label;
	}
	(*number)++;
}

int cautare(unsigned int *vector, int lungime, unsigned int numar_cautat) {
	int pozitie = -1;
	for (int i = 0; i < lungime; i++) {
		if (vector[i] == numar_cautat) {
			pozitie = i;
			break;
		}
	}
	return pozitie;
}

void loader_add_server(load_balancer *main, int server_id) {
	main->num_servers++;
	main->servers[server_id].ht = ht_create(10, hash_function_key,
											compare_function_strings);
	main->servers[server_id].id = server_id;
	if (main->num_servers == 1) {
		for (int i = 0; i < 3; ++i) {
			int label = i * 100000 + server_id;
			unsigned int uf = hash_function_servers(&label);
			insert(main->array, &main->labels,
				   uf, main->serverlabel, label);
		}
	} else {
		int x;
		if (hash_function_servers(&server_id) > main->array[main->labels - 1]) {
			x = 0;
		} else {
			for (x = 0; x < main->labels; ++x) {
				if (main->array[x] > hash_function_servers(&server_id))
					break;
			}
		}
		int label1 = main->serverlabel[x];
		if (label1 > 99999) {
			if (label1 < 200000)
				label1 = label1 - 100000;
			else
				label1 = label1 - 200000;
		}
		for (unsigned int i = 0; i < main->servers[label1].ht->hmax; ++i) {
			if (main->servers[label1].ht->buckets[i]->head != NULL) {
				ll_node_t *node = main->servers[label1].ht->buckets[i]->head;
				while (node != NULL) {
					char *key = (char *)(((info *)node->data)->key);
					char *value = (char *)(((info *)node->data)->value);
					if (hash_function_key(key) < hash_function_servers(&server_id))
						ht_put(main->servers[server_id].ht, key, value);
					node = node->next;
				}
			}
		}
		int server = server_id + 100000;
		if (hash_function_servers(&server) > main->array[main->labels - 1]) {
			x = 0;
		} else {
			for (x = 0; x < main->labels; ++x) {
				if (main->array[x] > hash_function_servers(&server))
					break;
			}
		}
		int label2 = main->serverlabel[x];
		if (label2 > 99999) {
			if (label2 < 200000)
				label2 = label2 - 100000;
			else
				label2 = label2 - 200000;
		}
		for (unsigned int i = 0; i < main->servers[label2].ht->hmax; ++i) {
			if (main->servers[label2].ht->buckets[i]->head != NULL) {
				ll_node_t *node = main->servers[label2].ht->buckets[i]->head;
				while (node != NULL) {
					char *key = (char *)(((info *)node->data)->key);
					char *value = (char *)(((info *)node->data)->value);
					if (hash_function_key(key) < hash_function_servers(&server))
						ht_put(main->servers[server_id].ht, key, value);
					node = node->next;
				}
			}
		}
		server = server_id + 200000;
		if (hash_function_servers(&server) > main->array[main->labels - 1]) {
			x = 0;
		} else {
			for (x = 0; x < main->labels; ++x) {
				if (main->array[x] > hash_function_servers(&server))
					break;
			}
		}
		int label3 = main->serverlabel[x];
		if (label3 > 99999) {
			if (label3 < 200000)
				label3 = label3 - 100000;
			else
				label3 = label3 - 200000;
		}
		for (unsigned int i = 0; i < main->servers[label3].ht->hmax; ++i) {
			if (main->servers[label3].ht->buckets[i]->head != NULL) {
				ll_node_t *node = main->servers[label3].ht->buckets[i]->head;
				while (node != NULL) {
					char *key = (char *)(((info *)node->data)->key);
					char *value = (char *)(((info *)node->data)->value);
					if (hash_function_key(key) < hash_function_servers(&server))
						ht_put(main->servers[server_id].ht, key, value);
			   		node = node->next;
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			int label = i * 100000 + server_id;
			unsigned int uf = hash_function_servers(&label);
			insert(main->array, &main->labels, uf, main->serverlabel, label);
		}
	}
}

void loader_remove_server(load_balancer *main, int server_id) {
	for (int s = 0; s < 3; ++s) {
		unsigned int label = s * 100000 + server_id;
		remove_number(main->array, &main->labels, hash_function_servers(&label));
		main->labels++;
		remove_number(main->serverlabel, &main->labels, label);
	}
	main->num_servers--;
	for (unsigned int i = 0; i < main->servers[server_id].ht->hmax; ++i) {
		if (main->servers[server_id].ht->buckets[i]->head != NULL) {
			ll_node_t *node = main->servers[server_id].ht->buckets[i]->head;
			while (node != NULL) {
				int server = 0;
				char *key = (char *)(((info *)node->data)->key);
				char *value = (char *)(((info *)node->data)->value);
				loader_store(main, key, value, &server);
				node = node->next;
			}
		}
	}
}

void loader_store(load_balancer *main, char *key, char *value, int *server_id) {
	int i = 0;
	if (main->array[main->labels - 1] < hash_function_key(key))
		i = 0;
	else
		while (main->array[i] < hash_function_key(key))
			i++;
	unsigned int server = main->serverlabel[i];
	if (server > 99999) {
		if (server < 200000)
			server = server - 100000;
		else
			server = server - 200000;
	}
	*server_id = server;
	ht_put(main->servers[*server_id].ht, key, value);
}

char *loader_retrieve(load_balancer *main, char *key, int *server_id) {
	int i = 0;
	void *value;
	if (main->array[main->labels - 1] < hash_function_key(key))
		i = 0;
	else
		while (main->array[i] < hash_function_key(key))
			i++;
	unsigned int server = main->serverlabel[i];
	if (server > 99999) {
		if (server < 200000)
			server = server - 100000;
		else
			server = server - 200000;
	}
	*server_id = server;
	value = ht_get(main->servers[*server_id].ht, key);
	return value;
}

// functia de eliberare a resurselor
void free_load_balancer(load_balancer *main) {
	// eliberez toate hashtable-urile din servere
	for (int i = 0; i < 100000; i++) {
		if (main->servers[i].ht)
			ht_free(main->servers[i].ht);
	}
	// eliberez vectorii utilizati
	free(main->serverlabel);
	free(main->servers);
	free(main->array);
	// eliberez load balancer-ul
	free(main);
}