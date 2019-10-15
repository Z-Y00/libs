#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <iterator>

//never use for bool! for raw vector only!!!
template <typename T>
inline void  _dump_vector(const std::string fileName,const std::vector<T>& v){
    std::ofstream d(fileName, std::ios::out | std::ios::binary);
    d.write((char*)&v[0], v.size() * sizeof(T));
    d.close();
}

//https://stackoverflow.com/questions/15138353/how-to-read-a-binary-file-into-a-vector-of-unsigned-chars

template <typename T>
inline std::vector<T> _load_vector(const std::string filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<T> v(fileSize);
    file.read((char*) &v[0], fileSize);
    return v;
}

//test of this 

// int main(){
//     std::vector<int> f(20);
//     f[0]=1;f[2]=2;f[1]=1;f[3]=9;
//     std::string t("./test");
//     _dump_vector<int>(t,f);
//     auto k = _load_vector<int>(t); 
//     std::cout<<k.size()<<std::endl<<k[0]<<k[1]<<k[2]<<k[3]<<std::endl;
//     
// }
