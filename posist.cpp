#include<bits/stdc++.h>
#include<iostream>
#include<string.h>

using namespace std;

 
struct Owner
{
	
        string add;
	int ownerNo;
	string mobile;
	string name;
	string pwd;
	float value;
	
	
};

struct Node
{
	int nodeId;
	time_t timestamp;
	Owner *owner;
	int nodeNumber;
	vector<int> childNodeId;
	Node *refernceNodeId;
	vector<Node*> refChildNodeId;
	
};

Node *getNode(int n,Owner *owner)
{
	Node *pointnode=new Node;
	pointnode->timestamp=time(0);
	pointnode->owner=owner;
	pointnode->nodeNumber=n;
	pointnode->nodeId=(n);
	vector<Node*> v;
	pointnode->refChildNodeId=v;
	pointnode->refernceNodeId=NULL;
	vector<int> s;
	pointnode->childNodeId=s;
	return pointnode;
}

void task3(Node *children,int iddata,vector<Node*> &vec)
{
	for(int i=0;i<vec.size();i++)
	{
		if(vec[i]->nodeId==iddata)
		{
			vec[i]->refChildNodeId.push_back(children);
			vec[i]->childNodeId.push_back(children->nodeId);
			children->refernceNodeId=v[i];
			break;
		}	
	}
}

/* Encryption of data is done here */

string encryption(string str,int n)
{
	string sol=str;
	for(int i=0;i<sol.length();i++)
	{
		sol[i]+=n+10;
	}
	return sol;
}

/*decryption of data is done here*/

string decryption(string data,int n)
{
	string sol=data;
	for(int i=0;i<sol.length();i++)
	{
		sol[i]-=n-10;
	}
	return sol;
}


Owner *getOwner(int n,string name, string add, string mobile, string phn, float num,string pass)
{
	
	Owner *own=new Owner;
	own->ownerNo=n;
	own->add=encryption(add,n);
	own->add=encryption(name,n);
	own->add=encryption(mobile,n);
	own->value=num;
	own->pwd=encryption(pass,n);
	return own;	
}
// verifying the owner
bool task4(vector<Owner*> &owners,Owner *currOwner,vector<Node*> &v)
{
	cout<<"Enter NodeId: ";
	int id;
	cin>>id;
	bool f=false;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]->nodeId==id)
		{
			if(currOwner==v[i]->owner)
			{
				f=true;
			}
			break;
		}	
	}
		
	return f;
}

void task5(vector<Owner*> &owners, Owner *currOwner, vector<Node*> &v){
	cout<<"Enter nodeId of node to be deleted: "<<endl;
	int id;
	cin>>id;
	bool f=false;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]->nodeId==id)
		{
			if(task4(owners,currOwner,v))
			{
				f=true;
				Node *parent=v[i]->refernceNodeId;
				vector<Node*> child=parent->refChildNodeId;
				for(int k=0;k<child.size();k++)
				{
					if(child[k]->nodeId==id)
					{
						child.erase(child.begin()+i);
						
						break;
					}
				}
				
			}
			else
			{
				cout<<"OOPS! You are not the owner of the node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<"Node is removed succesfullly"<<endl;
	}else{
		cout<<"Not found!"<<endl;
	}
}

// edting the value of particular node

void task6(vector<Owner*> &owners,Owner *currOwner, vector<Node*> &v)
{
	cout<<"Enter nodeId of node to be changed: "<<endl;
	int id,id2;
	cin>>id;
	cout<<"enter the value to be changed:"<<endl;
	cin>>id2;
	bool f=false;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]->nodeId==id)
		{
			if(task4(owners,currOwner,v))
			{
				f=true;
				Node *parent=v[i]->refernceNodeId;
				vector<Node*> child=parent->refChildNodeId;
				for(int k=0;k<child.size();k++)
				{
					if(child[k]->nodeId==id)
					{
						child[k]->nodeId=id2;
						
						break;
					}
				}
				
			}
			else
			{
				cout<<"OOPS! You are not the owner of the node"<<endl;
				return;
			}
			break;
		}
	}
	if(f)
	{
		cout<<"Node is changed successfully"<<endl;
	}
	else
	{
		cout<<"Not found!"<<endl;
	}
}

//transfer ownership of a particular node

void task7(vector<Node*> v)
{
	cout<<"Enter Node Id and user Id: "<<endl;
	int id,userId;
	cin>>id>>userId;
	bool f=false;
	for(int i=0;i<v.size();i++)
	{
		if(v[i]->nodeId==id)
		{
			if(task4(owners,currOwner,v))
			{				
				Node *np=v[i];
				for(int k=0;k<owners.size();k++)
				{
					if(owners[k]->ownerNo==userId)
					{
						np->owner=owners[k];
						f=true;
						break;
					}	
				}
				
			}
			else
			{
				cout<<"You are not the owner of this node"<<endl;
				return;
			}
			break;
		}
	}
	if(f){
		cout<<" Owner changed"<<endl;
	}else{
		cout<<"not found"<<endl;
	}
}

void dfs(Node *root,int &n,int num){
	if(root==NULL){
		n=max(n,num);
	}
	int count=num+1;
	vector<Node*> child=root->refChildNodeId;
	for(int i=0;i<child.size();i++){
		dfs(child[i],n,num+1);
	}
	n=max(n,count);
}

//merging of two nodes

