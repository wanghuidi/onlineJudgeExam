#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge {
	int start;
	int end;
	int cost;
	int built;
};

int parents[101];

int findRoot(int i) {
	if(parents[i]!=-1)
		return findRoot(parents[i]);
	else
		return i;
}

void mergeSet(int a1,int a2,int num) {
	int from_root,to_root;
	if(a1<a2) {
		from_root=findRoot(a2);
		to_root=findRoot(a1);
	} else {
		from_root=findRoot(a1);
		to_root=findRoot(a2);
	}

	for(int i=1; i<=num; i++) {
		int from=findRoot(i);
		if(from==from_root) {
			parents[i]=to_root;
		}
	}
}

bool cmp(Edge a,Edge b) {
	if(a.built>b.built){
		return true;
	}else if(a.built==b.built){
		return a.cost<b.cost;
	}else{
		return false;
	}
}

int setNum(int num) {
	int n=0;
	for(int i=1; i<=num; i++) {
		if(parents[i]==-1)n++;
	}

	return n;
}



int main() {
	int n,m;
	//n 道路数，m 村庄数 
	while(cin>>m&&m!=0) {
		for(int i=1; i<=m; i++) {
			parents[i]=-1;
		}
		
		vector<Edge> edges;
		int n=m*(m-1)/2;
		for(int i=0;i<n;i++){
			Edge edge;
			cin>>edge.start>>edge.end>>edge.cost>>edge.built;
			edges.push_back(edge);
		}
		
		sort(edges.begin(),edges.end(),cmp);
		
		int sum=0;
		for(int i=0;i<edges.size();i++){
			if(setNum(m)==1){
				break;
			}
			
			Edge edge=edges[i];
			if(findRoot(edge.start)!=findRoot(edge.end)){
				if(edge.built==0){
					sum+=edge.cost;
				}
				mergeSet(edge.start,edge.end,m);
			}
		}
		
		cout<<sum<<endl;
	}
	return 0;
}
