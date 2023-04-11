#ifndef _UNIONFINDSET_H_
#define _UNIONFINDSET_H_

//带权的路径压缩并查集
class UnionFindSet{
private:
	int* set;
	int* weight;
	int size;
	int count;
public:
	UnionFindSet(int size);	
	~UnionFindSet();	
    void init();	
	int find(int id);
	int quickFind(int id);
	bool unionSet(int p, int q);
	int setCount() const;
private:
	//禁止复制(重点在算法，减少其它方面的代码)
	UnionFindSet(const UnionFindSet& set);
	UnionFindSet& operator=(const UnionFindSet& set);
};
#endif //_UINONFINDSET_H_