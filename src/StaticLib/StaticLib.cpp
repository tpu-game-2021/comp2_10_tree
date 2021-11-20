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
	int n = (int)strlen(value);
	memcpy(p->value, value, strlen(value) + 1);

	p->left = p->right = NULL;

	return p;
}

static bool addnode(int key, const char* value, node* p)
{
	if (p == NULL) return false;

	if (key < p->key) {
		if (p->left == NULL) {
			p->left = generate(key, value);
			return (p->left != NULL);
		}
		return addnode(key, value, p->left);
	}
	else if (key > p->key) {
		if (p->right == NULL) {
			p->right = generate(key, value);
			return (p->right != NULL);
		}
		return addnode(key, value, p->right);
	}
	else {
		memcpy(p->value, value, sizeof(char) * 256);
		return true;
	}
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	if (t->root == NULL) {
		t->root = generate(key, value);
		return  (t->root != NULL);// メモリ確保できたかどうか
	}

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	return addnode(key, value, t->root);
}

static node* findnode(node* p, int key)
{

	if (key >= p->key) {
		if (p->right == NULL)return NULL;
		p->right = findnode(p->right, key);
	}
	else {
		if (p->left == NULL)return NULL;
		p->left = findnode(p->left, key);
	}
	return p;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	if (t == NULL || key == NULL)return NULL;
	if (t->root == NULL)return NULL;

	if (findnode(t->root, key)->value != NULL)
		return findnode(t->root, key)->value;
	else return NULL;
}

void searchkey(node* n, void (*func)(const node* p))
{
	if (n->left) {
		searchkey(n->left, func);
	}
	func(n);
	if (n->right) {
		searchkey(n->right, func);
	}
}
// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	if (t == NULL)return;
	searchkey(t->root, func);
}