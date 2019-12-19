//some of the codes are written by youwei
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <iterator>
#include <cassert>


template <typename T>
void printVector(std::vector<T> const& v) {
	for (auto const& q : v) {
		std::cout << q << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void printVectorArrayArray(std::vector<T> vaa[][CUBE_NUM], int rows) {
	std::cout << "{ ";
	for (int i = 0; i < rows; ++i) {
		std::cout << "[ ";
		for (int j = 0; j < CUBE_NUM; ++j) {
			std::cout << "( ";
			for (auto q : vaa[i][j])
				std::cout << q << " ";
			std::cout << ") ";
		}
		std::cout << "] ";
	}
	std::cout << "} ";
	std::cout << std::endl;
}

template <typename T>
void printVectorArray(std::vector<T> va[], int rows) {
	for (int i = 0; i < rows; ++i) {
		std::cout << i << ": ";
		for (auto q : va[i])
			std::cout << q << " ";
		std::cout << std::endl;
	}
}

#define PAGESIZE 4096
// c style io
template <typename Q>
void loadArray(std::vector<Q>& array, const std::string& fname) {
	Timer timer(fname);
	struct stat st;
	assert(stat(fname.c_str(), &st) == 0);
	ssize_t fsize = st.st_size;
	array.resize(fsize / sizeof(Q));
	Q* p_array = array.data();
	int fd = open(fname.c_str(), O_RDONLY);
	assert(fd != -1);
	ssize_t offset = 0;
	while (offset < fsize) {
		ssize_t retsize = read(fd, (char*)p_array + offset, (fsize - offset + PAGESIZE - 1) / PAGESIZE * PAGESIZE);
		if (retsize == -1) {
			fprintf(stderr, "%s\n", strerror(errno));
			exit(-1);
		}
		offset += retsize;
	}
	assert(close(fd) == 0);
}

template <typename Q>
void dumpArray(const std::vector<Q>& array, int fd) {
	ssize_t fsize = array.size() * sizeof(Q);
	const Q* const p_array = array.data();
	ssize_t offset = 0;
	while (offset < fsize) {
		ssize_t retsize = write(fd, (char*)p_array + offset, fsize - offset);
		if (retsize == -1) {
			fprintf(stderr, "%s %d: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(-1);
		}
		offset += retsize;
	}
	std::cout << array.size() << "elements (" << fsize << "bytes)" << std::endl;
}

template <typename Q>
void dumpArray(const std::vector<Q>& array, const std::string& fname) {
	Timer timer(fname);
	int fd = open(fname.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	// size_t fsize = array.size() * sizeof(Q);
	// std::cerr << "fsize" << fsize << std::endl;
	assert(fd != -1);
	// fprintf(stderr, "%s\n", strerror(errno));
	dumpArray(array, fd);
	assert(close(fd) == 0);
}

template <typename Q>
void appendArray(const std::vector<Q>& array, const std::string& fname) {
	Timer timer(fname);
	int fd = open(fname.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	// size_t fsize = array.size() * sizeof(Q);
	// std::cerr << "fsize" << fsize << std::endl;
	assert(fd != -1);
	// fprintf(stderr, "%s\n", strerror(errno));
	dumpArray(array, fd);
	assert(close(fd) == 0);
}



//never use for bool! for raw vector only!!!
template <typename T>
inline void  _dump_vector(const std::string fileName,const std::vector<T>& v){
    std::ofstream d(fileName, std::ios::out | std::ios::binary);//oh, the stupid cpp won't create dir!!!
	assert(d.is_open());
    d.write((char*)&v[0], v.size() * sizeof(T));
    d.close();
}
// template <typename T>//won't create dir!!!
// inline void  _dump_vector(const std::string fileName,const std::vector<T>& v){
//         dumpArray(v,fileName);
// }

//https://stackoverflow.com/questions/15138353/how-to-read-a-binary-file-into-a-vector-of-unsigned-chars

template <typename T>
inline std::vector<T> _load_vector(const std::string filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
	assert(file.is_open());
    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    uint64_t realSize = fileSize/(sizeof(T));

    // read the data:
    std::vector<T> v(realSize);//size problem!!
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
