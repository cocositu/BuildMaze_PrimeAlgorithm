#include"UnionFindSet.h"

UnionFindSet::UnionFindSet(int size){
	this->size = size;
	this->set = new int[size];
	this->weight = new int[size];
	init();
}
UnionFindSet::~UnionFindSet() {
	delete[] this->set;
	delete[] this->weight;
}

void UnionFindSet::init(){
	this->count = this->size;
	for (int i = 0; i < size; i++) {
		this->set[i] = i;
		this->weight[i] = 1;
	}
}

int UnionFindSet::find(int id){
	while (this->set[id] != id)
		id = this->set[id];
	return id;
}

int UnionFindSet::quickFind(int id){
		int root = id;
		while (this->set[root] != root)
			root = this->set[root];
		//路径压缩，将沿路的结点直接连到根节点上
		while (this->set[id] != root) {
			int t = id;
			id = this->set[id];
			this->set[t] = root;
		}
		return root;
}

//合并两个集合，返回是否进行了合并操作
bool UnionFindSet::unionSet(int p, int q){
	int i = quickFind(p), j = quickFind(q);
	if (i == j)
		return false;
	this->count--;
	if (this->weight[i] < this->weight[j]) {
		this->set[i] = j;
		this->weight[j] += this->weight[i];
	}else {
		this->set[j] = i;
		this->weight[i] +=this-> weight[j];
	}
	return true;
}

//返回集合数
int UnionFindSet::setCount() const {
     return this->count; 
}

