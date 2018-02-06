#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<iterator>
#include <windows.h>
#include <utility>
#include<bits/stdc++.h>
#include<conio.h>

using namespace std;

vector<pair<string,vector<int>>>inv_ind;
vector<pair<string,vector<pair<int,vector<int>>>>> pos_ind;
vector<pair<string,string>> ii_docs;
vector<pair<string,string>> pi_docs;
vector<int>alldocs;

vector<string> ii_posts;
int ii_index=0;
	
void create_ii(string file, vector<string> vec){
	string str,docid;
	ifstream fin1;
	//ofstream fout2;
	vector<string> tokens;
	
	//fout2.open("ii_docid.txt", ios_base::app);	
	fin1.open(file);
	while(!fin1.eof()){
		getline(fin1,str);
		if(str[0]!='['){ //distiguish string 
			ii_docs.insert(ii_docs.begin()+ii_index-1,make_pair(docid,str));
			str.resize(remove_if(str.begin(), str.end(),[](char x){return !isalnum(x) && !isspace(x);})-str.begin());
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			istringstream iss(str);
			copy(istream_iterator<string>(iss),
     		istream_iterator<string>(),
     		back_inserter(tokens));
		}
		else{ //distinguish doc id
			str.erase(remove(str.begin(), str.end(), '['), str.end());
			str.erase(remove(str.begin(), str.end(), ']'), str.end());
			docid=str;
			ii_index++;
			alldocs.push_back(ii_index);
			//fout2<<ii_index<<"=="<<docid<<"\n";
		}
		for(string i : tokens)
		{
			if (!(find(vec.begin(), vec.end(), i) != vec.end()))
			ii_posts.push_back(i+" "+to_string(ii_index));
		}
		tokens.clear();		
	}
	fin1.close();
}

void write_ii(){
	string doc,term;
	vector<string> termdoc;
	vector<int> docsort;
	ofstream fout1;
	fout1.open("inverted_index_dictionary.txt");
	
	sort(ii_posts.begin(), ii_posts.end());
	for(string i : ii_posts)
	{
		istringstream iss(i);
		copy(istream_iterator<string>(iss),
  		istream_iterator<string>(),
   		back_inserter(termdoc));
   		if(term!=termdoc[0])
   		{
   			if(!docsort.empty()){
				sort(docsort.begin(),docsort.end());
				docsort.erase( unique( docsort.begin(), docsort.end() ), docsort.end() );
				//fout1<<" | "<<docsort.size()<<" < ";
				fout1<<"   < ";
				inv_ind.push_back(make_pair(term,docsort));
				for(int i: docsort)
				fout1<<i<<" ";
				fout1<<">\n";
			}
			docsort.clear();
	   		term=termdoc[0];
			fout1<<term;   			
		}
   		doc=termdoc[1];
   		docsort.push_back(stoi(doc));
		termdoc.clear();
	}
	if(!docsort.empty()){
		sort(docsort.begin(),docsort.end());
		docsort.erase( unique( docsort.begin(), docsort.end() ), docsort.end() );
		//fout1<<" | "<<docsort.size()<<" < ";
		fout1<<"   < ";
		inv_ind.push_back(make_pair(term,docsort));
		for(int i: docsort)
		fout1<<i<<" ";
		fout1<<">\n";
	}

}

vector<string> pi_posts;
int pi_index=0;

void create_pi(string file, vector<string> vec){
	int posi=1;
	string str,docid;
	ifstream fin1;
	//ofstream fout2;
	vector<string> tokens;
	
	//fout2.open("pi_docid.txt", ios_base::app);
	fin1.open(file);        	
	while(!fin1.eof()){
		getline(fin1,str);				
		if(str[0]!='['){ //distiguish string 
			pi_docs.insert(pi_docs.begin()+pi_index-1,make_pair(docid,str));
			str.resize(remove_if(str.begin(), str.end(),[](char x){return !isalnum(x) && !isspace(x);})-str.begin());
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			istringstream iss(str);
			copy(istream_iterator<string>(iss),
     		istream_iterator<string>(),
     		back_inserter(tokens));
		}
		else{ //distinguish doc id
			str.erase(remove(str.begin(), str.end(), '['), str.end());
			str.erase(remove(str.begin(), str.end(), ']'), str.end());
			docid=str;
			pi_index++;
			//fout2<<pi_index<<"=="<<docid<<"\n";
			posi=1;
		}
		for(string i : tokens)
		{
			if (!(find(vec.begin(), vec.end(), i) != vec.end()))
			pi_posts.push_back(i+" "+to_string(pi_index)+" "+to_string(posi));
			posi++;
		}
		tokens.clear();
	}
	fin1.close();	
}

