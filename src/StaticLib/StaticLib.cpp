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
	memcpy(p->value, value, strlen(value)+1);

	p->left = p->right = NULL;

	return p;
}

// keyの値を見てノードを追加する
bool add(tree* t, int key, const char* value)
{
	if (t == NULL) return false;

	node* p = generate(key, value);
	if (p == NULL) return false;// メモリ確保できなかった。

	if (t->root == NULL) {
		t->root = p;
		return true;
	}

	node* a = t->root;

	while (a)
	{
		if (a->key == p->key)
		{
			memcpy(a->value, p->value, sizeof(char) * 256);
			free(p);
			return true;
		}

		else if (a->key > p->key)
		{
			if (a->left == NULL)
			{
				a->left = p;
				return true;
			}

			a = a->left;
		}

		else if (a->key < p->key)
		{
			if (a->right == NULL)
			{
				a->right = p;
				return true;
			}

			a = a->right;
		}
	}
	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する

	return true;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	if (t->root == NULL)  return NULL;

	node* a = t->root;

	while (a)
	{
		if (a == NULL)  return NULL;

		else
		{
			if (a->key == key)
			{
				return (a->value);
			}

			else if (a->key > key)
			{
				a = a->left;
			}

			else if (a->key < key)
			{
				a = a->right;
			}
		}
	}
	// ToDo: 実装する
	return NULL;
}

// keyの小さな順にコールバック関数funcを呼び出す
void find(node* a, void (*func)(const node* p))
{
	if (a->left)
	{
		find(a->left, func);
	}
	func(a);
	if (a->right)
	{
		find(a->right, func);
	}


	// ToDo: 実装する
}
void search(const tree* t, void (*func)(const node* p))
{
	find(t->root, func);
	// ToDo: 実装する
}