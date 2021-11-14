#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// 2分木の初期化
void initialize(tree* t)
{
	if (t == NULL) return;

	t->root = NULL;
}

static void release_recursive(node* n)
{
	if (n == NULL) return;

	if (n->right) {
		release_recursive(n->right);
		n->right = NULL;
	}

	if (n->left) {
		release_recursive(n->left);
		n->left = NULL;
	}

	free(n);
}

// 使用メモリの全解放
void finalize(tree* t)
{
	if (t == NULL) return;

	release_recursive(t->root);
	t->root = NULL;
}


static node* generate(int key, const char* value)
{
	node* p = (node*)malloc(sizeof(node));

	if (p == NULL) return NULL;

	p->key = key;
	memcpy(p->value, value, (int)strlen(value) + 1);

	p->left = p->right = NULL;

	return p;
}

static bool insert( node* p, int key, const char* value)
{
	if (key < p->key) {
		if (p->left == NULL) {
			p->left = generate(key, value);
			return (p->left != NULL);
		}
		return insert(p->left, key, value);
	}
	else if (p->key < key) {
		if (p->right == NULL) {
			p->right = generate(key, value);
			return (p->right != NULL);
		}
		return insert(p->right, key, value);
	}

	strcpy_s(p->value, 256, value);
	return true;
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	if (t->root == NULL) {
		t->root = generate(key, value);
		return (t->root != NULL);
	}

	return insert(t->root, key, value);
}

static const char* find(const node* p, int key)
{
	if (p == NULL) return NULL;

	if (p->key == key) return p->value;

	if (key < p->key) {
		return find(p->left, key);
	}
	else {
		return find(p->right, key);
	}
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	if (t == NULL) return NULL;

	return find(t->root, key);
}

static void find(const node* p, void (*func)(const node* p))
{
	if (p == NULL) return;

	// 左側を実効
	if (p->left) {
		find(p->left, func);
	}

	// 自分自身を実効
	func(p);

	// 右側を実効
	if (p->right) {
		find(p->right, func);
	}
}


// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	if (t == NULL) return;

	find(t->root, func);
}