void write_pi(){
	string doc,term,pos;
	vector<string> termdoc;
	vector<pair<int,vector<int>>> docsort;
	vector<int> temppos;
	ofstream fout1;
	fout1.open("positional_index_dictionary.txt");
	
	sort(pi_posts.begin(), pi_posts.end());
	for(string i : pi_posts)
	{
		istringstream iss(i);
		copy(istream_iterator<string>(iss),
  		istream_iterator<string>(),
   		back_inserter(termdoc));
   		if(term!=termdoc[0])
   		{
   			if(!temppos.empty()){
				sort(temppos.begin(),temppos.end());
				docsort.push_back(make_pair(stoi(doc),temppos));
			}
			temppos.clear();
   			if(!docsort.empty()){
				sort(docsort.begin(),docsort.end());
				//fout1<<" | "<<docsort.size()<<"\n<";
				fout1<<"\n<";
				pos_ind.push_back(make_pair(term,docsort));
				for(int i=0;i<docsort.size();i++){
					//fout1<<"\t"<<docsort[i].first<<" | "<<(docsort[i].second).size()<<", ";//<<docsort[i].second<<"\n";
					fout1<<"\t"<<docsort[i].first<<", ";
					for(int j:docsort[i].second)
					fout1<<j<<" ";
					fout1<<"\n";
				}
				fout1<<">\n";
			}
			docsort.clear();
	   		term=termdoc[0];
			fout1<<term;   			
		}
		if(doc!=termdoc[1]){
			if(!temppos.empty()){
				sort(temppos.begin(),temppos.end());
				docsort.push_back(make_pair(stoi(doc),temppos));			
			}
			temppos.clear();
			doc=termdoc[1];
		}
   		pos=termdoc[2];
   		temppos.push_back(stoi(pos));
		termdoc.clear();
	}
	if(!temppos.empty()){
		sort(temppos.begin(),temppos.end());
		docsort.push_back(make_pair(stoi(doc),temppos));
	}
	temppos.clear();
	if(!docsort.empty()){
		sort(docsort.begin(),docsort.end());
		//fout1<<" | "<<docsort.size()<<"\n<";
		fout1<<"\n<";
		pos_ind.push_back(make_pair(term,docsort));
		for(int i=0;i<docsort.size();i++){
			//fout1<<"\t"<<docsort[i].first<<" | "<<(docsort[i].second).size()<<", ";//<<docsort[i].second<<"\n";
			fout1<<"\t"<<docsort[i].first<<", ";
			for(int j:docsort[i].second)
			fout1<<j<<" ";
			fout1<<"\n";
		}
		fout1<<">\n";
	}
}

