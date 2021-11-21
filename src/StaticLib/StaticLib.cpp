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

	if (n->right != NULL) {
		release_recursive(n->right);
		n->right = NULL;
	}

	if (n->left != NULL) {
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
	// Todo: t->rootの下にkeyの値の大小でleftかrightを切り替えながらpを追加する処理を実装する
	node* q = t->root;

	while (q) {
		if (key == q->key) {
			strcpy_s(q->value, 256, p->value);
			free(p);
			p = NULL;
			break;
		}
		else if (key < q->key) {
			if (q->left == NULL) {
				q->left = p;
				break;
			}
			q = q->left;
		}
		else if (key > q->key) {
			if (q->right == NULL) {
				q->right = p;
				break;
			}
			q = q->right;
		}
		else return false;
	}
	return true;
}

// keyの値を見てノードを検索して、値を取得する
const char* find(const tree* t, int key)
{
	// ToDo: 実装する
	node* p;
	p = t->root;
	if (p == NULL) return NULL;

	while(p){
		if (key == p->key) {
			return p->value;
		}
		else if (key < p->key) {
			p = p->left;
		}
		else if (key > p->key) {
			p = p->right;
		}
		else break;
	}
	return NULL;
}


// keyの小さな順にコールバック関数funcを呼び出す
void search(const tree* t, void (*func)(const node* p))
{
	// ToDo: 実装する
	int i = 0;
	int flag = 0;

	do{
		node* p = t->root;
		if (p == NULL) return;
		flag = 0;
		while (p) 
		{
			if (i == p->key) break;
			else if (i < p->key) {
				p = p->left;
				flag = 1;
			}
			else if (i > p->key) p = p->right;
		}
		func(p);
		i++;
	} while (flag);
	return;
}