void mergeSet(vector<Node*> &first, vector<Node*> &second,Owner *current){
	
       //merge sets of same owner
	
        int i=0,j=0;
	while(i<first.size() && j<second.size())
	{
		while(i<first.size() && first[i]->owner!=current)
		{
			i++;
		}
		while(j<second.size() && second[j]->owner!=current)
		{
			j++;
		}
		int n1=-1,n2=-1;
		dfs(second[j],n2,0);
		dfs(first[i],n1,0);
		if(n1>n2)
		{
			second[j]->refernceNodeId=first[i];
			first[i]->refChildNodeId.push_back(second[j]);
			second.erase(second.begin()+j);
			i++;
		}
		else
		{
			first[i]->refernceNodeId=second[j];
			second[j]->refChildNodeId.push_back(first[i]);
			second.erase(second.begin()+j);
			j++;
		}
	}
	
}
int main(){
	
St:
    int num=0,nOwners=0;
    vector<vector<Node*> > set;
    vector<Node*> v;
    vector<Owner*> owners;
    int q;

    Owner *currOwner;
    bool f=false;
    
    while(!f)
    {
    	cout<<"Enter 1 to login ";
    	cout<<"\nEnter 2 to signup"<<endl;
    	cin>>q;
    	if(q==1)
	{
			
		cout<<"Enter key and password";
	    	string pass;
	    	int p, q, r;
	    	int key;
	    	cin>>key;
	    	cin>>pass;
	    	
	    	for(int i=0;i<owners.size();i++)
		{
	    		if(owners[i]->ownerNo==key)
			{
	    			if(pass==decryption(owners[i]->pwd,owners[i]->ownerNo))
				{
	    				f=true;
	    				currOwner=owners[i];
	    				break;
				}
			}
		}
			cout<<"Unable to login"<<endl;
	}
	else
	{
		cout<<"Enter name, add, mobile value, password:"<<endl;
		string name,add,mobile,phone,pass;
		float value;
		cin>>name;
		cin>>add;
		cin>>mobile;
		cin>>value;
		cin>>pass;
		currOwner=getOwner(nOwners++,name, add, mobile, phone, value,pass);
		owners.push_back(currOwner);
		cout<<"Key=  "<<currOwner->ownerNo<<endl;
		f=true;
	}
    }
    
    
    while(1)
    {
    	cout<<"Enter the task you want to perform Query: ";
    	cout<<"1. Create Genesis Node";
    	cout<<"2. Create child nodes of particular node";
    	cout<<"3. create child node that originates from a particular node";
    	cout<<"4. Encryption and decryption";
    	cout<<"5. verify owner";
	cout<<"6. edit value of node";
    	cout<<"7. transfer ownership";
    	cout<<"8. longest chain of genesis code";
    	cout<<"9. longest chain of any code";
    	cout<<"10. Merging of nodes";
	cin>>q;
	if(q==1)
	{
		
		vector<Node*> v;
		v.push_back(getNode(num++,currOwner));
		set.push_back(v);
	}
	else if(q==2)
	{
	
		int n=0;
		cout<<"Enter number of nodes: ";
		cin>>n;
		vector<Node*> v(1);
		for(int i=0;i<n;i++)
		{
			v[0]=(getNode(num++,currOwner));	
			set.push_back(v);
		}
		cout<<"Pushing nodes... "<<endl;
	}
	else if(q==3)
	{
		//Create child nodes
		Node *np=getNode(num++,currOwner);
		v.push_back(np);
		cout<<"Enter number of set: ";
		int setNo;
		cin>>setNo;
		set[setNo].push_back(np);
		
	}
	else if(q==4)
	{
		//encryption and decryption:  
		string str,str1,str2;
		str=owners->add;
		int n=0;
		str1=encryption(str,n);
		str2=decryption(str1,n);
		
	
	}
	else if(q==5)
	{
		//Owner verification
		bool f=false;
		for(int i=0;i<set.size();i++)
		{
			f=task4(owners,currOwner,set[i]);
			if(f)
			{
				cout<<"You are the authorised owner!"<<endl;
			}		
		}
		if(!f)
		{			
			cout<<"You are NOT the authorised owner!"<<endl;
		}
	}
	else if(q==6)
	{
		//edit any node
		task6(owners,currOwner,v);
		
		
	}
	else if(q==7)
	{
		//tranfering ownership
		task7(v);
		
		
	}
	else if(q==8)
	{
		//longest chain
		int mx=-1;
		for(int i=0;i<set.size();i++)
		{
				
			dfs(set[i][0],mx,0);	
		}
		cout<<"max chain="<<mx<<endl;
	}
	else if(q==9)
	{
		//find longest chain of any node
		cout<<"enter node id"<<endl;
		int id;
		cin>>id;
		int ans=-1;
		bool f=false;
		for(int i=0;i<set.size();i++)
		{
			for(int j=0;j<set[i].size();j++)
			{
				if(set[i][j]->nodeId==id)
				{
					f=true;
					dfs(set[i][j],ans,0);
					break;
				}
			}
			if(f)
			{
				break;	
			}
		}
	}
	else if(q==10)
	{
		//merging two nodes
		cout<<"Enter set number 1 and 2"<<endl;
		int f,s;
		cin>>f>>s;
		mergeSet(set[f],set[s],currOwner);
		
	}
	else 
	{
		break;
	}
   }
    return 0;
}
