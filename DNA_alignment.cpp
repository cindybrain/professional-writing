

////ʹ�ö�̬�滮�㷨
// 
//#include<iostream>
//#include<stdio.h>
//#include<stdlib.h>
//#include<string>
//#include<string.h>
//#include<math.h>
//#include<algorithm>
//using namespace std;
////�㷨3.12 ʹ�÷��η������ж�׼
//char x[12]={'A','A','C','A','G','T','T','A','C','C'};
//char y[10]={'T','A','A','G','G','T','C','A'};
//int m=0,n=0;
//int M[11][13]; 
//int opt(int i,int j)
//{
//    int penalty;
//    if(M[i][j]==-1){
//    	if(i==m)
//        return M[i][j]=2*(n-j);
//    else if(j==n)
//        return M[i][j]=2*(m-i);
//    else{
//        if(x[i]==y[j])
//            penalty=0;
//        else
//            penalty=1;
//        return M[i][j]=min(opt(i+1,j+1)+penalty,min(opt(i+1,j)+2,opt(i,j+1)+2));
//    }
//	} 
//	else{
//		return M[i][j];
//	}
//    
//}
//
//int main()
//{
//	//��ʼ��M 
//    m=strlen(x);
//    n=strlen(y);
//    cout<<m<<" "<<n<<endl;
//    int op=opt(0,0);
//    
//    cout<<op<<endl;
//}



#include <iostream>
#include <vector>
#include <string>
#include<time.h> 
#include<iomanip>
using namespace std;

const int costCopy=-1;
const int costReplace=1;
const int costDelete=2;
const int costInsert=2;
enum {cop=1,replace,del,insert};

void trackBack(vector < vector<int> > operMatrix,const string &s1,
     const string &s2){
     int len1=s1.size();
     int len2=s2.size();
     string seq1,seq2;
     int i=0;
     int j=0;
     while(i<=len1-1&&j<=len2-1){
         switch(operMatrix[i][j]){
           case 1://copy
           {
             seq1.insert(seq1.end(),s1[i]);
             seq2.insert(seq2.end(),s2[j]);
             i++;j++;
             break;
           }
           case 2://replace
           {
             seq1.insert(seq1.end(),s1[i]);
             seq2.insert(seq2.end(),s2[j]);
             i++;j++;
             break;
           }
           case 3://delete
           {
             seq1.insert(seq1.end(),s1[i]);
             seq2.insert(seq2.end(),'-');
             i++;
             break;
           }
           case 4://insert
           {
             seq1.insert(seq1.end(),'-');
             seq2.insert(seq2.end(),s2[j]);
             j++;
             break;
           }      
         }
     }
     if(i==len1){
       for(;j<len2;j++){ 
         seq1.insert(seq1.end(),'-');
         seq2.insert(seq2.end(),s2[j]);
       }
     }
     else{
       for(;i<len1;i++){
         seq1.insert(seq1.end(),s1[i]);
         seq2.insert(seq2.end(),'-'); 
       }
     }
     cout<<seq1.c_str()<<endl;
     cout<<seq2.c_str()<<endl;
}

int levenshteinDistance(const string &s1,const string &s2){
  int len1=s1.size();
  int len2=s2.size();
  if(!len1) return len2;
  if(!len2) return len1;
  
  vector <vector <int> > dp(len1+1,vector <int>(len2+1,0));
  //record the action
  vector <vector <int> > oper(len1+1,vector <int>(len2+1,0));

  //initialize dp
  //��ʼ���� 
  for(int i=len1-1;i>=0;i--){
    dp[i][len2]=dp[i+1][len2]+costDelete;
    oper[i][len2]=del;
  }
  //��ʼ���� 
  for(int j=len2-1;j>=0;j--){
    dp[len1][j]=dp[len1][j+1]+costInsert;
    oper[len1][j]=insert;
  }

  //dp
  for(int i=len1-1;i>=0;i--){
    for(int j=len2-1;j>=0;j--){
      int minDis=0;
      if(s1[i]==s2[j]){
        minDis=dp[i+1][j+1]+costCopy;
        oper[i][j]=cop;
      }
      else{
        minDis=dp[i+1][j+1]+costReplace;
        oper[i][j]=replace;
      }
      int tempDis=dp[i+1][j]+costDelete;
      if(minDis>tempDis){
        minDis=tempDis;
        oper[i][j]=del;
      }
      tempDis=dp[i][j+1]+costInsert;
      if(minDis>tempDis){
        minDis=tempDis;
        oper[i][j]=insert;
      }
      dp[i][j]=minDis;
    }
  }
//  cout<<"***************************"<<endl;
//  for(int i=0;i<=len1;i++){
//    for(int j=0;j<=len2;j++){
//      cout<<dp[i][j]<<" ";
//    }
//    cout<<endl;
//  }
//  cout<<"**************************"<<endl;
//  cout<<"***************************"<<endl;
//  for(int i=0;i<=len1;i++){
//    for(int j=0;j<=len2;j++){
//      cout<<oper[i][j]<<" ";
//    }
//    cout<<endl;
//  }
//  cout<<"**************************"<<endl;

  trackBack(oper,s1,s2);
  return dp[0][0];
}



int main(){
  string s1("AAAATATAAAAACTCAACACAACATACAAAATTTTATGCAATCAAATCAATCTCAAGCTATCAAAATTTTTCGAATCTCACTTGAAAGATCAAAAATCAACAAAGAAAATTCCTTAATTTCTTTACTAAATTTACTGCAA");
  string s2("TCGAATCTCACTTGAAAGATCAAAAATCAACAAAGAAAATTCCTTAATTTCTTTACTAAATTTACTGCAAAAAATATAAAAACTCAACACAACATACAAAATTTTATGCAATCAAATCAATCTCAAGCTATCAAAATTTT");
  clock_t startTime,endTime;
  startTime=clock();
  cout<<"�༭����:"<<levenshteinDistance(s1,s2)<<endl;
  endTime=clock();
  cout<<"Total Time : "<<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
  return 0;
}

