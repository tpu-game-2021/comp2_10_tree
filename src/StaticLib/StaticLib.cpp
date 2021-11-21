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

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	node* NODE = (node*)malloc(sizeof(node));
	if (NODE == NULL) return false;// メモリ確保できなかった。

	if (t->root == NULL) {
		t->root = NODE;
		return true;
	}
	
	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	while (NODE)
	{
		NODE = t->root;
		if (key == NODE->key) {
			memcpy(NODE->value, value, sizeof(char) * 256);
			free(NODE);
			return true;
		}
		else if (key < NODE->key) {
			if (NODE->left == NULL) {
				NODE->left = NODE;
				return true;
			}
			NODE = NODE->left;
		}
		else {
			if (NODE->right == NULL) {
				NODE->right = NODE;
				return true;
			}
			NODE = NODE->right;
		}
	}
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	//////// ToDo: 実装する
	if (t == NULL) return NULL;
	node* NODE = t->root;
	
	while (NODE)
	{
		if (NODE == NULL) return NULL;
		if (key < NODE->key) NODE = NODE->left;
		else if (key > NODE->key) NODE = NODE->right;
		else return (NODE->value);
	}
	//return NULL;
}

// keyの小さな順にコールバック関数funcを呼び出す
void search_find(node* NODE, void (*func)(const node* p))
{
	if(NODE->left)	search_find(NODE->left, func);
	func(NODE);
	if(NODE->right)	search_find(NODE->right, func);
}

void search(const tree* t, void (*func)(const node* p))
{
	search_find(t->root, func);
}