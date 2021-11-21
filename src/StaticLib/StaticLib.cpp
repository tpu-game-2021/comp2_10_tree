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

bool myadd(node* p, int key, const char* value)
{
	//チェック
	if (p == NULL || key == NULL || value)return false;
	
	//同値
	if (p->key == key)
	{
		memcpy(p->value, value, sizeof(char) * 256);
		free(p);
		return true;
	}

	//Left再帰
	if (key < p->key && p->left == NULL)
	{
		p->left = generate(key, value);
		return (p->left != NULL);
	}
	if (key < p->key && p->left != NULL)
	{
		return myadd(p->left, key, value);
	}
	
	//Rigth再帰
	if (key > p->key && p->right == NULL)
	{
		p->right = generate(key, value);
		return (p->right != NULL);
	}
	if (key > p->key && p->right != NULL)
	{
		return myadd(p->right, key, value);
	}
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

	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	return myadd(t->root, key, value);
}

node* myfind(node* p, int key)
{
	if (key < p->key && p->left != NULL)
	{
		p->left = myfind(p->left, key);
	}
	if (key < p->key && p->left == NULL)
	{
		return NULL;
	}

	if (key > p->key && p->right != NULL)
	{
		p->left = myfind(p->right, key);
	}
	if (key < p->key && p->right == NULL)
	{
		return NULL;
	}

	return p;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	if (t == NULL || key == NULL || t->root == NULL)return NULL;

	if (myfind(t->root, key) == NULL)return NULL;
	if (myfind(t->root, key) != NULL)
	{
		return myfind(t->root, key)->value;
	}
}

void mysearch(node* n, void (*func)(const node* p))
{
	if (n->left)
	{
		mysearch(n->left, func);
	}
	func(n);
	if (n->right)
	{
		mysearch(n->left, func);
	}
}
// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	if (t == NULL)return;

	mysearch(t->root, func);
}