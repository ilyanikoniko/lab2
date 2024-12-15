using namespace std;
#include <iostream>
#include <vector>

struct stats { 
    size_t comparison_count = 0; 
    size_t copy_count = 0; 
};

stats sort_insert(vector<int>& a)
{
    stats result;
    for(int i=1; i<a.size(); i++)
    {   
        result.comparison_count++;
        for(int j=i; j>0 && a[j-1]>a[j]; j--)
        {
            result.comparison_count += 2;  
            int tmp=a[j-1];
			a[j-1]=a[j];
			a[j]=tmp;
            result.copy_count += 3;
        }
    }
    return result;
}

ostream& operator<<(ostream& stream, const stats& s) {
    stream << "Количество сравнений: " << s.comparison_count << ", Количество копирований: " << s.copy_count;
    return stream;
}

ostream& operator<<(ostream& stream, const vector<int>& v)
{
    stream<< "(";
    for (size_t i = 0; i < v.size() - 1; ++i) 
    {
        cout << v[i] << ",";  
    }
    cout<<v[v.size()-1];
    cout<<")";
    return stream;
}

int main()
{
    vector<int> arr = {6,4,2,8,9};
    cout<<arr<<endl;
    stats result = sort_insert(arr);
    cout<<arr<<endl;
    return 0;
}