void querysearch(string query){
	deque<vector<int>> terms;
	vector<int>t1;
	bool proxim=false;
	bool proxim1=false;
	int termcount=0;
	vector<string> qtokens;
	vector<string> qterms;
	vector<vector<int>> qtdocs;
	istringstream iss(query);
	copy(istream_iterator<string>(iss),
	istream_iterator<string>(),
	back_inserter(qtokens));
	if (qtokens[0]=="AND"||qtokens[0]=="OR"||qtokens[qtokens.size()-1]=="AND"||qtokens[qtokens.size()-1]=="OR"||qtokens[qtokens.size()-1]=="NOT")
		cout<<"invalid query";
	for(int i=1;i<qtokens.size()-1;i++){
		//cout<<qtokens[i]<<endl;
		if(qtokens[i]=="NOT"&&(qtokens[i-1]!="AND"&&qtokens[i-1]!="OR"&&qtokens[i-1]!="NOT")){
			cout<<"invalid query"; break;
		}
		if(qtokens[i]=="NOT"&&(qtokens[i-1]=="NOT"||qtokens[i+1]=="NOT")){
			cout<<"invalid query"; break;
		}
		if(qtokens[i]=="NOT"&&(qtokens[i+1]=="AND"||qtokens[i+1]=="OR")){
				cout<<"invalid query"; break;
		}
		if((qtokens[i]=="AND"||qtokens[i]=="OR")&&qtokens[i-1]=="NOT"){
				cout<<"invalid query"; break;
		}
		if((qtokens[i]=="AND"||qtokens[i]=="OR")&&(qtokens[i-1]=="AND"||qtokens[i-1]=="OR")){
				cout<<"invalid query"; break;
		}
		if((qtokens[i]=="AND"||qtokens[i]=="OR")&&(qtokens[i+1]=="AND"||qtokens[i+1]=="OR")){
				cout<<"invalid query"; break;
		}
	}
	int count=0;
	for(string i: qtokens){
		if(i!="AND"&&i!="OR"&&i!="NOT"&&i.substr(0,1)!="/"){
			qterms.push_back(i);
		}
		if(i.substr(0,1)=="/"){
		proxim=true;
		if(count>0)proxim1=true;
		count++;
		}
	}
	sort(qterms.begin(),qterms.end());
	int qi=0;
	for(pair<string,vector<int>> j: inv_ind){
		if(qterms[qi]==j.first){
			qtdocs.push_back(j.second);
			qi++;
			if(qi>=qterms.size())break;
		}
	}

	for(int k=0;k<qtokens.size();k++){
		if(qtokens[k]!="AND"&&qtokens[k]!="OR"&&qtokens[k]!="NOT"&&qtokens[k].substr(0,1)!="/")
		{
			ptrdiff_t tsrch = find(qterms.begin(), qterms.end(), qtokens[k]) - qterms.begin();
			terms.push_back(qtdocs[tsrch]);
		}
		if(qtokens[k]=="NOT"){
			k++;
			ptrdiff_t tsrch = find(qterms.begin(), qterms.end(), qtokens[k]) - qterms.begin();
			set_difference(alldocs.begin(),alldocs.end(),qtdocs[tsrch].begin(),qtdocs[tsrch].end(),inserter(t1, t1.begin()));
			terms.push_back(t1);
		}
	}

	vector<int> temp1;
	vector<int> temp2;
	vector<int> tempres;
	vector<vector<int>> t1p;
	vector<vector<int>> t2p;
	int proxcount=0;
	
	
	for(int k=0;k<qtokens.size();k++){
		vector<int> vec1;
		vector<int> vec2;
		vector<int> ftemp;
		if(qtokens[k]=="AND" &&  proxim1==true){
			temp1=terms.front();
			terms.pop_front();
			temp2=terms.front();
			set_intersection(temp1.begin(),temp1.end(),temp2.begin(),temp2.end(),inserter(tempres, tempres.begin()));
		
			if(qtokens[k+2].substr(0,1)=="/"){
				int prox=stoi(qtokens[k+2].substr(1,1));
				string ttt;
				if(proxcount==0)ttt=qtokens[k-1];else ttt=qtokens[k-2] ;
				auto it=find_if(pos_ind.begin(),pos_ind.end(),[&ttt](const pair<string,vector<pair<int,vector<int>>>>& element){ return element.first == ttt;});
				string ttt1=qtokens[k+1];
				auto it1=find_if(pos_ind.begin(),pos_ind.end(),[&ttt1](const pair<string,vector<pair<int,vector<int>>>>& element){ return element.first == ttt1;});
				for(int j: tempres){
					auto it2=find_if(((*it).second).begin(),((*it).second).end(),[&j](const pair<int,vector<int>>& element1){ return element1.first == j;});
					t1p.push_back((*it2).second);
					auto it3=find_if(((*it1).second).begin(),((*it1).second).end(),[&j](const pair<int,vector<int>>& element2){ return element2.first == j;});
					t2p.push_back((*it3).second);
				}
				for(int l=0;l<t1p.size();l++){
					for(int m:t1p[l]){
						for(int n:t2p[l]){
							if(n>=m&&n<=(m+prox+1))
								goto mout;	
						}
					}
					tempres[l]=0;
					mout:;
				}
			tempres.erase(remove(tempres.begin(), tempres.end(),0), tempres.end());
			proxcount++;
			}
			if(proxcount==1)	
				vec1=tempres;
			else{
				vec2=tempres;
				set_intersection(vec1.begin(),vec1.end(),vec2.begin(),vec2.end(),inserter(ftemp, ftemp.begin()));
				terms.pop_back();
				terms.push_front(ftemp);
			}
			tempres.clear();			
		}
		
		if(qtokens[k]=="AND" && proxim1!=true){
			temp1=terms.front();
			terms.pop_front();
			temp2=terms.front();
			terms.pop_front();
			set_intersection(temp1.begin(),temp1.end(),temp2.begin(),temp2.end(),inserter(tempres, tempres.begin()));
			if(proxim==true){
			if(qtokens[k+2].substr(0,1)=="/"){
				int prox=stoi(qtokens[k+2].substr(1,1));
				string ttt;
				if(proxcount==0)ttt=qtokens[k-1];else ttt=qtokens[k-2] ;
				auto it=find_if(pos_ind.begin(),pos_ind.end(),[&ttt](const pair<string,vector<pair<int,vector<int>>>>& element){ return element.first == ttt;});
				string ttt1=qtokens[k+1];
				auto it1=find_if(pos_ind.begin(),pos_ind.end(),[&ttt1](const pair<string,vector<pair<int,vector<int>>>>& element){ return element.first == ttt1;});
				for(int j: tempres){
					auto it2=find_if(((*it).second).begin(),((*it).second).end(),[&j](const pair<int,vector<int>>& element1){ return element1.first == j;});
					t1p.push_back((*it2).second);
					auto it3=find_if(((*it1).second).begin(),((*it1).second).end(),[&j](const pair<int,vector<int>>& element2){ return element2.first == j;});
					t2p.push_back((*it3).second);
				}
				for(int l=0;l<t1p.size();l++){
					for(int m:t1p[l]){
						for(int n:t2p[l]){
							if(n>=m&&n<=(m+prox+1))
								goto nout;	
						}
					}
					tempres[l]=0;
					nout:;
				}
			tempres.erase(remove(tempres.begin(), tempres.end(),0), tempres.end());
			proxcount++;
			}
			proxim=false;
			}
			
			terms.push_front(tempres);
			tempres.clear();
		}
		
		if(qtokens[k]=="OR"){
			temp1=terms.front();
			terms.pop_front();
			temp2=terms.front();
			terms.pop_front();
			set_union(temp1.begin(),temp1.end(),temp2.begin(),temp2.end(),inserter(tempres, tempres.begin()));
			terms.push_front(tempres);
			tempres.clear();
		}
	}
	for(vector<int> i: terms){
		cout<<"Documents Retrieved: "<<i.size()<<endl<<"Document IDs: ";
		for(int j: i){
			cout<<ii_docs[j-1].first<<" ";
		}
		cout<<endl;
		cout<<"------------------------------"<<endl;
	}
	cout<<"Press 'v' to view documents. (Press any button to continue)"<<endl;
	char inp=getch();
	if(inp=='v'){
	for(vector<int> i: terms){
		for(int j: i){
			cout<<"["<<ii_docs[j-1].first<<"] :\t"<<setw(2)<<ii_docs[j-1].second<<endl;
		}
	}	
	}
	cout<<"------------------------------"<<endl<<endl;
}

int main(){
	int filecount=1;
	string str1;
	ifstream fin2,fin3;
	vector<string> vec;
	string rfile="Quran Translation.txt";

	cout<<"BOOLEAN RETRIEVAL MODEL"<<endl<<endl;
	cout<<"Please Wait. Loading..."<<endl<<endl;
	fin2.open("dataset\\Stopword-List.txt");
	fin3.open("dataset\\QueryList.txt");
	while(!fin2.eof()){ //read stop words
		fin2>>str1;
		vec.push_back(str1);
	}
	
	for(int i=0;i<16;i++){
		create_ii("dataset\\"+rfile,vec);
		create_pi("dataset\\"+rfile,vec);
		rfile=to_string(filecount);
		filecount++;
	}
	write_ii();
	cout<<"Inverted Index Constructed"<<endl;
	write_pi();
	cout<<"Positional Index Constructed"<<endl<<endl;
	
	string query;
	while(getline(fin3,query)){
		cout<<query<<endl;
		querysearch(query);
	}
	while(true){
	cout<<"Type Your Query(# to exit)"<<endl<<endl;
	getline(cin,query);
		if(query=="#")break;
	querysearch(query);
	}
	
	return 0;
	
}
